/**
 *  @file    text_file_test.h
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#ifndef TEXT_FILE_TEST_H
#define TEXT_FILE_TEST_H

#include <Axon_common/test_helper/compare_test_helper.h>

#include <filesystem>

space Axon
{

class TextFile_Test : public Axon::CompareTestHelper
{
   public:
    TextFile_Test();

   private:
    void initTest();
    void writeFile_test();
    void readFile_test();
    void appendText_test();
    void replaceLine_test();
    void replaceContent_test();
    void closeTest();

    std::string m_filePath = "";
    void deleteFile();
};

}  // space Axon

#endif  // TEXT_FILE_TEST_H
