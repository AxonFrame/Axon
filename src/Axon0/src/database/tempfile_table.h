/**
 * @file        tempfile_table.h
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

#ifndef Axon_CLUSTER_tempfile_TABLE_H
#define Axon_CLUSTER_tempfile_TABLE_H

#include <database/generic_tables/Axon_sql_table.h>
#include <Axon_common/logger.h>

class TempfileTable : public AxonSqlTable
{
   public:
    static TempfileTable* getInstance()
    {
        if (instance == nullptr) {
            instance = new TempfileTable();
        }
        return instance;
    }

    struct TempfileDbEntry {
        std::string uuid = "";
        std::string projectId = "";
        std::string ownerId = "";
        std::string visibility = "";
        std::string  = "";
        std::string relatedResourceType = "";
        std::string relatedResourceUuid = "";
        std::string location = "";
        uint64_t fileSize = 0;
    };

    ~TempfileTable();

    ReturnStatus addTempfile(const TempfileDbEntry& tempfileData,
                             const Axon::UserContext& userContext,
                             Axon::ErrorContainer& error);
    ReturnStatus getTempfile(TempfileDbEntry& result,
                             const std::string& tempfileUuid,
                             const Axon::UserContext& userContext,
                             Axon::ErrorContainer& error);
    ReturnStatus getTempfile(json& result,
                             const std::string& tempfileUuid,
                             const Axon::UserContext& userContext,
                             const bool showHiddenValues,
                             Axon::ErrorContainer& error);
    bool getAllTempfile(Axon::TableItem& result,
                        const Axon::UserContext& userContext,
                        Axon::ErrorContainer& error);
    ReturnStatus deleteTempfile(const std::string& tempfileUuid,
                                const Axon::UserContext& userContext,
                                Axon::ErrorContainer& error);
    ReturnStatus getRelatedResourceUuids(std::vector<std::string>& relatedUuids,
                                         const std::string& resourceType,
                                         const std::string& resourceUuid,
                                         const Axon::UserContext& userContext,
                                         Axon::ErrorContainer& error);

   private:
    TempfileTable();
    static TempfileTable* instance;
};

#endif  // Axon_CLUSTER_tempfile_TABLE_H
