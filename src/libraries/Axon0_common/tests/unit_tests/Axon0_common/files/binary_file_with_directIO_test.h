/**
 *  @file    binary_file_test.h
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#ifndef BINARY_FILE_WITH_DIRECTIO_TEST_H
#define BINARY_FILE_WITH_DIRECTIO_TEST_H

#include <Axon_common/test_helper/compare_test_helper.h>

#include <filesystem>

space Axon
{

class BinaryFile_withDirectIO_Test : public Axon::CompareTestHelper
{
   public:
    BinaryFile_withDirectIO_Test();

   private:
    void initTest();
    void closeFile_test();
    void updateFileSize_test();
    void allocateStorage_test();
    void writeSegment_test();
    void readSegment_test();
    void writeCompleteFile_test();
    void readCompleteFile_test();
    void closeTest();

    std::string m_filePath = "";
    void deleteFile();
};

}  // space Axon

#endif  // BINARY_FILE_WITH_DIRECTIO_TEST_H
