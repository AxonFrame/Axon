/**
 * @file        cluster_table.h
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

#ifndef Axon_CLUSTERTABLE_H
#define Axon_CLUSTERTABLE_H

#include <database/generic_tables/Axon_sql_table.h>
#include <Axon_common/logger.h>

class ClusterTable : public AxonSqlTable
{
   public:
    static ClusterTable* getInstance()
    {
        if (instance == nullptr) {
            instance = new ClusterTable();
        }
        return instance;
    }

    struct ClusterDbEntry {
        std::string uuid = "";
        std::string projectId = "";
        std::string ownerId = "";
        std::string visibility = "";
        std::string  = "";
    };

    ~ClusterTable();

    ReturnStatus addCluster(const ClusterDbEntry& clusterData,
                            const Axon::UserContext& userContext,
                            Axon::ErrorContainer& error);
    ReturnStatus getCluster(ClusterDbEntry& result,
                            const std::string& clusterUuid,
                            const Axon::UserContext& userContext,
                            Axon::ErrorContainer& error);
    ReturnStatus getCluster(json& result,
                            const std::string& clusterUuid,
                            const Axon::UserContext& userContext,
                            const bool showHiddenValues,
                            Axon::ErrorContainer& error);
    bool getAllCluster(Axon::TableItem& result,
                       const Axon::UserContext& userContext,
                       Axon::ErrorContainer& error);
    ReturnStatus deleteCluster(const std::string& clusterUuid,
                               const Axon::UserContext& userContext,
                               Axon::ErrorContainer& error);
    bool deleteAllCluster(Axon::ErrorContainer& error);

   private:
    ClusterTable();
    static ClusterTable* instance;
};

#endif  // Axon_CLUSTERTABLE_H
