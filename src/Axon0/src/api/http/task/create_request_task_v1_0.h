/**
 * @file        create_request_task_v1_0.h
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

#ifndef CREATEREQUESTTASK_H
#define CREATEREQUESTTASK_H

#include <api/endpoint_processing/blossom.h>
#include <core/cluster/task.h>

class Cluster;

class CreateRequestTaskV1M0 : public Blossom
{
   public:
    CreateRequestTaskV1M0();

   protected:
    bool runTask(BlossomIO& blossomIO,
                 const Axon::UserContext& userContext,
                 BlossomStatus& status,
                 Axon::ErrorContainer& error);

   private:
    ReturnStatus fillTaskIo(DataSetFileHandle& fileHandle,
                            const Axon::UserContext& userContext,
                            const std::string& column,
                            const std::string& datasetUuid,
                            BlossomStatus& status,
                            Axon::ErrorContainer& error);

    ReturnStatus createResultDataset(Cluster* cluster,
                                     Task* task,
                                     const std::string& dataset,
                                     const json& resultMetaData,
                                     const Axon::UserContext& userContext,
                                     BlossomStatus& status,
                                     Axon::ErrorContainer& error);
};

#endif  // CREATEREQUESTTASK_H
