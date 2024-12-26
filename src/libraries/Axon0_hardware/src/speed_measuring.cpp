/**
 * @file        speed_measuring.cpp
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
#include <Axon_hardware/speed_measuring.h>

SpeedMeasuring* SpeedMeasuring::instance = nullptr;

SpeedMeasuring::SpeedMeasuring() : Axon::Thread("SpeedMeasuring") {}

SpeedMeasuring::~SpeedMeasuring() {}

/**
 * @brief return all collected values as json-like tree
 *
 * @return json-output
 */
json
SpeedMeasuring::getJson()
{
    return m_valueContainer.toJson();
}

/**
 * @brief ThreadBinder::run
 */
void
SpeedMeasuring::run()
{
    Axon::ErrorContainer error;
    Axon::CpuThread* thread = nullptr;

    while (m_abort == false) {
        uint64_t currentSpeed = 0;
        uint64_t numberOfValues = 0;
        Axon::Host* host = Axon::Host::getInstance();

        for (uint64_t i = 0; i < host->cpuPackages.size(); i++) {
            for (uint64_t j = 0; j < host->getPackage(i)->cpuCores.size(); j++) {
                numberOfValues++;
                thread = host->getPackage(i)->cpuCores.at(j)->cpuThreads.at(0);
                currentSpeed += thread->getCurrentThreadSpeed();
            }
        }

        if (currentSpeed != 0 && numberOfValues != 0) {
            double curSpeed
                = static_cast<double>(currentSpeed) / static_cast<double>(numberOfValues);
            curSpeed /= 1000.0;  // convert from KHz to MHz
            m_valueContainer.addValue(curSpeed);
        }
        else {
            m_valueContainer.addValue(0.0);
        }

        sleep(1);
    }
}
