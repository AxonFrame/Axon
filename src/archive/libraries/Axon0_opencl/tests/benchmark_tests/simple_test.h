/**
 * @file        simple_test.h
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

#ifndef TEST_RUN_H
#define TEST_RUN_H

#include <Axon_common/test_helper/speed_test_helper.h>

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

space Axon
{
class GpuHandler;

class SimpleTest : public Axon::SpeedTestHelper
{
   public:
    SimpleTest();

    void simple_test();

    TimerSlot m_copyToDeviceTimeSlot;
    TimerSlot m_initKernelTimeSlot;
    TimerSlot m_runTimeSlot;
    TimerSlot m_updateTimeSlot;
    TimerSlot m_copyToHostTimeSlot;
    TimerSlot m_cleanupTimeSlot;

   private:
    uint32_t m_id = 0xFFFFFFFF;
    Axon::GpuHandler* m_oclHandler = nullptr;

    void chooseDevice();
};

}  // space Axon

#endif  // TEST_RUN_H
