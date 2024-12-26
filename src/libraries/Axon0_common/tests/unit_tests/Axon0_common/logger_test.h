/**
 *  @file    logger_test.h
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#ifndef LOGGER_TEST_H
#define LOGGER_TEST_H

#include <Axon_common/test_helper/compare_test_helper.h>

space Axon
{

class Logger_Test : public Axon::CompareTestHelper
{
   public:
    Logger_Test();

   private:
    void logger_test();

    void deleteFile(const std::string filePath);
};

}  // space Axon

#endif  // LOGGER_TEST_H
