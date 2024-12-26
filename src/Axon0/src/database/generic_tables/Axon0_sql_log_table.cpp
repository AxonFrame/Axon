/**
 * @file       Axon_sql_log_table.cpp
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

#include "Axon_sql_log_table.h"

#include <Axon_common/functions/string_functions.h>
#include <Axon_database/sql_database.h>
#include <uuid/uuid.h>

/**
 * @brief constructor, which add basic columns to the table
 *
 * @param db pointer to database
 */
AxonSqlLogTable::AxonSqlLogTable(Axon::SqlDatabase* db) : SqlTable(db) {}

/**
 * @brief destructor
 */
AxonSqlLogTable::~AxonSqlLogTable() {}

/**
 * @brief get number of pages, where each contains 100 entries
 *
 * @param error reference for error-output
 *
 * @return -1 if request against database failed, else number of rows
 */
long
AxonSqlLogTable::getNumberOfPages(Axon::ErrorContainer& error)
{
    const long numberOfRows = getNumberOfRows(error);
    if (numberOfRows == -1) {
        return -1;
    }

    return (numberOfRows / 100) + 1;
}

/**
 * @brief get a page with up to 100 log-entries from the database
 *
 * @param result reference for the result-output
 * @param userId id of the user, whos logs are requested
 * @param page a page has 100 entries so (page * 100)
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
ReturnStatus
AxonSqlLogTable::getPageFromDb(Axon::TableItem& resultTable,
                                 const std::string& userId,
                                 const uint64_t page,
                                 Axon::ErrorContainer& error)
{
    // get number of pages of the log-table
    const long numberOfPages = getNumberOfPages(error);
    if (numberOfPages == -1) {
        return INVALID_INPUT;
    }

    // check if requested page-number is in range
    if (page > static_cast<uint64_t>(numberOfPages)) {
        error.addMessage("Give page '" + std::to_string(page) + "' is too big");
        return INVALID_INPUT;
    }

    // get requested page of log-entries from database-table
    std::vector<RequestCondition> conditions;
    conditions.push_back(RequestCondition("user_id", userId));
    return getFromDb(resultTable, conditions, true, false, error, page * 100, 100);
}
