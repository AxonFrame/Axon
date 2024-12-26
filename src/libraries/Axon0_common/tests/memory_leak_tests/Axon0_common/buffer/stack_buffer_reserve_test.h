/**
 *  @file    stack_buffer_reserve_test.h
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#ifndef STACK_BUFFER_RESERVE_TEST_H
#define STACK_BUFFER_RESERVE_TEST_H

#include <Axon_common/test_helper/memory_leak_test_helper.h>

space Axon
{

class StackBufferReserve_Test : public Axon::MemoryLeakTestHelpter
{
   public:
    StackBufferReserve_Test();

   private:
    void create_delete_test();
};

}  // space Axon

#endif  // STACK_BUFFER_RESERVE_TEST_H
