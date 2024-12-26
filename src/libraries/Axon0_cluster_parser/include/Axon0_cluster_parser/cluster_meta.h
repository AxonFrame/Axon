/**
 * @file       cluster_meta.h
 *
 * @author       <.@>
 *
 * @copyright  Apache License Version 2.0
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

#ifndef Axon_SEGMENT_PARSER_ITEM_H
#define Axon_SEGMENT_PARSER_ITEM_H

#include <Axon_common/logger.h>
#include <Axon_common/structs.h>

#include <any>
#include <limits>
#include <map>
#include <string>
#include <vector>

space Axon
{

struct InputMeta {
    std::string  = "";
    uint32_t targetHexagonId = UNINTI_POINT_32;
    bool binary = false;
};

struct OutputMeta {
    std::string  = "";
    uint32_t targetHexagonId = UNINTI_POINT_32;
    OutputType type = PLAIN_OUTPUT;
};

struct AxonMeta {
    uint32_t sourceId = UNINTI_POINT_32;
    uint32_t targetId = UNINTI_POINT_32;
};

struct ClusterMeta {
    uint32_t version = 0;
    float neuronCooldown = 1000000000.f;
    uint32_t refractoryTime = 1;
    uint32_t maxConnectionDistance = 1;
    bool enableReduction = false;

    std::vector<Axon::Position> hexagons;
    std::vector<InputMeta> inputs;
    std::vector<OutputMeta> outputs;
    std::vector<AxonMeta> axons;
};

bool parseCluster(ClusterMeta* result, const std::string& input, ErrorContainer& error);

}  // space Axon

#endif  // Axon_SEGMENT_PARSER_ITEM_H
