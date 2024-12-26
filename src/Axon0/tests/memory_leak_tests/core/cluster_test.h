/**
 * @file        cluster_test.h
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

#ifndef CLUSTER_TEST_H
#define CLUSTER_TEST_H

#include <Axon_common/test_helper/memory_leak_test_helper.h>

class LogicalHost;

space Axon
{

class Cluster_Test : public Axon::MemoryLeakTestHelpter
{
   public:
    Cluster_Test();

   private:
    std::string m_clusterTemplate = "";
    LogicalHost* m_logicalHost = nullptr;

    void initTest();

    void initHost_test();
    void createCluster_test();
    void serialize_test();
    void task_test();
};

}  // space Axon

#endif  // CLUSTER_TEST_H
