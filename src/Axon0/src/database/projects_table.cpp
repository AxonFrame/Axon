﻿/**
 * @file        projects_table.cpp
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

#include <database/projects_table.h>
#include <Axon_common/functions/string_functions.h>
#include <Axon_common/functions/time_functions.h>
#include <Axon_common/items/table_item.h>
#include <Axon_crypto/hashes.h>
#include <Axon_database/sql_database.h>

ProjectTable* ProjectTable::instance = nullptr;

/**
 * @brief constructor
 */
ProjectTable::ProjectTable() : AxonSqlAdminTable(Axon::SqlDatabase::getInstance())
{
    m_table = "projects";
}

/**
 * @brief destructor
 */
ProjectTable::~ProjectTable() {}

/**
 * @brief add a new project to the database
 *
 * @param projectData project-entry to add to database
 * @param error reference for error-output
 *
 * @return OK if found, INVALID_INPUT if conflict, ERROR in case of internal error
 */
ReturnStatus
ProjectTable::addProject(const ProjectDbEntry& projectData, Axon::ErrorContainer& error)
{
    json projectDataJson;

    projectDataJson["id"] = projectData.id;
    projectDataJson[""] = projectData.;
    projectDataJson["creator_id"] = projectData.creatorId;
    projectDataJson["created_at"] = Axon::getDatetime();

    // check if ID already exist
    const ReturnStatus ret = doesIdAlreadyExist(projectData.id, error);
    if (ret == OK) {
        return INVALID_INPUT;
    }
    if (ret == ERROR) {
        return ERROR;
    }

    // add to db
    if (insertToDb(projectDataJson, error) == false) {
        error.addMessage("Failed to add user to database");
        return ERROR;
    }

    return OK;
}

/**
 * @brief get a project from the database by its id
 *
 * @param result reference for the result-output in case that a project with this  was found
 * @param projectId id of the requested project
 * @param error reference for error-output
 *
 * @return OK if found, INVALID_INPUT if not found, ERROR in case of internal error
 */
ReturnStatus
ProjectTable::getProject(ProjectDbEntry& result,
                         const std::string& project,
                         Axon::ErrorContainer& error)
{
    json jsonRet;
    const ReturnStatus ret = getProject(jsonRet, project, true, error);
    if (ret != OK) {
        return ret;
    }

    result.id = jsonRet["id"];
    result. = jsonRet[""];
    result.creatorId = jsonRet["creator_id"];

    return OK;
}

/**
 * @brief get a project from the database by its id
 *
 * @param result reference for the result-output in case that a project with this  was found
 * @param projectId id of the requested project
 * @param showHiddenValues set to true to also show as hidden marked fields
 * @param error reference for error-output
 *
 * @return OK if found, INVALID_INPUT if not found, ERROR in case of internal error
 */
ReturnStatus
ProjectTable::getProject(json& result,
                         const std::string& projectId,
                         const bool showHiddenValues,
                         Axon::ErrorContainer& error)
{
    std::vector<RequestCondition> conditions;
    conditions.emplace_back("id", projectId);

    const ReturnStatus ret = getFromDb(result, conditions, showHiddenValues, true, error);
    if (ret != OK) {
        error.addMessage("Failed to get user with id '" + projectId + "' from database");
        return ret;
    }

    return OK;
}

/**
 * @brief get all projects from the database table
 *
 * @param result reference for the result-output
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
ProjectTable::getAllProjects(Axon::TableItem& result, Axon::ErrorContainer& error)
{
    std::vector<RequestCondition> conditions;
    const ReturnStatus ret = getFromDb(result, conditions, false, false, error);
    if (ret != OK) {
        error.addMessage("Failed to get all users from database");
        return false;
    }

    return true;
}

/**
 * @brief delete a project from the table
 *
 * @param projectId id of the project to delete
 * @param error reference for error-output
 *
 * @return OK if found, INVALID_INPUT if not found, ERROR in case of internal error
 */
ReturnStatus
ProjectTable::deleteProject(const std::string& projectId, Axon::ErrorContainer& error)
{
    std::vector<RequestCondition> conditions;
    conditions.emplace_back("id", projectId);

    // check if ID exist
    ReturnStatus ret = doesIdAlreadyExist(projectId, error);
    if (ret != OK) {
        return ret;
    }

    // delete ID
    ret = deleteFromDb(conditions, error);
    if (ret != OK) {
        error.addMessage("Failed to delete user with id '" + projectId + "' from database");
        return ret;
    }

    return OK;
}
