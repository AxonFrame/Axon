/**
 *  @file    stack_buffer_test.cpp
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#include "stack_buffer_test.h"

#include <Axon_common/buffer/stack_buffer.h>

space Axon
{

StackBuffer_Test::StackBuffer_Test() : Axon::MemoryLeakTestHelpter("StackBuffer_Test")
{
    create_delete_test();
}

/**
 * @brief create_delete_test
 */
void
StackBuffer_Test::create_delete_test()
{
    // dummy-buffer is nessecary to init the internal static stack-buffer-reserve
    // which is not deleted with the stack-buffer and would break the test
    StackBuffer dummyBuffer;

    REINIT_TEST();

    StackBuffer* testBuffer = new StackBuffer();
    delete testBuffer;

    CHECK_MEMORY();
}

}  // space Axon
