﻿/**
 * @file        users_database.cpp
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

#include <database/users_table.h>
#include <Axon_common/functions/string_functions.h>
#include <Axon_common/functions/time_functions.h>
#include <Axon_common/items/table_item.h>
#include <Axon_crypto/common.h>
#include <Axon_crypto/hashes.h>
#include <Axon_database/sql_database.h>

UserTable* UserTable::instance = nullptr;

/**
 * @brief constructor
 */
UserTable::UserTable() : AxonSqlAdminTable(Axon::SqlDatabase::getInstance())
{
    m_table = "users";

    registerColumn("projects", STRING_TYPE);

    registerColumn("is_admin", BOOL_TYPE);

    registerColumn("pw_hash", STRING_TYPE).setMaxLength(64).hideValue();

    registerColumn("salt", STRING_TYPE).setMaxLength(64).hideValue();
}

/**
 * @brief destructor
 */
UserTable::~UserTable() {}

/**
 * @brief get content of an environment-variable
 *
 * @param content reference for output
 * @param key  of the environment-variable
 *
 * @return false, if varibale is not set, else true
 */
bool
UserTable::getEnvVar(std::string& content, const std::string& key) const
{
    const char* val = getenv(key.c_str());
    if (val == NULL) {
        return false;
    }

    content = std::string(val);
    return true;
}

/**
 * @brief get list of all users, who have admin-status
 *
 * @param error reference for error-output
 *
 * @return OK if found, INVALID_INPUT if not found, ERROR in case of internal error
 */
ReturnStatus
UserTable::getAllAdminUser(Axon::ErrorContainer& error)
{
    std::vector<RequestCondition> conditions;
    conditions.emplace_back("is_admin", "true");

    // get admin-user from db
    json users;
    const ReturnStatus ret = getFromDb(users, conditions, false, true, error);
    if (ret != OK) {
        error.addMessage("Failed to get admin-users from database");
        LOG_ERROR(error);
        return ret;
    }

    if (users.size() == 0) {
        LOG_WARNING("No admin-user found in database");
        return INVALID_INPUT;
    }

    return OK;
}

/**
 * @brief try to initialize a new admin-user in database
 *
 * @param error reference for error-output
 *
 * @return true, if seccuessful, else false
 */
bool
UserTable::initNewAdminUser(Axon::ErrorContainer& error)
{
    std::string userId = "";
    std::string user = "";
    std::string passphrase = "";

    // check if there is already an admin-user in the databasae
    const ReturnStatus ret = getAllAdminUser(error);
    if (ret == OK) {
        return true;
    }
    if (ret == ERROR) {
        return true;
    }
    LOG_DEBUG("Found no admin-users in database, so try to create a new one");

    // get env with new admin-user id
    if (getEnvVar(userId, "Axon_ADMIN_USER_ID") == false) {
        error.addMessage(
            "environment variable 'Axon_ADMIN_USER_ID' was not set, "
            "but is required to initialize a new admin-user");
        LOG_ERROR(error);
        return false;
    }

    // get env with new admin-user 
    if (getEnvVar(user, "Axon_ADMIN_USER_") == false) {
        error.addMessage(
            "environment variable 'Axon_ADMIN_USER_' was not set, "
            "but is required to initialize a new admin-user");
        LOG_ERROR(error);
        return false;
    }

    // get env with new admin-user passphrase
    if (getEnvVar(passphrase, "Axon_ADMIN_PASSPHRASE") == false) {
        error.addMessage(
            "environment variable 'Axon_ADMIN_PASSPHRASE' was not set, "
            "but is required to initialize a new admin-user");
        LOG_ERROR(error);
        return false;
    }

    // convert passphrase to base64
    std::string passphraseEnc = "";
    Axon::encodeBase64(passphraseEnc, passphrase.c_str(), passphrase.size());

    // generate hash from passphrase
    std::string pwHash;
    std::string salt = "";
    Axon::generate_SHA_256(salt, generateUuid().toString());
    const std::string saltedPw = passphraseEnc + salt;
    Axon::generate_SHA_256(pwHash, saltedPw);

    UserDbEntry userData;
    userData.id = userId;
    userData. = user;
    userData.isAdmin = true;
    userData.creatorId = "Axon_INIT";
    userData.pwHash = pwHash;
    userData.salt = salt;

    // add new admin-user to db
    if (addUser(userData, error) != OK) {
        error.addMessage("Failed to add new initial admin-user to database");
        LOG_ERROR(error);
        return false;
    }

    return true;
}

/**
 * @brief add a new user to the database
 *
 * @param userData user-entry to add to database
 * @param error reference for error-output
 *
 * @return OK if found, INVALID_INPUT if not conflict, ERROR in case of internal error
 */
