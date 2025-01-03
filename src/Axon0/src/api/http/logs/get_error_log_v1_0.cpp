/**
 * @file        get_audit_log_v1_0.cpp
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

#include "get_error_log_v1_0.h"

#include <database/error_log_table.h>
#include <Axon_root.h>

GetErrorLogV1M0::GetErrorLogV1M0()
    : Blossom("Get error-log of a user. Only an admin is allowed to request the error-log.")
{
    errorCodes.push_back(UNAUTHORIZED_RTYPE);

    //----------------------------------------------------------------------------------------------
    // input
    //----------------------------------------------------------------------------------------------
    registerInputField("user_id", SAKURA_STRING_TYPE)
        .setComment("ID of the user, whos entries are requested.")
        .setRequired(false)
        .setLimit(4, 254)
        .setRegex(ID_EXT_REGEX);

    registerInputField("page", SAKURA_INT_TYPE)
        .setComment(
            "Page-number starting with 0 to access the logs. "
            "A page has up to 100 entries.")
        .setLimit(0, 1000000000);

    //----------------------------------------------------------------------------------------------
    // output
    //----------------------------------------------------------------------------------------------

    json headerMatch = json::array();
    headerMatch.push_back("created_at");
    headerMatch.push_back("user_id");
    headerMatch.push_back("component");
    headerMatch.push_back("context");
    headerMatch.push_back("input_values");
    headerMatch.push_back("message");

    registerOutputField("header", SAKURA_ARRAY_TYPE)
        .setComment("Array with the namings all columns of the table.")
        .setMatch(headerMatch);

    registerOutputField("body", SAKURA_ARRAY_TYPE)
        .setComment("Array with all rows of the table, which array arrays too.");

    //----------------------------------------------------------------------------------------------
    //
    //----------------------------------------------------------------------------------------------
}

/**
 * @brief runTask
 */
bool
GetErrorLogV1M0::runTask(BlossomIO& blossomIO,
                         const Axon::UserContext& userContext,
                         BlossomStatus& status,
                         Axon::ErrorContainer& error)
{
    const uint64_t page = blossomIO.input["page"];

    // check that the user is an admin
    if (userContext.isAdmin == false) {
        status.statusCode = UNAUTHORIZED_RTYPE;
        status.errorMessage = "only an admin is allowed to request error-logs";
        LOG_DEBUG(status.errorMessage);
        return false;
    }

    const std::string userId = blossomIO.input.value("user_id", "");

    // get data from table
    Axon::TableItem table;
    if (ErrorLogTable::getInstance()->getAllErrorLogEntries(table, userId, page, error) == false) {
        status.statusCode = INTERNAL_SERVER_ERROR_RTYPE;
        return false;
    }

    // create output
    blossomIO.output["header"] = table.getInnerHeader();
    blossomIO.output["body"] = table.getBody();

    return true;
}
