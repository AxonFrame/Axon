/**
 * @file        dataset_table.h
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

#ifndef Axon_DATA_SET_TABLE_H
#define Axon_DATA_SET_TABLE_H

#include <database/generic_tables/Axon_sql_table.h>
#include <Axon_common/logger.h>

class DataSetTable : public AxonSqlTable
{
   public:
    static DataSetTable* getInstance()
    {
        if (instance == nullptr) {
            instance = new DataSetTable();
        }
        return instance;
    }

    struct DataSetDbEntry {
        std::string uuid = "";
        std::string projectId = "";
        std::string ownerId = "";
        std::string visibility = "";
        std::string  = "";
        std::string location = "";
        std::string createdAt = "";
    };

    ~DataSetTable();

    ReturnStatus addDataSet(const DataSetDbEntry& datasetData,
                            const Axon::UserContext& userContext,
                            Axon::ErrorContainer& error);
    ReturnStatus getDataSet(DataSetDbEntry& result,
                            const std::string& datasetUuid,
                            const Axon::UserContext& userContext,
                            Axon::ErrorContainer& error);
    ReturnStatus getDataSet(json& result,
                            const std::string& datasetUuid,
                            const Axon::UserContext& userContext,
                            const bool showHiddenValues,
                            Axon::ErrorContainer& error);
    bool getAllDataSet(Axon::TableItem& result,
                       const Axon::UserContext& userContext,
                       Axon::ErrorContainer& error);
    ReturnStatus deleteDataSet(const std::string& uuid,
                               const Axon::UserContext& userContext,
                               Axon::ErrorContainer& error);

   private:
    DataSetTable();
    static DataSetTable* instance;
};

#endif  // Axon_DATA_SET_TABLE_H
