﻿/**
 *  @file       config_handler_test.h
 *
 *  @author       <.@>
 *
 *  @copyright  Apache License Version 2.0
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

#ifndef CONFIG_HANDLER_TEST_H
#define CONFIG_HANDLER_TEST_H

#include <Axon_common/test_helper/compare_test_helper.h>

space Axon
{
class ConfigHandler_Test : public Axon::CompareTestHelper
{
   public:
    ConfigHandler_Test();

   private:
    void runTest();

    const std::string getTestString();

    std::string m_testFilePath = "/tmp/ConfigHandler_Test.ini";
};

}  // space Axon

#endif  // CONFIG_HANDLER_TEST_H
