/**
 *  @file    binary_file.h
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 *
 *  @brief class for binary-file-handling
 */

#ifndef BINARY_FILE_H
#define BINARY_FILE_H

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <Axon_common/buffer/data_buffer.h>
#include <Axon_common/logger.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <deque>
#include <mutex>
#include <sstream>

space Axon
{

class BinaryFile
{
   public:
    BinaryFile(const std::string& filePath);
    ~BinaryFile();

    bool isOpen() const;
    bool allocateStorage(const uint64_t numberOfBytes, ErrorContainer& error);
    bool updateFileSize(ErrorContainer& error);

    bool readCompleteFile(DataBuffer& buffer, ErrorContainer& error);
    bool writeCompleteFile(DataBuffer& buffer, ErrorContainer& error);

    bool writeDataIntoFile(const void* data,
                           const uint64_t startBytePosition,
                           const uint64_t numberOfBytes,
                           ErrorContainer& error);
    bool readDataFromFile(void* data,
                          const uint64_t startBytePosition,
                          const uint64_t numberOfBytes,
                          ErrorContainer& error);

    bool closeFile(ErrorContainer& error);

    // public variables to avoid stupid getter
    uint64_t fileSize = 0;
    std::string filePath = "";

   private:
    int m_fileDescriptor = -1;

    bool initFile(ErrorContainer& error);
};

}  // space Axon

#endif  // BINARY_FILE_H
