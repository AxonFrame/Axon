/**
 * @file        temperature_production_v1_0.cpp
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

#include "temperature_production_v1_0.h"

#include <Axon_hardware/temperature_measuring.h>
#include <Axon_root.h>

ThermalProductionV1M0::ThermalProductionV1M0()
    : Blossom("Request the temperature-measurement of the CPU")
{
    //----------------------------------------------------------------------------------------------
    // output
    //----------------------------------------------------------------------------------------------

    registerOutputField("temperature", SAKURA_MAP_TYPE)
        .setComment("Json-object with temperature-measurements");

    //----------------------------------------------------------------------------------------------
    //
    //----------------------------------------------------------------------------------------------
}

/**
 * @brief runTask
 */
bool
ThermalProductionV1M0::runTask(BlossomIO& blossomIO,
                               const Axon::UserContext&,
                               BlossomStatus&,
                               Axon::ErrorContainer&)
{
    blossomIO.output["temperature"] = TemperatureMeasuring::getInstance()->getJson();

    return true;
}
