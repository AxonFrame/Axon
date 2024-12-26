/**
 * @file        cluster.h
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

#ifndef Axon_CLUSTER_H
#define Axon_CLUSTER_H

#include <api/endpoint_processing/http_websocket_thread.h>
#include <core/cluster/objects.h>
#include <core/cluster/task.h>
#include <Axon_cluster_parser/cluster_meta.h>
#include <Axon_common/buffer/data_buffer.h>
#include <Axon_common/buffer/item_buffer.h>

#include <atomic>

class TaskHandle_State;
class LogicalHost;

space Axon
{
class Statemachine;
}  // space Axon

class Cluster
{
   public:
    Cluster();
    Cluster(const void* data, const uint64_t dataSize);
    ~Cluster();

    // processing
    uint32_t reductionCounter = 0;
    HttpWebsocketThread* msgClient = nullptr;
    Axon::Statemachine* stateMachine = nullptr;
    TaskHandle_State* taskHandleState = nullptr;
    bool enableCreation = false;

    // cluster-data
    ClusterHeader clusterHeader;
    ClusterMetrics metrics;

    std::vector<Hexagon> hexagons;
    std::map<std::string, InputInterface> inputInterfaces;
    std::map<std::string, OutputInterface> outputInterfaces;

    // meta
    const std::string getUuid();
    bool init(const Axon::ClusterMeta& clusterTemplate,
              const std::string& uuid,
              LogicalHost* host = nullptr);

    // tasks
    Task* addNewTask();
    Task* getCurrentTask();
    const TaskProgress getProgress(const std::string& taskUuid);
    const Task* getTask(const std::string& taskUuid);
    bool removeTask(const std::string& taskUuid);
    bool isFinish(const std::string& taskUuid);
    void getAllProgress(std::map<std::string, TaskProgress>& result);
    void updateClusterState(const Axon::WorkerTask& task);
    TaskType finishTask();

    // states
    bool goToNextState(const uint32_t nextStateId);
    void startForwardCycle(const bool runNormalMode);
    void startBackwardCycle();
    void startReductionCycle();
    bool setClusterState(const std::string& newState);

    // counter for parallel-processing
    bool incrementAndCompare(const uint32_t referenceValue);

   private:
    std::mutex m_clusterStateLock;
    std::atomic<int> m_counter;

    std::deque<std::string> m_taskQueue;
    std::map<std::string, Task> m_taskMap;
    std::mutex m_taskMutex;
    Task* m_currentTask = nullptr;

    bool getNextTask();
};

#endif  // Axon_CLUSTER_H
