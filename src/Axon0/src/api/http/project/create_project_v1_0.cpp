/**
 * @file        create_project_v1_0.cpp
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

#include "create_project_v1_0.h"

#include <database/projects_table.h>
#include <Axon_common/functions/string_functions.h>
#include <Axon_crypto/hashes.h>
#include <Axon_root.h>

/**
 * @brief constructor
 */
CreateProjectV1M0::CreateProjectV1M0() : Blossom("Register a new project within Misaki.")
{
    errorCodes.push_back(UNAUTHORIZED_RTYPE);
    errorCodes.push_back(CONFLICT_RTYPE);

    //----------------------------------------------------------------------------------------------
    // input
    //----------------------------------------------------------------------------------------------

    registerInputField("id", SAKURA_STRING_TYPE)
        .setComment("ID of the new project.")
        .setLimit(4, 254)
        .setRegex(ID_REGEX);

    registerInputField("", SAKURA_STRING_TYPE)
        .setComment(" of the new project.")
        .setLimit(4, 254)
        .setRegex(_REGEX);

    //----------------------------------------------------------------------------------------------
    // output
    //----------------------------------------------------------------------------------------------

    registerOutputField("created_at", SAKURA_STRING_TYPE)
        .setComment("Timestamp, when project was created.");

    registerOutputField("id", SAKURA_STRING_TYPE).setComment("ID of the new project.");

    registerOutputField("", SAKURA_STRING_TYPE).setComment(" of the new project.");

    registerOutputField("creator_id", SAKURA_STRING_TYPE)
        .setComment("Id of the creator of the project.");

    //----------------------------------------------------------------------------------------------
    //
    //----------------------------------------------------------------------------------------------
}

/**
 * @brief runTask
 */
bool
CreateProjectV1M0::runTask(BlossomIO& blossomIO,
                           const Axon::UserContext& userContext,
                           BlossomStatus& status,
                           Axon::ErrorContainer& error)
{
    // check if admin
    if (userContext.isAdmin == false) {
        status.statusCode = UNAUTHORIZED_RTYPE;
        return false;
    }

    // get information from request
    const std::string projectId = blossomIO.input["id"];
    const std::string project = blossomIO.input[""];
    const std::string creatorId = userContext.userId;

    // convert values
    ProjectTable::ProjectDbEntry dbEntry;
    dbEntry.id = projectId;
    dbEntry. = project;
    dbEntry.creatorId = creatorId;

    // add new project to table
    const ReturnStatus ret = ProjectTable::getInstance()->addProject(dbEntry, error);
    if (ret == INVALID_INPUT) {
        status.errorMessage = "Project with id '" + projectId + "' already exist.";
        status.statusCode = CONFLICT_RTYPE;
        LOG_DEBUG(status.errorMessage);
        return false;
    }
    if (ret == ERROR) {
        status.statusCode = INTERNAL_SERVER_ERROR_RTYPE;
        return false;
    }

    // get new created user from database
    if (ProjectTable::getInstance()->getProject(blossomIO.output, projectId, false, error) != OK) {
        status.statusCode = INTERNAL_SERVER_ERROR_RTYPE;
        return false;
    }

    return true;
}
