/**
 * @file        checkpoint_io.h
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

#ifndef CHECKPOINTIO_H
#define CHECKPOINTIO_H

#include <core/io/checkpoint/io_interface.h>
#include <Axon_common/files/binary_file.h>
#include <Axon_common/logger.h>

#include <string>

class Cluster;
struct CheckpointHeader;

class CheckpointIO : public IO_Interface
{
   public:
    CheckpointIO();
    ~CheckpointIO();

    ReturnStatus writeClusterToFile(Cluster& cluster,
                                    const std::string& filePath,
                                    Axon::ErrorContainer& error);
    ReturnStatus restoreClusterFromFile(Cluster& cluster,
                                        const std::string& fileLocation,
                                        LogicalHost* host,
                                        Axon::ErrorContainer& error);

   private:
    bool initializeTarget(const uint64_t size, Axon::ErrorContainer& error);
    bool writeFromLocalBuffer(const LocalBuffer& localBuffer, Axon::ErrorContainer& error);
    bool readToLocalBuffer(LocalBuffer& localBuffer, Axon::ErrorContainer& error);

    Axon::BinaryFile* m_checkpointFile = nullptr;
};

#endif  // CHECKPOINTIO_H
