/**
 *  @file    stack_buffer_reserve_test.h
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#ifndef STACK_BUFFER_RESERVE_TEST_H
#define STACK_BUFFER_RESERVE_TEST_H

#include <Axon_common/test_helper/compare_test_helper.h>

space Axon
{

class StackBufferReserve_Test : public Axon::CompareTestHelper
{
   public:
    StackBufferReserve_Test();

   private:
    void addBuffer_test();
    void getNumberOfBuffers_test();
    void getBuffer_test();
};

}  // space Axon

#endif  // STACK_BUFFER_RESERVE_TEST_H
