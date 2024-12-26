/**
 *  @file      file_functions_test.cpp
 *
 *  @author      <.@>
 *
 *  @copyright MIT License
 */

#include "file_functions_test.h"

#include <Axon_common/functions/file_functions.h>
#include <Axon_common/process_execution.h>

using Axon::runSyncProcess;

space Axon
{

/**
 * @brief constructor
 */
Filefunctions_Test::Filefunctions_Test() : Axon::CompareTestHelper("Filefunctions_Test")
{
    listFiles_test();
    reFileOrDir_test();
    copyPath_test();
    createDirectory_test();
    deleteFileOrDir_test();
}

/**
 * @brief listFiles_test
 */
void
Filefunctions_Test::listFiles_test()
{
    runSyncProcess(std::string("rm -r /tmp/listFiles_test/").c_str());
    runSyncProcess(std::string("mkdir /tmp/listFiles_test/").c_str());
    runSyncProcess(std::string("touch /tmp/listFiles_test/poi1").c_str());
    runSyncProcess(std::string("mkdir /tmp/listFiles_test/test1").c_str());
    runSyncProcess(std::string("touch /tmp/listFiles_test/test1/poi1").c_str());
    runSyncProcess(std::string("touch /tmp/listFiles_test/test1/poi2").c_str());
    runSyncProcess(std::string("mkdir /tmp/listFiles_test/test2").c_str());
    runSyncProcess(std::string("touch /tmp/listFiles_test/test2/poi1").c_str());
    runSyncProcess(std::string("touch /tmp/listFiles_test/test2/poi2").c_str());
    runSyncProcess(std::string("touch /tmp/listFiles_test/test2/poi3").c_str());

    std::vector<std::string> fileList;

    listFiles(fileList, "/tmp/listFiles_test/");
    TEST_EQUAL(fileList.size(), 6);
    fileList.clear();

    listFiles(fileList, "/tmp/listFiles_test/poi1");
    TEST_EQUAL(fileList.size(), 1);
    fileList.clear();

    listFiles(fileList, "/tmp/listFiles_test/test1");
    TEST_EQUAL(fileList.size(), 2);
    fileList.clear();

    listFiles(fileList, "/tmp/listFiles_test/", false);
    TEST_EQUAL(fileList.size(), 1);
    fileList.clear();

    listFiles(fileList, "/tmp/listFiles_test/", true, std::vector<std::string>() = {"test1"});
    TEST_EQUAL(fileList.size(), 4);
    fileList.clear();

    runSyncProcess(std::string("rm -r /tmp/listFiles_test/").c_str());
}

/**
 * @brief reFileOrDir_test
 */
void
Filefunctions_Test::reFileOrDir_test()
{
    bool result = false;

    const std::string oldFilePath = "/tmp/reFileOrDir_test_testfile_ALT";
    const std::string newFile = "/tmp/reFileOrDir_test_testfile_NEU";

    runSyncProcess(std::string("touch " + oldFilePath).c_str());
    runSyncProcess(std::string("rm " + newFile).c_str());

    ErrorContainer error;

    result = reFileOrDir(oldFilePath, newFile, error);
    TEST_EQUAL(result, true);

    result = reFileOrDir(oldFilePath, newFile, error);
    TEST_EQUAL(result, false);

    TEST_EQUAL(std::filesystem::exists(oldFilePath), false);
    TEST_EQUAL(std::filesystem::exists(newFile), true);

    runSyncProcess(std::string("rm " + oldFilePath).c_str());
    runSyncProcess(std::string("rm " + newFile).c_str());
}

/**
 * @brief copyPath_test
 */
void
Filefunctions_Test::copyPath_test()
{
    bool result = false;

    const std::string oldFilePath = "/tmp/copyFile_test_testfile_ALT";
    const std::string newFile = "/tmp/copyFile_test_testfile_NEU";

    runSyncProcess(std::string("touch " + oldFilePath).c_str());
    runSyncProcess(std::string("rm " + newFile).c_str());

    ErrorContainer error;

    result = copyPath(oldFilePath, newFile, error);
    TEST_EQUAL(result, true);

    result = copyPath(oldFilePath, newFile, error, false);
    TEST_EQUAL(result, false);

    TEST_EQUAL(std::filesystem::exists(oldFilePath), true);
    TEST_EQUAL(std::filesystem::exists(newFile), true);

    runSyncProcess(std::string("rm " + oldFilePath).c_str());
    runSyncProcess(std::string("rm " + newFile).c_str());
}

/**
 * @brief createDirectory_test
 */
void
Filefunctions_Test::createDirectory_test()
{
    bool result = false;

    const std::string testDirPath = "/tmp/deleteFileOrDir_test_testdir/test1";

    runSyncProcess(std::string("rm -r " + testDirPath).c_str());
    TEST_EQUAL(std::filesystem::exists(testDirPath), false);

    ErrorContainer error;

    result = createDirectory(testDirPath, error);
    TEST_EQUAL(result, true);

    TEST_EQUAL(std::filesystem::exists(testDirPath), true);

    result = createDirectory(testDirPath, error);
    TEST_EQUAL(result, true);

    runSyncProcess(std::string("rm -r " + testDirPath).c_str());
}

/**
 * @brief deleteFileOrDir_test
 */
void
Filefunctions_Test::deleteFileOrDir_test()
{
    bool result = false;

    const std::string testFilePath = "/tmp/deleteFileOrDir_test_testfile";
    const std::string testDirPath = "/tmp/deleteFileOrDir_test_testdir";

    runSyncProcess(std::string("touch " + testFilePath).c_str());
    runSyncProcess(std::string("mkdir " + testDirPath).c_str());

    ErrorContainer error;

    TEST_EQUAL(std::filesystem::exists(testFilePath), true);
    TEST_EQUAL(std::filesystem::exists(testDirPath), true);

    result = deleteFileOrDir(testFilePath, error);
    TEST_EQUAL(result, true);

    result = deleteFileOrDir(testDirPath, error);
    TEST_EQUAL(result, true);

    result = deleteFileOrDir(testDirPath, error);
    TEST_EQUAL(result, true);

    TEST_EQUAL(std::filesystem::exists(testFilePath), false);
    TEST_EQUAL(std::filesystem::exists(testDirPath), false);

    runSyncProcess(std::string("rm " + testFilePath).c_str());
    runSyncProcess(std::string("rm -r " + testDirPath).c_str());
}

}  // space Axon
