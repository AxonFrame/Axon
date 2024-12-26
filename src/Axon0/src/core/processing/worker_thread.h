/**
 * @file        worker_thread.h
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

#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <Axon_common/defines.h>
#include <Axon_common/structs.h>
#include <Axon_common/threading/thread.h>

class LogicalHost;
class Cluster;

class WorkerThread : public Axon::Thread
{
   public:
    WorkerThread();
    ~WorkerThread();

   protected:
    void run();

    LogicalHost* m_host = nullptr;

    void addWorkerTaskToQueue(const Axon::WorkerTask task);

   private:
    void handleTask(const Axon::WorkerTask& task);
    virtual void handleTrainForwardTask(Axon::WorkerTask task) = 0;
    virtual void handleTrainBackwardTask(Axon::WorkerTask task) = 0;
    ;
    virtual void handleReductionTask(const Axon::WorkerTask task) = 0;
    virtual void handleProcessTask(const Axon::WorkerTask task) = 0;

    uint32_t m_inactiveCounter = 0;
};

#endif  // WORKERTHREAD_H
