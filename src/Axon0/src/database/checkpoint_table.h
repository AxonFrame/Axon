/**
 * @file        checkpoint_table.h
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

#ifndef Axon_CLUSTER_CHECKPOINT_TABLE_H
#define Axon_CLUSTER_CHECKPOINT_TABLE_H

#include <database/generic_tables/Axon_sql_table.h>
#include <Axon_common/logger.h>
#include <Axon_common/structs.h>

class CheckpointTable : public AxonSqlTable
{
   public:
    static CheckpointTable* getInstance()
    {
        if (instance == nullptr) {
            instance = new CheckpointTable();
        }
        return instance;
    }

    struct CheckpointDbEntry {
        std::string uuid = "";
        std::string projectId = "";
        std::string ownerId = "";
        std::string visibility = "";
        std::string  = "";
        std::string location = "";
    };

    ~CheckpointTable();

    ReturnStatus addCheckpoint(const CheckpointDbEntry& checkpointData,
                               const Axon::UserContext& userContext,
                               Axon::ErrorContainer& error);
    ReturnStatus getCheckpoint(CheckpointDbEntry& result,
                               const std::string& checkpointUuid,
                               const Axon::UserContext& userContext,
                               Axon::ErrorContainer& error);
    ReturnStatus getCheckpoint(json& result,
                               const std::string& checkpointUuid,
                               const Axon::UserContext& userContext,
                               const bool showHiddenValues,
                               Axon::ErrorContainer& error);
    bool getAllCheckpoint(Axon::TableItem& result,
                          const Axon::UserContext& userContext,
                          const bool showHiddenValues,
                          Axon::ErrorContainer& error);
    ReturnStatus deleteCheckpoint(const std::string& checkpointUuid,
                                  const Axon::UserContext& userContext,
                                  Axon::ErrorContainer& error);

   private:
    CheckpointTable();
    static CheckpointTable* instance;
};

#endif  // Axon_CLUSTER_CHECKPOINT_TABLE_H
