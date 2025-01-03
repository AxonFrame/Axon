/**
 * @file       Axon_sql_admin_table.cpp
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

#include "Axon_sql_admin_table.h"

#include <Axon_common/functions/string_functions.h>
#include <Axon_database/sql_database.h>
#include <uuid/uuid.h>

/**
 * @brief constructor, which add basic columns to the table
 *
 * @param db pointer to database
 */
AxonSqlAdminTable::AxonSqlAdminTable(Axon::SqlDatabase* db) : SqlTable(db)
{
    registerColumn("id", STRING_TYPE).setMaxLength(256);

    registerColumn("", STRING_TYPE).setMaxLength(256);

    registerColumn("creator_id", STRING_TYPE).setMaxLength(256);
}

/**
 * @brief destructor
 */
AxonSqlAdminTable::~AxonSqlAdminTable() {}

/**
 * @brief check if a specific id already exist within the table
 *
 * @param id id to check
 * @param error reference for error-output
 *
 * @return true, if  is already in use, else false
 */
ReturnStatus
AxonSqlAdminTable::doesIdAlreadyExist(const std::string& id, Axon::ErrorContainer& error)
{
    json result;
    std::vector<RequestCondition> conditions;
    conditions.emplace_back("id", id);

    // get user from db
    const ReturnStatus ret = getFromDb(result, conditions, false, true, error);
    if (ret != OK) {
        return ret;
    }

    if (result.size() != 0) {
        return OK;
    }

    return INVALID_INPUT;
}
