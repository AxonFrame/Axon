/**
 * @file       Axon_sql_table.h
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

#ifndef Axon_SQL_TABLE_H
#define Axon_SQL_TABLE_H

#include <Axon_common/logger.h>
#include <Axon_common/structs.h>
#include <Axon_database/sql_table.h>
#include <uuid/uuid.h>

#include <string>
#include <vector>

class SqlDatabase;

class AxonSqlTable : public Axon::SqlTable
{
   public:
    AxonSqlTable(Axon::SqlDatabase* db);
    virtual ~AxonSqlTable();

    ReturnStatus doesAlreadyExist(const std::string& ,
                                      const Axon::UserContext& userContext,
                                      Axon::ErrorContainer& error);
    ReturnStatus doesUuidAlreadyExist(const std::string& uuid,
                                      const Axon::UserContext& userContext,
                                      Axon::ErrorContainer& error);

   protected:
    ReturnStatus addWithContext(json& values,
                                const Axon::UserContext& userContext,
                                Axon::ErrorContainer& error);
    ReturnStatus getWithContext(json& result,
                                const Axon::UserContext& userContext,
                                std::vector<RequestCondition>& conditions,
                                const bool showHiddenValues,
                                Axon::ErrorContainer& error);
    ReturnStatus updateWithContext(json& values,
                                   const Axon::UserContext& userContext,
                                   std::vector<RequestCondition>& conditions,
                                   Axon::ErrorContainer& error);
    ReturnStatus getAllWithContext(Axon::TableItem& result,
                                   const Axon::UserContext& userContext,
                                   std::vector<RequestCondition>& conditions,
                                   Axon::ErrorContainer& error,
                                   const bool showHiddenValues);
    ReturnStatus deleteFromDbWithContext(std::vector<RequestCondition>& conditions,
                                         const Axon::UserContext& userContext,
                                         Axon::ErrorContainer& error);

   private:
    void fillCondition(std::vector<RequestCondition>& conditions,
                       const Axon::UserContext& userContext);
};

#endif  // Axon_SQL_TABLE_H
