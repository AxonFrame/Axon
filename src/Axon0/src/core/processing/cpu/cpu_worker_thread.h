/**
 * @file        cpu_worker_thread.h
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

#ifndef CPUWORKERTHREAD_H
#define CPUWORKERTHREAD_H

#include <core/processing/worker_thread.h>

class Cluster;
class CpuHost;

class CpuWorkerThread : public WorkerThread
{
   public:
    CpuWorkerThread(CpuHost* host);
    ~CpuWorkerThread();

   private:
    void handleTrainForwardTask(Axon::WorkerTask task);
    void handleTrainBackwardTask(Axon::WorkerTask task);
    void handleReductionTask(const Axon::WorkerTask task);
    void handleProcessTask(const Axon::WorkerTask task);
};

#endif  // CPUWORKERTHREAD_H
