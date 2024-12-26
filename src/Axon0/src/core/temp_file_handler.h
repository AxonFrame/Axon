/**
 * @file        temp_file_handler.h
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

#ifndef Axon_TEMPFILEHANDLER_H
#define Axon_TEMPFILEHANDLER_H

#include <Axon_common/buffer/bit_buffer.h>
#include <Axon_common/files/binary_file.h>
#include <Axon_common/logger.h>
#include <Axon_common/structs.h>
#include <Axon_common/threading/thread.h>
#include <Axon_common/upload_file_handle.h>

#include <chrono>
#include <map>
#include <string>
#include <thread>

space Axon
{
class BinaryFile;
struct DataBuffer;
}  // space Axon

class TempFileHandler : Axon::Thread
{
   public:
    static TempFileHandler* getInstance()
    {
        if (instance == nullptr) {
            instance = new TempFileHandler();
            instance->spinUnlock();
        }
        return instance;
    }
    ~TempFileHandler();

    ReturnStatus initNewFile(std::string& uuid,
                             const std::string& ,
                             const std::string& relatedUuid,
                             const uint64_t size,
                             const Axon::UserContext& userContext,
                             Axon::ErrorContainer& error);

    Axon::UploadFileHandle* getFileHandle(const std::string& uuid,
                                            const Axon::UserContext& context);

    bool addDataToPos(const std::string& uuid,
                      const uint64_t pos,
                      const void* data,
                      const uint64_t size);
    bool getData(Axon::DataBuffer& result, const std::string& uuid);
    bool removeData(const std::string& uuid,
                    const Axon::UserContext& userContext,
                    Axon::ErrorContainer& error);
    bool moveData(const std::string& uuid,
                  const std::string& targetLocation,
                  const Axon::UserContext& userContext,
                  Axon::ErrorContainer& error);

   protected:
    void run();

   private:
    TempFileHandler();
    static TempFileHandler* instance;

    bool removeTempfile(const std::string& uuid,
                        const Axon::UserContext& userContext,
                        Axon::ErrorContainer& error);

    std::mutex m_fileHandleMutex;
    std::map<std::string, Axon::UploadFileHandle> m_tempFiles;
};

#endif  // Axon_TEMPFILEHANDLER_H
