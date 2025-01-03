/**
 * @file        list_hosts_v1_0.cpp
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

#include "list_hosts_v1_0.h"

#include <core/processing/physical_host.h>
#include <Axon_root.h>

ListHostsV1M0::ListHostsV1M0() : Blossom("List all logical hosts.")
{
    //----------------------------------------------------------------------------------------------
    // output
    //----------------------------------------------------------------------------------------------

    json headerMatch = json::array();
    headerMatch.push_back("uuid");
    headerMatch.push_back("type");

    registerOutputField("header", SAKURA_ARRAY_TYPE)
        .setComment("Array with the s all columns of the table.")
        .setMatch(headerMatch);

    registerOutputField("body", SAKURA_ARRAY_TYPE)
        .setComment("Json-string with all information of all vilible hosts.");

    //----------------------------------------------------------------------------------------------
    //
    //----------------------------------------------------------------------------------------------
}

/**
 * @brief runTask
 */
bool
ListHostsV1M0::runTask(BlossomIO& blossomIO,
                       const Axon::UserContext& userContext,
                       BlossomStatus& status,
                       Axon::ErrorContainer& error)
{
    // prepare header
    json header = json::array();
    header.push_back("uuid");
    header.push_back("type");

    // get data from table
    const json body = AxonRoot::physicalHost->getAllHostsAsJson();

    // create output
    blossomIO.output["header"] = header;
    blossomIO.output["body"] = body;

    return true;
}
