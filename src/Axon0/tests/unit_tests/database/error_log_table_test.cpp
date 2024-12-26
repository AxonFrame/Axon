/**
 * @file        error_log_table_test.cpp
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

#include "error_log_table_test.h"

#include <Axon_common/functions/file_functions.h>
#include <Axon_common/logger.h>
#include <Axon_common/uuid.h>
#include <Axon_database/sql_database.h>
#include <src/database/error_log_table.h>

ErrorLogTable_Test::ErrorLogTable_Test() : Axon::CompareTestHelper("ErrorLogTable_Test")
{
    addErrorLog_test();
    getAllErrorLog_test();
}

/**
 * @brief initTest
 */
void
ErrorLogTable_Test::initTest()
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
 * @brief cleanupTest
 */
void
ErrorLogTable_Test::cleanupTest()
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
 * @brief addErrorLog_test
 */
void
ErrorLogTable_Test::addErrorLog_test()
{
    initTest();

    Axon::ErrorContainer error;

    ErrorLogTable* errorLogTable = ErrorLogTable::getInstance();
    TEST_EQUAL(errorLogTable->initTable(error), true);
    TEST_EQUAL(
        errorLogTable->addErrorLogEntry(
            "test-user", "Axon", "example-context", "values", "this is a test-message", error),
        true);
    TEST_EQUAL(
        errorLogTable->addErrorLogEntry(
            "test-user2", "Axon", "example-context", "values", "this is a test-message", error),
        true);

    cleanupTest();
}

/**
 * @brief getAllErrorLog_test
 */
void
ErrorLogTable_Test::getAllErrorLog_test()
{
    initTest();

    Axon::ErrorContainer error;
    ErrorLogTable* errorLogTable = ErrorLogTable::getInstance();

    errorLogTable->initTable(error);
    errorLogTable->addErrorLogEntry(
        "test-user", "Axon", "example-context", "values", "this is a test-message", error);
    errorLogTable->addErrorLogEntry(
        "test-user2", "Axon", "example-context", "values", "this is a test-message", error);

    Axon::TableItem result;
    TEST_EQUAL(errorLogTable->getAllErrorLogEntries(result, "test-user", 0, error), true);
    TEST_EQUAL(result.getNumberOfRows(), 1);
    TEST_EQUAL(result.getNumberOfColums(), errorLogTable->getNumberOfColumns());

    TEST_EQUAL(result.getCell(1, 0), "test-user");
    TEST_EQUAL(result.getCell(2, 0), "Axon");
    TEST_EQUAL(result.getCell(3, 0), "example-context");
    TEST_EQUAL(result.getCell(4, 0), "values");
    TEST_EQUAL(result.getCell(5, 0), "this is a test-message");

    cleanupTest();
}
