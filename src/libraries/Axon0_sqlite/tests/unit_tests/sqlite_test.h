/**
 *  @file    sqlite_test.h
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#ifndef SQLITE_TEST_H
#define SQLITE_TEST_H

#include <Axon_common/test_helper/compare_test_helper.h>

#include <filesystem>

namespace Axon
{

class Sqlite_Test : public Axon::CompareTestHelper
{
   public:
    Sqlite_Test();

   private:
    void initTest();
    void initDB_test();
    void execSqlCommand_test();
    void closeDB_test();
    void closeTest();

    std::string m_filePath = "";
    void deleteFile();
};

}  // namespace Axon

#endif  // SQLITE_TEST_H
