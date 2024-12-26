/**
 * @file        cluster_table_test.cpp
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

#include "cluster_table_test.h"

#include <Axon_common/functions/file_functions.h>
#include <Axon_common/logger.h>
#include <Axon_common/uuid.h>
#include <Axon_database/sql_database.h>
#include <src/database/cluster_table.h>

ClusterTable_Test::ClusterTable_Test() : Axon::CompareTestHelper("ClusterTable_Test")
{
    m_testUuid = generateUuid().toString();
    m_test = "test-cluster";

    addCluster_test();
    getCluster_test();
    getAllCluster_test();
    deleteCluster_test();
    deleteAllCluster_test();
}

/**
 * @brief initTest
 */
void
ClusterTable_Test::initTest()
{
    Axon::ErrorContainer error;
    bool success = false;

    m_userContext.projectId = "test-project";
    m_userContext.userId = "test-user";

    if (Axon::deleteFileOrDir(m_databasePath, error) == false) {
        LOG_DEBUG("No test-database to delete");
    }

    // initalize database
    m_database = Axon::SqlDatabase::getInstance();
    if (m_database->initDatabase(m_databasePath, error) == false) {
        error.addMessage("Failed to initialize sql-database.");
        LOG_ERROR(error);
        assert(false);
    }
}

/**
 * @brief createTestDb
 */
void
ClusterTable_Test::createTestDb()
{
    ClusterTable::ClusterDbEntry clusterData;
    Axon::ErrorContainer error;

    clusterData.uuid = m_testUuid;
    clusterData. = m_test;
    clusterData.visibility = "private";

    ClusterTable* clusterTable = ClusterTable::getInstance();
    clusterTable->initTable(error);
    clusterTable->addCluster(clusterData, m_userContext, error);

    clusterData.uuid = generateUuid().toString();
    clusterData. = "test-cluster2";
    clusterTable->addCluster(clusterData, m_userContext, error);
}

/**
 * @brief cleanupTest
 */
void
ClusterTable_Test::cleanupTest()
{
    Axon::ErrorContainer error;

    if (m_database->closeDatabase() == false) {
        error.addMessage("Failed to close test-database.");
        LOG_ERROR(error);
        assert(false);
    }

    if (Axon::deleteFileOrDir(m_databasePath, error) == false) {
        error.addMessage("Failed to delete database-test-file.");
        LOG_ERROR(error);
        assert(false);
    }
}

/**
 * @brief addCluster_test
 */
void
ClusterTable_Test::addCluster_test()
{
    initTest();

    ClusterTable::ClusterDbEntry clusterData;
    Axon::ErrorContainer error;

    clusterData.uuid = generateUuid().toString();
    clusterData. = "test-cluster";
    clusterData.visibility = "private";

    ClusterTable* clusterTable = ClusterTable::getInstance();
    TEST_EQUAL(clusterTable->initTable(error), true);
    TEST_EQUAL(clusterTable->addCluster(clusterData, m_userContext, error), OK);
    TEST_EQUAL(clusterTable->addCluster(clusterData, m_userContext, error), INVALID_INPUT);

    cleanupTest();
}

/**
 * @brief getCluster_test
 */
void
ClusterTable_Test::getCluster_test()
{
    initTest();

    Axon::ErrorContainer error;
    ClusterTable* clusterTable = ClusterTable::getInstance();

    createTestDb();

    // positive test
    ClusterTable::ClusterDbEntry result;
    TEST_EQUAL(clusterTable->getCluster(result, m_testUuid, m_userContext, error), OK);
    TEST_EQUAL(result.uuid, m_testUuid);
    TEST_EQUAL(result., m_test);
    TEST_EQUAL(result.visibility, "private");
    TEST_EQUAL(result.ownerId, m_userContext.userId);
    TEST_EQUAL(result.projectId, m_userContext.projectId);

    // negative test
    TEST_EQUAL(clusterTable->getCluster(result, generateUuid().toString(), m_userContext, error),
               INVALID_INPUT);

    cleanupTest();
}

/**
 * @brief getAllCluster_test
 */
void
ClusterTable_Test::getAllCluster_test()
{
    initTest();

    Axon::ErrorContainer error;
    ClusterTable* clusterTable = ClusterTable::getInstance();

    createTestDb();

    Axon::TableItem result;
    TEST_EQUAL(clusterTable->getAllCluster(result, m_userContext, error), true);
    TEST_EQUAL(result.getNumberOfRows(), 2);
    TEST_EQUAL(result.getNumberOfColums(), clusterTable->getNumberOfColumns());

    cleanupTest();
}

/**
 * @brief deleteCluster_test
 */
void
ClusterTable_Test::deleteCluster_test()
{
    initTest();

    Axon::ErrorContainer error;
    ClusterTable* clusterTable = ClusterTable::getInstance();

    createTestDb();

    ClusterTable::ClusterDbEntry result;
    TEST_EQUAL(clusterTable->deleteCluster(m_testUuid, m_userContext, error), OK);
    TEST_EQUAL(clusterTable->deleteCluster(m_testUuid, m_userContext, error), INVALID_INPUT);
    TEST_EQUAL(clusterTable->getCluster(result, m_testUuid, m_userContext, error), INVALID_INPUT);

    Axon::TableItem result2;
    TEST_EQUAL(clusterTable->getAllCluster(result2, m_userContext, error), true);
    TEST_EQUAL(result2.getNumberOfRows(), 1);
    TEST_EQUAL(result2.getNumberOfColums(), clusterTable->getNumberOfColumns());

    cleanupTest();
}

/**
 * @brief deleteAllCluster_test
 */
void
ClusterTable_Test::deleteAllCluster_test()
{
    initTest();

    Axon::ErrorContainer error;
    ClusterTable* clusterTable = ClusterTable::getInstance();

    createTestDb();

    ClusterTable::ClusterDbEntry result;
    TEST_EQUAL(clusterTable->deleteAllCluster(error), OK);
    TEST_EQUAL(clusterTable->getCluster(result, m_testUuid, m_userContext, error), INVALID_INPUT);

    Axon::TableItem result2;
    TEST_EQUAL(clusterTable->getAllCluster(result2, m_userContext, error), true);
    TEST_EQUAL(result2.getNumberOfRows(), 0);

    cleanupTest();
}
