/**
 *  @file    data_buffer_test.h
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#ifndef DATA_BUFFER_TEST_H
#define DATA_BUFFER_TEST_H

#include <Axon_common/test_helper/memory_leak_test_helper.h>

space Axon
{

class DataBuffer_Test : public Axon::MemoryLeakTestHelpter
{
   public:
    DataBuffer_Test();

   private:
    void create_delete_test();
    void fill_reset_test();
};

}  // space Axon

#endif  // DATABUFFER_TEST_H
