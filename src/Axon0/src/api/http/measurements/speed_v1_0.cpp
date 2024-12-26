/**
 * @file        speed_v1_0.cpp
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

#include "speed_v1_0.h"

#include <Axon_hardware/speed_measuring.h>
#include <Axon_root.h>

SpeedV1M0::SpeedV1M0() : Blossom("Request the speed of the CPU")
{
    //----------------------------------------------------------------------------------------------
    // output
    //----------------------------------------------------------------------------------------------

    registerOutputField("current_speed", SAKURA_MAP_TYPE)
        .setComment("Json-object with current-speed-measurements");

    //----------------------------------------------------------------------------------------------
    //
    //----------------------------------------------------------------------------------------------
}

/**
 * @brief runTask
 */
bool
SpeedV1M0::runTask(BlossomIO& blossomIO,
                   const Axon::UserContext&,
                   BlossomStatus&,
                   Axon::ErrorContainer&)
{
    blossomIO.output["current_speed"] = SpeedMeasuring::getInstance()->getJson();

    return true;
}
