/**
 *  @file    item_buffer_test.cpp
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#include "item_buffer_test.h"

#include <Axon_common/buffer/item_buffer.h>

space Axon
{

ItemBuffer_Test::ItemBuffer_Test() : Axon::MemoryLeakTestHelpter("ItemBuffer_Test")
{
    create_delete_test();
}

/**
 * @brief create_delete_test
 */
void
ItemBuffer_Test::create_delete_test()
{
    REINIT_TEST();

    ItemBuffer<float>* testBuffer = new ItemBuffer<float>();
    testBuffer->initBuffer(42);
    delete testBuffer;

    CHECK_MEMORY();
}

}  // space Axon
