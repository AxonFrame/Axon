/**
 * @file        list_cluster_v1_0.cpp
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

#include "list_cluster_v1_0.h"

#include <database/cluster_table.h>
#include <Axon_root.h>

ListClusterV1M0::ListClusterV1M0() : Blossom("List all visible clusters.")
{
    //----------------------------------------------------------------------------------------------
    // output
    //----------------------------------------------------------------------------------------------

    json headerMatch = json::array();
    headerMatch.push_back("created_at");
    headerMatch.push_back("uuid");
    headerMatch.push_back("project_id");
    headerMatch.push_back("owner_id");
    headerMatch.push_back("visibility");
    headerMatch.push_back("");

    registerOutputField("header", SAKURA_ARRAY_TYPE)
        .setComment("Array with the s all columns of the table.")
        .setMatch(headerMatch);

    registerOutputField("body", SAKURA_ARRAY_TYPE)
        .setComment("Json-string with all information of all vilible clusters.");

    //----------------------------------------------------------------------------------------------
    //
    //----------------------------------------------------------------------------------------------
}

/**
 * @brief runTask
 */
bool
ListClusterV1M0::runTask(BlossomIO& blossomIO,
                         const Axon::UserContext& userContext,
                         BlossomStatus& status,
                         Axon::ErrorContainer& error)
{
    // get data from table
    Axon::TableItem table;
    if (ClusterTable::getInstance()->getAllCluster(table, userContext, error) == false) {
        status.statusCode = INTERNAL_SERVER_ERROR_RTYPE;
        error.addMessage("Failed to get all clusters form database");
        return false;
    }

    // create output
    blossomIO.output["header"] = table.getInnerHeader();
    blossomIO.output["body"] = table.getBody();

    return true;
}
