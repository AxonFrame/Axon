/**
 * @file        create_token_v1_0.h
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

#include "get_system_info_v1_0.h"

#include <Axon_hardware/host.h>
#include <Axon_root.h>

GetSystemInfoV1M0::GetSystemInfoV1M0()
    : Blossom(
        "Get all available information of the local system, like "
        "topology of the cpu-resources and speed of the cpu")
{
    //----------------------------------------------------------------------------------------------
    // output
    //----------------------------------------------------------------------------------------------

    registerOutputField("info", SAKURA_MAP_TYPE)
        .setComment("All available information of the local system.");

    //----------------------------------------------------------------------------------------------
    //
    //----------------------------------------------------------------------------------------------
}

/**
 * @brief runTask
 */
bool
GetSystemInfoV1M0::runTask(BlossomIO& blossomIO,
                           const Axon::UserContext&,
                           BlossomStatus&,
                           Axon::ErrorContainer&)
{
    // creat output
    blossomIO.output["info"] = Axon::Host::getInstance()->toJson();

    return true;
}