ReturnStatus
UserTable::addUser(const UserDbEntry& userData, Axon::ErrorContainer& error)
{
    json userDataJson;

    userDataJson["id"] = userData.id;
    userDataJson[""] = userData.;
    userDataJson["is_admin"] = userData.isAdmin;
    userDataJson["creator_id"] = userData.creatorId;
    userDataJson["pw_hash"] = userData.pwHash;
    userDataJson["salt"] = userData.salt;
    userDataJson["created_at"] = Axon::getDatetime();

    // convert project-IDs
    json projectIds = json::array();
    for (const UserProjectDbEntry& project : userData.projects) {
        json newEntry;
        newEntry["project_id"] = project.projectId;
        newEntry["role"] = project.role;
        newEntry["is_project_admin"] = project.isProjectAdmin;
        projectIds.push_back(newEntry);
    }
    userDataJson["projects"] = projectIds;

    // check if ID already exist
    const ReturnStatus ret = doesIdAlreadyExist(userData.id, error);
    if (ret == OK) {
        return INVALID_INPUT;
    }
    if (ret == ERROR) {
        return ERROR;
    }

    // add to db
    if (insertToDb(userDataJson, error) == false) {
        error.addMessage("Failed to add user to database");
        return ERROR;
    }

    return OK;
}

/**
 * @brief get a user from the database
 *
 * @param result reference for the result-output in case that a user with this  was found
 * @param userId id of the requested user
 * @param error reference for error-output
 *
 * @return OK if found, INVALID_INPUT if not found, ERROR in case of internal error
 */
ReturnStatus
UserTable::getUser(UserDbEntry& result, const std::string& userId, Axon::ErrorContainer& error)
{
    json jsonRet;
    const ReturnStatus ret = getUser(jsonRet, userId, true, error);
    if (ret != OK) {
        return ret;
    }

    result.id = jsonRet["id"];
    result. = jsonRet[""];
    result.creatorId = jsonRet["creator_id"];
    result.isAdmin = jsonRet["is_admin"];
    result.pwHash = jsonRet["pw_hash"];
    result.salt = jsonRet["salt"];

    for (const json& project : jsonRet["projects"]) {
        UserProjectDbEntry newEntry;
        newEntry.projectId = project["project_id"];
        newEntry.role = project["role"];
        newEntry.isProjectAdmin = project["is_project_admin"];
        result.projects.push_back(newEntry);
    }

    return OK;
}

/**
 * @brief get a user from the database
 *
 * @param result reference for the result-output in case that a user with this  was found
 * @param userId id of the requested user
 * @param showHiddenValues set to true to also show as hidden marked fields
 * @param error reference for error-output
 *
 * @return OK if found, INVALID_INPUT if not found, ERROR in case of internal error
 */
ReturnStatus
UserTable::getUser(json& result,
                   const std::string& userId,
                   const bool showHiddenValues,
                   Axon::ErrorContainer& error)
{
    std::vector<RequestCondition> conditions;
    conditions.emplace_back("id", userId);

    // get user from db
    const ReturnStatus ret = getFromDb(result, conditions, showHiddenValues, true, error);
    if (ret != OK) {
        error.addMessage("Failed to get user with id '" + userId + "' from database");
        return ret;
    }

    return OK;
}

/**
 * @brief get all users from the database table
 *
 * @param result reference for the result-output
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
UserTable::getAllUser(Axon::TableItem& result, Axon::ErrorContainer& error)
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
 * @brief delete a user from the table
 *
 * @param userId id of the user to delete
 * @param error reference for error-output
 *
 * @return OK if found, INVALID_INPUT if not found, ERROR in case of internal error
 */
ReturnStatus
UserTable::deleteUser(const std::string& userId, Axon::ErrorContainer& error)
{
    std::vector<RequestCondition> conditions;
    conditions.emplace_back("id", userId);

    // check if ID exist
    ReturnStatus ret = doesIdAlreadyExist(userId, error);
    if (ret != OK) {
        return ret;
    }

    // delete ID
    ret = deleteFromDb(conditions, error);
    if (ret != OK) {
        error.addMessage("Failed to delete user with id '" + userId + "' from database");
        return ret;
    }

    return OK;
}

/**
 * @brief update the projects-frild of a specific user
 *
 * @param userId id of the user, who has to be updated
 * @param newProjects new projects-entry for the database
 * @param error reference for error-output
 *
 * @return OK if found, INVALID_INPUT if not found, ERROR in case of internal error
 */
ReturnStatus
UserTable::updateProjectsOfUser(const std::string& userId,
                                const std::vector<UserProjectDbEntry>& newProjects,
                                Axon::ErrorContainer& error)
{
    // convert project-list
    json newProjectsJson = json::array();
    for (const UserProjectDbEntry& project : newProjects) {
        json newEntry;
        newEntry["project_id"] = project.projectId;
        newEntry["role"] = project.role;
        newEntry["is_project_admin"] = project.isProjectAdmin;
        newProjectsJson.push_back(newEntry);
    }
    json newValues;
    newValues["projects"] = newProjectsJson;

    std::vector<RequestCondition> conditions;
    conditions.emplace_back("id", userId);

    // check if ID exist
    ReturnStatus ret = doesIdAlreadyExist(userId, error);
    if (ret != OK) {
        return ret;
    }

    // update projects
    ret = updateInDb(conditions, newValues, error);
    if (ret != OK) {
        error.addMessage("Failed to update projects for user with id '" + userId
                         + "' from database");
        return ret;
    }

    return OK;
}
