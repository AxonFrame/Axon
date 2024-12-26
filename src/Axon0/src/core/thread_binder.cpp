/**
 * @file        thread_binder.cpp
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

#include "thread_binder.h"

#include <Axon_common/threading/thread.h>
#include <Axon_common/threading/thread_handler.h>
#include <Axon_hardware/cpu_core.h>
#include <Axon_hardware/cpu_package.h>
#include <Axon_hardware/cpu_thread.h>
#include <Axon_hardware/host.h>
#include <Axon_root.h>

ThreadBinder* ThreadBinder::instance = nullptr;

ThreadBinder::ThreadBinder() : Axon::Thread("ThreadBinder") {}

/**
 * @brief init by selecting threads
 *
 * @param error reference for error-output
 *
 * @return
 */
bool
ThreadBinder::init(Axon::ErrorContainer& error)
{
    if (fillCoreIds(m_controlCoreIds, m_processingCoreIds, error) == false) {
        error.addMessage("Failed to initialize cpu-thread-lists for thread-binder.");
        return false;
    }

    return true;
}

/**
 * @brief get actual mapping as json
 */
json
ThreadBinder::getMapping()
{
    std::lock_guard<std::mutex> guard(m_mapLock);
    return m_completeMap;
}

/**
 * @brief get number of physical threads, which are defined for
 *        the core-processing
 */
uint64_t
ThreadBinder::getNumberOfProcessingThreads()
{
    std::lock_guard<std::mutex> guard(m_mapLock);
    return m_processingCoreIds.size();
}

/**
 * @brief fill lists with ids for the binding
 *
 * @param controlCoreIds reference to the list for all ids of control-processes
 * @param processingCoreIds reference to the list for all ids of processing-processes
 * @param error reference for error-output
 *
 * @return false, if a list is empty, else true
 */
bool
ThreadBinder::fillCoreIds(std::vector<uint64_t>& controlCoreIds,
                          std::vector<uint64_t>& processingCoreIds,
                          Axon::ErrorContainer& error)
{
    std::lock_guard<std::mutex> guard(m_mapLock);

    Axon::CpuCore* phyCore = nullptr;
    Axon::Host* host = Axon::Host::getInstance();

    if (host->cpuPackages.size() == 0) {
        error.addMessage("Failed to read number of cpu-packages from host.");
        return false;
    }

    if (host->cpuPackages[0]->cpuCores.size() == 0) {
        error.addMessage("Failed to read number of cpu-cores from host.");
        return false;
    }

    // control-cores
    phyCore = host->cpuPackages[0]->cpuCores[0];
    for (Axon::CpuThread* singleThread : phyCore->cpuThreads) {
        controlCoreIds.push_back(singleThread->threadId);
    }

    return true;
}

/**
 * @brief ThreadBinder::run
 */
void
ThreadBinder::run()
{
    Axon::ThreadHandler* threadHandler = Axon::ThreadHandler::getInstance();
    sleep(5);

    while (m_abort == false) {
        m_mapLock.lock();

        do {
            m_completeMap.clear();
            const std::vector<std::string> threads = threadHandler->getRegistereds();

            for (const std::string&  : threads) {
                // update thread-binding
                const std::vector<Axon::Thread*> threads = threadHandler->getThreads();
                for (Axon::Thread* thread : threads) {
                    if ( != "WorkerThread") {
                        if (thread->bindThreadToCores(m_controlCoreIds) == false) {
                            break;
                        }
                    }
                }

                // update list for output
                if ( != "CpuProcessingUnit") {
                    json idList = json::array();
                    for (const uint64_t id : m_controlCoreIds) {
                        idList.push_back((long)id);
                    }
                    m_completeMap[] = idList;
                }
            }

            // add initially defined core-ids to output
            ThreadHandler* threadHandler = ThreadHandler::getInstance();
            const std::vector<Thread*> coreThreads = threadHandler->getThreads("WorkerThread");
            for (const Thread* thread : coreThreads) {
                const std::string entry = "WorkerThread_" + std::to_string(thread->getThreadId());
                const uint64_t coreId = thread->getCoreIds().at(0);
                json idList = json::array();
                idList.push_back((long)coreId);
                m_completeMap[entry] = idList;
            }

            // debug-output
            // std::cout<<"#############################################################"<<std::endl;
            // std::cout<<m_completeMap.dump(4)<<std::endl;
            // std::cout<<"#############################################################"<<std::endl;
            // LOG_DEBUG(newMapping.dump(4));
        }
        while (false);
        m_mapLock.unlock();

        sleep(10);
    }
}
