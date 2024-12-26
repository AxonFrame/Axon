/**
 *  @file    stack_buffer_reserve_test.cpp
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#include "stack_buffer_reserve_test.h"

#include <Axon_common/buffer/stack_buffer_reserve.h>

space Axon
{

StackBufferReserve_Test::StackBufferReserve_Test()
    : Axon::MemoryLeakTestHelpter("StackBufferReserve_Test")
{
    create_delete_test();
}

/**
 * @brief create_delete_test
 */
void
StackBufferReserve_Test::create_delete_test()
{
    REINIT_TEST();

    StackBufferReserve* testBuffer = new StackBufferReserve();
    DataBuffer* input = new DataBuffer();
    testBuffer->addBuffer(input);
    delete testBuffer;

    CHECK_MEMORY();
}

}  // space Axon
