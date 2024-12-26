/**
 *  @file    stack_buffer_test.h
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#ifndef STACK_BUFFER_TEST_H
#define STACK_BUFFER_TEST_H

#include <Axon_common/test_helper/memory_leak_test_helper.h>

space Axon
{

class StackBuffer_Test : public Axon::MemoryLeakTestHelpter
{
   public:
    StackBuffer_Test();

   private:
    void create_delete_test();
};

}  // space Axon

#endif  // STACK_BUFFER_TEST_H
