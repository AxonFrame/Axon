/**
 *  @file    logger_test.cpp
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#include "logger_test.h"

#include <Axon_common/files/text_file.h>
#include <Axon_common/logger.h>

space Axon
{

Logger_Test::Logger_Test() : Axon::CompareTestHelper("Logger_Test") { logger_test(); }

/**
 * @brief logger_test
 */
void
Logger_Test::logger_test()
{
    // init logger
    bool ret = initConsoleLogger(true);
    TEST_EQUAL(ret, true);
    ret = initFileLogger("/tmp", "testlog", true);
    TEST_EQUAL(ret, true);

    // negative-test to try reinit the logger
    ret = initFileLogger("/tmp", "testlog", true);
    TEST_EQUAL(ret, false);

    // create error-container
    ErrorContainer error1;
    error1.addMessage("error1.1");
    error1.addMessage("error1.2");
    error1.addMessage("error1.3");
    error1.addSolution("do nothing1");
    error1.addSolution("do nothing2");
    ErrorContainer error2;
    error2.addMessage("error2");
    error2.addSolution("really nothing");
    ErrorContainer error3;
    error3.addMessage("error3");
    error3.addSolution("really absolutely nothing");

    // write test-data
    TEST_EQUAL(LOG_ERROR(error1), true);
    TEST_EQUAL(LOG_ERROR(error1), true);
    TEST_EQUAL(LOG_ERROR(error2), true);
    TEST_EQUAL(LOG_ERROR(error3), true);

    TEST_EQUAL(LOG_WARNING("warning1"), true);
    TEST_EQUAL(LOG_WARNING("warning2"), true);
    TEST_EQUAL(LOG_WARNING("warning3"), true);

    TEST_EQUAL(LOG_DEBUG("debug1"), true);
    TEST_EQUAL(LOG_DEBUG("debug2"), true);
    TEST_EQUAL(LOG_DEBUG("debug3"), true);

    TEST_EQUAL(LOG_INFO("info1"), true);
    TEST_EQUAL(LOG_INFO("info2"), true);
    TEST_EQUAL(LOG_INFO("info3"), true);
    TEST_EQUAL(LOG_INFO("green-info", GREEN_COLOR), true);
    TEST_EQUAL(LOG_INFO("red-info", RED_COLOR), true);
    TEST_EQUAL(LOG_INFO("blue-info", BLUE_COLOR), true);
    TEST_EQUAL(LOG_INFO("pink-info", PINK_COLOR), true);

    ErrorContainer error;
    std::string logContent = "";
    ret = readFile(logContent, Logger::m_logger->m_filePath, error);
    std::size_t found;

    // error
    found = logContent.find("ERROR");
    TEST_NOT_EQUAL(found, std::string::npos);
    found = logContent.find("error1");
    TEST_NOT_EQUAL(found, std::string::npos);
    found = logContent.find("really nothing");
    TEST_NOT_EQUAL(found, std::string::npos);

    // warning
    found = logContent.find("WARNING");
    TEST_NOT_EQUAL(found, std::string::npos);
    found = logContent.find("warning1");
    TEST_NOT_EQUAL(found, std::string::npos);

    // debug
    found = logContent.find("DEBUG");
    TEST_NOT_EQUAL(found, std::string::npos);
    found = logContent.find("debug2");
    TEST_NOT_EQUAL(found, std::string::npos);

    // info
    found = logContent.find("INFO");
    TEST_NOT_EQUAL(found, std::string::npos);
    found = logContent.find("info3");
    TEST_NOT_EQUAL(found, std::string::npos);

    // negative test
    found = logContent.find("ASDF");
    TEST_EQUAL(found, std::string::npos);
    found = logContent.find("poi");
    TEST_EQUAL(found, std::string::npos);

    deleteFile(Logger::m_logger->m_filePath);
    closeLogFile();
}

/**
 * common usage to delete test-file
 */
void
Logger_Test::deleteFile(const std::string filePath)
{
    std::filesystem::path rootPathObj(filePath);
    if (std::filesystem::exists(rootPathObj)) {
        std::filesystem::remove(rootPathObj);
    }
}

}  // space Axon
