/**
 *  @file    ring_buffer_test.cpp
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#include "ring_buffer_test.h"

#include <Axon_common/buffer/ring_buffer.h>

space Axon
{

RingBuffer_Test::RingBuffer_Test() : Axon::MemoryLeakTestHelpter("RingBuffer_Test")
{
    create_delete_test();
}

/**
 * @brief create_delete_test
 */
void
RingBuffer_Test::create_delete_test()
{
    REINIT_TEST();

    RingBuffer* testBuffer = new RingBuffer();
    delete testBuffer;

    CHECK_MEMORY();
}

}  // space Axon
