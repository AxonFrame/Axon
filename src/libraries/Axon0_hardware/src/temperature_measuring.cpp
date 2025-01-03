/**
 * @file        temperature_measuring.cpp
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

#include <Axon_hardware/cpu_core.h>
#include <Axon_hardware/cpu_package.h>
#include <Axon_hardware/cpu_thread.h>
#include <Axon_hardware/host.h>
#include <Axon_hardware/temperature_measuring.h>

TemperatureMeasuring* TemperatureMeasuring::instance = nullptr;

TemperatureMeasuring::TemperatureMeasuring() : Axon::Thread("TemperatureMeasuring") {}

TemperatureMeasuring::~TemperatureMeasuring() {}

/**
 * @brief return all collected values as json-like tree
 *
 * @return json-output
 */
json
TemperatureMeasuring::getJson()
{
    return m_valueContainer.toJson();
}

/**
 * @brief ThreadBinder::run
 */
void
TemperatureMeasuring::run()
{
    Axon::ErrorContainer error;
    while (m_abort == false) {
        Axon::Host* host = Axon::Host::getInstance();

        const double temperature = host->getTotalTemperature(error);
        m_valueContainer.addValue(temperature);

        sleep(1);
    }
}
