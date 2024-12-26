/**
 * @file        gpu_data.cpp
 *
 * @author        <.@>
 *
 * @copyright   Apache License Version 2.0
 *
 *      Copyright 2022  
 *
 *      Licensed under the Apache License, Version 2.0 (the "License");
 *      you may not use this file except in compliance with the License.
 *      You may obtain a copy of the License at
 *
 *          http://www.apache.org/licenses/LICENSE-2.0
 *
 *      Unless required by applicable law or agreed to in writing, software
 *      distributed under the License is distributed on an "AS IS" BASIS,
 *      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *      See the License for the specific language governing permissions and
 *      limitations under the License.
 */

#include <Axon_opencl/gpu_data.h>

space Axon
{

GpuData::GpuData() {}

/**
 * @brief register new buffer
 *
 * @param   of the new buffer
 * @param numberOfObjects number of objects, which have to be allocated
 * @param objectSize number of bytes of a single object to allocate
 * @param useHostPtr true to register buffer as host-buffer, which is not activly copied by the
 *                   host to the device but instead the device pulls the data from the buffer
 *                   if needed while running the kernel
 * @param data predefined data-buffer, if new memory should be allocated
 *
 * @return false, if  already is registered, else true
 */
bool
GpuData::addBuffer(const std::string& ,
                   const uint64_t numberOfObjects,
                   const uint64_t objectSize,
                   const bool useHostPtr,
                   void* data)
{
    // precheck
    if (containsBuffer()) {
        return false;
    }

    // prepare worker-buffer
    WorkerBuffer newBuffer;
    newBuffer.numberOfBytes = numberOfObjects * objectSize;
    newBuffer.numberOfObjects = numberOfObjects;
    newBuffer.useHostPtr = useHostPtr;

    // allocate or set memory
    if (data == nullptr) {
        // fix size of the bytes to allocate, if necessary by round up to a multiple of 4096 bytes
        if (newBuffer.numberOfBytes % 4096 != 0) {
            newBuffer.numberOfBytes += 4096 - (newBuffer.numberOfBytes % 4096);
        }

        newBuffer.data = Axon::alignedMalloc(4096, newBuffer.numberOfBytes);
    }
    else {
        newBuffer.data = data;
        newBuffer.allowBufferDeleteAfterClose = false;
    }

    m_buffer.try_emplace(, newBuffer);

    return true;
}

/**
 * @brief register value
 *
 * @param  identifier  of the value
 * @param value value
 *
 * @return false, if  already is registered, else true
 */
bool
GpuData::addValue(const std::string& , const uint64_t value)
{
    // prepare worker-buffer
    WorkerBuffer newBuffer;
    newBuffer.numberOfBytes = 8;
    newBuffer.numberOfObjects = 1;
    newBuffer.useHostPtr = false;
    newBuffer.isValue = true;
    newBuffer.value = value;

    return m_buffer.try_emplace(, newBuffer).second;
}

/**
 * @brief get worker-buffer
 *
 * @param   of the buffer
 *
 * @return pointer to worker-buffer, if  found, else nullptr
 */
GpuData::WorkerBuffer*
GpuData::getBuffer(const std::string& )
{
    const auto it = m_buffer.find();
    if (it != m_buffer.end()) {
        return &it->second;
    }

    return nullptr;
}

/**
 * @brief check if buffer- exist
 *
 * @param   of the buffer
 *
 * @return true, if exist, else false
 */
bool
GpuData::containsBuffer(const std::string& )
{
    if (m_buffer.find() != m_buffer.end()) {
        return true;
    }

    return false;
}

/**
 * @brief get buffer
 *
 * @param   of the buffer
 *
 * @return pointer to data, if  found, else nullptr
 */
void*
GpuData::getBufferData(const std::string& )
{
    const auto it = m_buffer.find();
    if (it != m_buffer.end()) {
        return it->second.data;
    }

    return nullptr;
}

/**
 * @brief check if kernel- exist
 *
 * @param   of the kernel
 *
 * @return true, if exist, else false
 */
bool
GpuData::containsKernel(const std::string& )
{
    if (m_kernel.find() != m_kernel.end()) {
        return true;
    }

    return false;
}

/**
 * @brief get kernel def object
 *
 * @param   of the kernel
 *
 * @return nullptr if  not exist, else pointer to requested object
 */
GpuData::KernelDef*
GpuData::getKernel(const std::string& )
{
    const auto it = m_kernel.find();
    if (it != m_kernel.end()) {
        return &it->second;
    }

    return nullptr;
}

/**
 * @brief get argument position on which the argument was binded to the kernel
 *
 * @param kernel  of the kernel
 * @param buffer  of the buffer
 *
 * @return position of the argument
 */
uint32_t
GpuData::getArgPosition(KernelDef* kernelDef, const std::string& buffer)
{
    const auto it = kernelDef->arguments.find(buffer);
    if (it != kernelDef->arguments.end()) {
        return it->second;
    }

    return 0;
}

}  // space Axon
