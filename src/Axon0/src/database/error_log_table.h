/**
 * @file        error_log_table.h
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

#ifndef Axon_ERROR_LOG_TABLE_H
#define Axon_ERROR_LOG_TABLE_H

#include <database/generic_tables/Axon_sql_log_table.h>
#include <Axon_common/logger.h>

class ErrorLogTable : public AxonSqlLogTable
{
   public:
    static ErrorLogTable* getInstance()
    {
        if (instance == nullptr) {
            instance = new ErrorLogTable();
        }
        return instance;
    }

    ~ErrorLogTable();

    bool addErrorLogEntry(const std::string& userid,
                          const std::string& component,
                          const std::string& context,
                          const std::string& values,
                          const std::string& message,
                          Axon::ErrorContainer& error);
    bool getAllErrorLogEntries(Axon::TableItem& result,
                               const std::string& userId,
                               const uint64_t page,
                               Axon::ErrorContainer& error);

   private:
    ErrorLogTable();
    static ErrorLogTable* instance;
};

#endif  // Axon_ERROR_LOG_TABLE_H
