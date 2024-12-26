/**
 * @file        buffer_io.h
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

#ifndef BUFFERIO_H
#define BUFFERIO_H

#include <core/io/checkpoint/io_interface.h>
#include <Axon_common/buffer/data_buffer.h>

class BufferIO : public IO_Interface
{
   public:
    BufferIO();
    ~BufferIO();

    ReturnStatus writeClusterIntoBuffer(Axon::DataBuffer& target,
                                        const Cluster& cluster,
                                        Axon::ErrorContainer& error);
    ReturnStatus readClusterFromBuffer(Cluster& cluster,
                                       Axon::DataBuffer& input,
                                       LogicalHost* host,
                                       Axon::ErrorContainer& error);

   private:
    bool initializeTarget(const uint64_t size, Axon::ErrorContainer& error);
    bool writeFromLocalBuffer(const LocalBuffer& localBuffer, Axon::ErrorContainer&);
    bool readToLocalBuffer(LocalBuffer& localBuffer, Axon::ErrorContainer&);

    Axon::DataBuffer* m_buffer = nullptr;
};

#endif  // BUFFERIO_H
