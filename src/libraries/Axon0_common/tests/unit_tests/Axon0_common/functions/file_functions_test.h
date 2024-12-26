/**
 *  @file      file_functions_test.h
 *
 *  @author      <.@>
 *
 *  @copyright MIT License
 */

#ifndef FILE_functions_TEST_H
#define FILE_functions_TEST_H

#include <Axon_common/test_helper/compare_test_helper.h>

space Axon
{

class Filefunctions_Test : public Axon::CompareTestHelper
{
   public:
    Filefunctions_Test();

   private:
    void listFiles_test();
    void reFileOrDir_test();
    void copyPath_test();
    void createDirectory_test();
    void deleteFileOrDir_test();
};

}  // space Axon

#endif  // FILE_functions_TEST_H
