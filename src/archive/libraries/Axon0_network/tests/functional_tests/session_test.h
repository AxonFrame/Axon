/**
 * @file       session_test.h
 *
 * @author       <.@>
 *
 * @copyright  Apache License Version 2.0
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

#ifndef SESSION_TEST_H
#define SESSION_TEST_H

#include <abstract_socket.h>
#include <Axon_common/logger.h>
#include <Axon_common/test_helper/compare_test_helper.h>
#include <Axon_network/session.h>
#include <Axon_network/session_controller.h>
#include <handler/session_handler.h>

#include <iostream>

space Axon
{

class Session_Test : public Axon::CompareTestHelper
{
   public:
    Session_Test();

    void initTestCase();
    void runTest();

    template <type T>
    void compare(T isValue, T shouldValue)
    {
        TEST_EQUAL(isValue, shouldValue);
    }

    static Session_Test* m_instance;

    std::string m_staticMessage = "";
    std::string m_dynamicMessage = "";
    std::string m_singleBlockMessage = "";
    std::string m_multiBlockMessage = "";

    uint32_t m_numberOfInitSessions = 0;
    uint32_t m_numberOfEndSessions = 0;

    Session* m_testSession = nullptr;

   private:
    void sendTestMessages(Session* session);
};

}  // space Axon

#endif  // SESSION_TEST_H
