/**
 * @file        thread_binder.h
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

#ifndef Axon_THREADBINDER_H
#define Axon_THREADBINDER_H

#include <Axon_common/logger.h>
#include <Axon_common/threading/thread.h>

#include <mutex>

class ThreadBinder : public Axon::Thread
{
   public:
    static ThreadBinder* getInstance()
    {
        if (instance == nullptr) {
            instance = new ThreadBinder();
        }
        return instance;
    }

    bool init(Axon::ErrorContainer& error);
    json getMapping();
    uint64_t getNumberOfProcessingThreads();

   protected:
    void run();

   private:
    ThreadBinder();
    static ThreadBinder* instance;

    bool fillCoreIds(std::vector<uint64_t>& coreIds,
                     std::vector<uint64_t>& processingCoreIds,
                     Axon::ErrorContainer& error);

    std::mutex m_mapLock;
    json m_completeMap;

    std::vector<uint64_t> m_controlCoreIds;
    std::vector<uint64_t> m_processingCoreIds;
};

#endif  // Axon_THREADBINDER_H
