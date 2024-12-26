/**
 * @file        cluster_init.h
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

#ifndef Axon_CLUSTERINIT_H
#define Axon_CLUSTERINIT_H

#include <core/cluster/objects.h>
#include <Axon_cluster_parser/cluster_meta.h>

class CoreSegment;
class Cluster;

using Axon::ClusterMeta;

bool initNewCluster(Cluster* cluster,
                    const Axon::ClusterMeta& clusterMeta,
                    const std::string& uuid,
                    LogicalHost* host);

void initializeHeader(Cluster* cluster, const std::string& uuid);
void initializeSettings(Cluster* cluster, const Axon::ClusterMeta& clusterMeta);

void initializeHexagons(Cluster* cluster,
                        const Axon::ClusterMeta& clusterMeta,
                        LogicalHost* host);
void updateAxons(Cluster* cluster, const Axon::ClusterMeta& clusterMeta);
void initializeTargetHexagonList(Cluster* cluster);
void initializeOutputNeurons(Cluster* cluster);
void initializeInputs(Cluster* cluster, const Axon::ClusterMeta& clusterMeta);
void initializeOutputs(Cluster* cluster, const Axon::ClusterMeta& clusterMeta);

void connectHexagon(Cluster* cluster, Hexagon& sourceHexagon, const uint8_t side);
void connectAllHexagons(Cluster* cluster);
uint32_t goToNextInitHexagon(Cluster* cluster,
                             Hexagon* currentHexagon,
                             int32_t& maxPathLength,
                             const uint32_t sourceHexagonId);

#endif  // Axon_CLUSTERINIT_H
