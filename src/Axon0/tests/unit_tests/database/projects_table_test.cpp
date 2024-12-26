/**
 * @file        project_table_test.cpp
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

#include "projects_table_test.h"

#include <Axon_common/functions/file_functions.h>
#include <Axon_common/logger.h>
#include <Axon_common/uuid.h>
#include <Axon_database/sql_database.h>
#include <src/database/projects_table.h>

ProjectTable_Test::ProjectTable_Test() : Axon::CompareTestHelper("ProjectTable_Test")
{
    m_testId = "test-id";
    m_test = "test-project";

    addProject_test();
    getProject_test();
    getAllProject_test();
    deleteProject_test();
}

/**
 * @brief initTest
 */
void
ProjectTable_Test::initTest()
{
    Axon::ErrorContainer error;
    bool success = false;

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
ProjectTable_Test::createTestDb()
{
    ProjectTable::ProjectDbEntry projectData;
    Axon::ErrorContainer error;

    projectData.id = m_testId;
    projectData. = m_test;
    projectData.creatorId = m_testId;

    ProjectTable* projectTable = ProjectTable::getInstance();
    projectTable->initTable(error);
    projectTable->addProject(projectData, error);

    projectData.id = "test-id2";
    projectData. = "test-project2";
    projectTable->addProject(projectData, error);
}

/**
 * @brief cleanupTest
 */
void
ProjectTable_Test::cleanupTest()
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
 * @brief addProject_test
 */
void
ProjectTable_Test::addProject_test()
{
    initTest();

    ProjectTable::ProjectDbEntry projectData;
    Axon::ErrorContainer error;

    projectData.id = m_testId;
    projectData. = m_test;
    projectData.creatorId = m_testId;

    ProjectTable* projectTable = ProjectTable::getInstance();
    TEST_EQUAL(projectTable->initTable(error), true);
    TEST_EQUAL(projectTable->addProject(projectData, error), OK);
    TEST_EQUAL(projectTable->addProject(projectData, error), INVALID_INPUT);

    cleanupTest();
}

/**
 * @brief getProject_test
 */
void
ProjectTable_Test::getProject_test()
{
    initTest();

    Axon::ErrorContainer error;
    ProjectTable* projectTable = ProjectTable::getInstance();

    createTestDb();

    // positive test
    ProjectTable::ProjectDbEntry result;
    TEST_EQUAL(projectTable->getProject(result, m_testId, error), OK);
    TEST_EQUAL(result.id, m_testId);
    TEST_EQUAL(result., m_test);
    TEST_EQUAL(result.creatorId, m_testId);

    // negative test
    TEST_EQUAL(projectTable->getProject(result, "fail", error), INVALID_INPUT);

    cleanupTest();
}

/**
 * @brief getAllProject_test
 */
void
ProjectTable_Test::getAllProject_test()
{
    initTest();

    Axon::ErrorContainer error;
    ProjectTable* projectTable = ProjectTable::getInstance();

    createTestDb();

    Axon::TableItem result;
    TEST_EQUAL(projectTable->getAllProjects(result, error), true);
    TEST_EQUAL(result.getNumberOfRows(), 2);
    TEST_EQUAL(result.getNumberOfColums(), projectTable->getNumberOfColumns());

    cleanupTest();
}

/**
 * @brief deleteProject_test
 */
void
ProjectTable_Test::deleteProject_test()
{
    initTest();

    Axon::ErrorContainer error;
    ProjectTable* projectTable = ProjectTable::getInstance();

    createTestDb();

    ProjectTable::ProjectDbEntry result;
    TEST_EQUAL(projectTable->deleteProject(m_testId, error), OK);
    TEST_EQUAL(projectTable->deleteProject(m_testId, error), INVALID_INPUT);
    TEST_EQUAL(projectTable->getProject(result, m_testId, error), INVALID_INPUT);

    Axon::TableItem result2;
    TEST_EQUAL(projectTable->getAllProjects(result2, error), true);
    TEST_EQUAL(result2.getNumberOfRows(), 1);
    TEST_EQUAL(result2.getNumberOfColums(), projectTable->getNumberOfColumns());

    cleanupTest();
}
