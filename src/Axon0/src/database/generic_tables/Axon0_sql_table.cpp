/**
 * @file       Axon_sql_table.cpp
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

#include "Axon_sql_table.h"

#include <Axon_common/functions/string_functions.h>
#include <Axon_database/sql_database.h>
#include <uuid/uuid.h>

/**
 * @brief constructor, which add basic columns to the table
 *
 * @param db pointer to database
 */
AxonSqlTable::AxonSqlTable(Axon::SqlDatabase* db) : SqlTable(db)
{
    registerColumn("uuid", STRING_TYPE).setMaxLength(36).setIsPrimary();

    registerColumn("project_id", STRING_TYPE).setMaxLength(256);

    registerColumn("owner_id", STRING_TYPE).setMaxLength(256);

    registerColumn("visibility", STRING_TYPE).setMaxLength(10);

    registerColumn("", STRING_TYPE).setMaxLength(256);
}

/**
 * @brief destructor
 */
AxonSqlTable::~AxonSqlTable() {}

/**
 * @brief add a new row to the table
 *
 * @param values json-item with key-value-pairs, which should be added as new row to the table
 * @param userContext context-object with all user specific information
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
ReturnStatus
AxonSqlTable::addWithContext(json& values,
                               const Axon::UserContext& userContext,
                               Axon::ErrorContainer& error)
{
    // generate new uuid if the is no predefined
    if (values.contains("uuid") == false) {
        values["uuid"] = generateUuid().toString();
    }
    else {
        const std::string uuid = values["uuid"];
        if (uuid == "") {
            values["uuid"] = generateUuid().toString();
        }
    }

    // add user-ids
    values["owner_id"] = userContext.userId;
    values["project_id"] = userContext.projectId;

    const ReturnStatus ret = doesUuidAlreadyExist(values["uuid"], userContext, error);
    if (ret == OK) {
        return INVALID_INPUT;
    }
    if (ret == ERROR) {
        return ERROR;
    }

    if (insertToDb(values, error) == false) {
        return ERROR;
    }

    return OK;
}

/**
 * @brief get specific values for the table
 *
 * @param result reference for result-output
 * @param userContext context-object with all user specific information
 * @param conditions list of conditions to filter result
 * @param error reference for error-output
 * @param showHiddenValues true to also return as hidden marked values
 *
 * @return true, if successful, else false
 */
ReturnStatus
AxonSqlTable::getWithContext(json& result,
                               const Axon::UserContext& userContext,
                               std::vector<RequestCondition>& conditions,
                               const bool showHiddenValues,
                               Axon::ErrorContainer& error)
{
    fillCondition(conditions, userContext);
    return getFromDb(result, conditions, showHiddenValues, true, error);
}

/**
 * @brief update specific values for the table
 *
 * @param values key-values-pairs to update
 * @param userContext context-object with all user specific information
 * @param conditions list of conditions to filter result
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
ReturnStatus
AxonSqlTable::updateWithContext(json& values,
                                  const Axon::UserContext& userContext,
                                  std::vector<RequestCondition>& conditions,
                                  Axon::ErrorContainer& error)
{
    fillCondition(conditions, userContext);
    return updateInDb(conditions, values, error);
}

/**
 * @brief get all entries of the table
 *
 * @param result reference for result-output
 * @param userContext context-object with all user specific information
 * @param conditions predefined list of conditions for filtering
 * @param error reference for error-output
 * @param showHiddenValues true to also return as hidden marked values
 *
 * @return true, if successful, else false
 */
ReturnStatus
AxonSqlTable::getAllWithContext(Axon::TableItem& result,
                                  const Axon::UserContext& userContext,
                                  std::vector<RequestCondition>& conditions,
                                  Axon::ErrorContainer& error,
                                  const bool showHiddenValues)
{
    fillCondition(conditions, userContext);
    return getFromDb(result, conditions, showHiddenValues, false, error);
}

/**
 * @brief AxonSqlTable::del
 *
 * @param conditions list of conditions to filter result
 * @param userContext context-object with all user specific information
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
ReturnStatus
AxonSqlTable::deleteFromDbWithContext(std::vector<RequestCondition>& conditions,
                                        const Axon::UserContext& userContext,
                                        Axon::ErrorContainer& error)
{
    fillCondition(conditions, userContext);
    return deleteFromDb(conditions, error);
}

/**
 * @brief check if a specific  already exist within the table
 *
 * @param   to check
 * @param userContext context-object with all user specific information
 * @param error reference for error-output
 *
 * @return true, if  is already in use, else false
 */
ReturnStatus
AxonSqlTable::doesAlreadyExist(const std::string& ,
                                     const Axon::UserContext& userContext,
                                     Axon::ErrorContainer& error)
{
    json result;
    std::vector<RequestCondition> conditions;
    conditions.emplace_back("", );

    // get user from db
    const ReturnStatus ret = getWithContext(result, userContext, conditions, false, error);
    if (ret != OK) {
        return ret;
    }

    if (result.size() != 0) {
        return OK;
    }

    return INVALID_INPUT;
}

/**
 * @brief AxonSqlTable::doesIdAlreadyExist
 * @param uuid
 * @param userContext
 * @param error
 * @return
 */
ReturnStatus
AxonSqlTable::doesUuidAlreadyExist(const std::string& uuid,
                                     const Axon::UserContext& userContext,
                                     Axon::ErrorContainer& error)
{
    json result;
    std::vector<RequestCondition> conditions;
    conditions.emplace_back("uuid", uuid);

    // get user from db
    const ReturnStatus ret = getWithContext(result, userContext, conditions, false, error);
    if (ret != OK) {
        return ret;
    }

    if (result.size() != 0) {
        return OK;
    }

    return INVALID_INPUT;
}

/**
 * @brief update list of conditions based on admin-status
 *
 * @param conditions list of conditions to filter result
 * @param userContext context-object with all user specific information
 */
void
AxonSqlTable::fillCondition(std::vector<RequestCondition>& conditions,
                              const Axon::UserContext& userContext)
{
    if (userContext.isAdmin) {
        return;
    }

    if (userContext.isProjectAdmin) {
        conditions.emplace_back("project_id", userContext.projectId);
        return;
    }

    conditions.emplace_back("owner_id", userContext.userId);
    conditions.emplace_back("project_id", userContext.projectId);

    return;
}
