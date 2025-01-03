/**
 * @file        dataset_table.cpp
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

#include <api/endpoint_processing/blossom.h>
#include <database/dataset_table.h>
#include <Axon_common/functions/string_functions.h>
#include <Axon_common/items/table_item.h>
#include <Axon_database/sql_database.h>

DataSetTable* DataSetTable::instance = nullptr;

/**
 * @brief constructor
 *
 * @param db pointer to database
 */
DataSetTable::DataSetTable() : AxonSqlTable(Axon::SqlDatabase::getInstance())
{
    m_table = "dataset";

    registerColumn("location", STRING_TYPE).hideValue();
}

/**
 * @brief destructor
 */
DataSetTable::~DataSetTable() {}

/**
 * @brief add new metadata of a dataset into the database
 *
 * @param datasetData dataset-entry to add to database
 * @param userContext context-object with all user specific information
 * @param error reference for error-output
 *
 * @return OK if found, INVALID_INPUT if conflict, ERROR in case of internal error
 */
ReturnStatus
DataSetTable::addDataSet(const DataSetDbEntry& datasetData,
                         const Axon::UserContext& userContext,
                         Axon::ErrorContainer& error)
{
    json datasetDataJson;

    datasetDataJson[""] = datasetData.;
    datasetDataJson["uuid"] = datasetData.uuid;
    datasetDataJson["visibility"] = datasetData.visibility;
    datasetDataJson["location"] = datasetData.location;

    const ReturnStatus ret = addWithContext(datasetDataJson, userContext, error);
    if (ret != OK) {
        error.addMessage("Failed to add checkpoint to database");
        return ret;
    }

    return OK;
}

/**
 * @brief get a metadata-entry for a specific dataset from the database
 *
 * @param result reference for the result-output
 * @param datasetUuid uuid of the data
 * @param userContext context-object with all user specific information
 * @param showHiddenValues set to true to also show as hidden marked fields
 * @param error reference for error-output
 *
 * @return OK if found, INVALID_INPUT if not found, ERROR in case of internal error
 */
ReturnStatus
DataSetTable::getDataSet(DataSetDbEntry& result,
                         const std::string& datasetUuid,
                         const Axon::UserContext& userContext,
                         Axon::ErrorContainer& error)
{
    json jsonRet;
    const ReturnStatus ret = getDataSet(jsonRet, datasetUuid, userContext, true, error);
    if (ret != OK) {
        return ret;
    }

    result. = jsonRet[""];
    result.ownerId = jsonRet["owner_id"];
    result.projectId = jsonRet["project_id"];
    result.uuid = jsonRet["uuid"];
    result.visibility = jsonRet["visibility"];
    result.location = jsonRet["location"];
    result.createdAt = jsonRet["created_at"];

    return OK;
}

/**
 * @brief get a metadata-entry for a specific dataset from the database
 *
 * @param result reference for the result-output
 * @param datasetUuid uuid of the data
 * @param userContext context-object with all user specific information
 * @param showHiddenValues set to true to also show as hidden marked fields
 * @param error reference for error-output
 *
 * @return OK if found, INVALID_INPUT if not found, ERROR in case of internal error
 */
ReturnStatus
DataSetTable::getDataSet(json& result,
                         const std::string& datasetUuid,
                         const Axon::UserContext& userContext,
                         const bool showHiddenValues,
                         Axon::ErrorContainer& error)
{
    // get user from db
    std::vector<RequestCondition> conditions;
    conditions.emplace_back("uuid", datasetUuid);

    // get dataset from db
    const ReturnStatus ret
        = getWithContext(result, userContext, conditions, showHiddenValues, error);
    if (ret != OK) {
        error.addMessage("Failed to get dataset with UUID '" + datasetUuid + "' from database");
        return ret;
    }

    return OK;
}

/**
 * @brief get metadata of all datasets from the database
 *
 * @param result reference for the result-output
 * @param userContext context-object with all user specific information
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
DataSetTable::getAllDataSet(Axon::TableItem& result,
                            const Axon::UserContext& userContext,
                            Axon::ErrorContainer& error)
{
    std::vector<RequestCondition> conditions;
    if (getAllWithContext(result, userContext, conditions, error, false) != OK) {
        error.addMessage("Failed to get all datasets from database");
        return false;
    }

    return true;
}

/**
 * @brief delete metadata of a datasett from the database
 *
 * @param datasetUuid uuid of the data
 * @param userContext context-object with all user specific information
 * @param error reference for error-output
 *
 * @return OK if found, INVALID_INPUT if not found, ERROR in case of internal error
 */
ReturnStatus
DataSetTable::deleteDataSet(const std::string& datasetUuid,
                            const Axon::UserContext& userContext,
                            Axon::ErrorContainer& error)
{
    std::vector<RequestCondition> conditions;
    conditions.emplace_back("uuid", datasetUuid);

    const ReturnStatus ret = deleteFromDbWithContext(conditions, userContext, error);
    if (ret != OK) {
        error.addMessage("Failed to delete dataset with UUID '" + datasetUuid + "' from database");
        return ret;
    }

    return OK;
}
