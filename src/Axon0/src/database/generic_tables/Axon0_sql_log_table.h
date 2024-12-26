/**
 * @file       Axon_sql_log_table.h
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

#ifndef Axon_DATABASE_SQL_LOG_TABLE_H
#define Axon_DATABASE_SQL_LOG_TABLE_H

#include <Axon_common/logger.h>
#include <Axon_database/sql_table.h>
#include <uuid/uuid.h>

#include <string>
#include <vector>

class SqlDatabase;

class AxonSqlLogTable : public Axon::SqlTable
{
   public:
    AxonSqlLogTable(Axon::SqlDatabase* db);
    virtual ~AxonSqlLogTable();

    long getNumberOfPages(Axon::ErrorContainer& error);
    ReturnStatus getPageFromDb(Axon::TableItem& resultTable,
                               const std::string& userId,
                               const uint64_t page,
                               Axon::ErrorContainer& error);
};

#endif  // Axon_DATABASE_SQL_LOG_TABLE_H
