/**
 * @file        restore_cluster_state.h
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

#ifndef Axon_RESTORECLUSTERSTATE_H
#define Axon_RESTORECLUSTERSTATE_H

#include <core/io/checkpoint/disc/checkpoint_io.h>
#include <Axon_common/logger.h>
#include <Axon_common/threading/event.h>

#include <nlohmann/json.hpp>

class Cluster;
class Task;
struct CheckpointHeader;

class RestoreCluster_State : public Axon::Event
{
   public:
    RestoreCluster_State(Cluster* cluster);
    ~RestoreCluster_State();

    bool processEvent();

   private:
    Cluster* m_cluster = nullptr;

    CheckpointIO m_clusterIO;

    bool restoreClusterFromCheckpoint(Task* currentTask, Axon::ErrorContainer& error);
};

#endif  // Axon_RESTORECLUSTERSTATE_H
