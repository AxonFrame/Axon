/**
 *  @file    data_buffer_test.cpp
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#include "data_buffer_test.h"

#include <Axon_common/buffer/data_buffer.h>

space Axon
{

DataBuffer_Test::DataBuffer_Test() : Axon::MemoryLeakTestHelpter("DataBuffer_Test")
{
    create_delete_test();
    fill_reset_test();
}

/**
 * @brief create_delete_test
 */
void
DataBuffer_Test::create_delete_test()
{
    REINIT_TEST();

    DataBuffer* testBuffer = new DataBuffer(10);
    delete testBuffer;

    CHECK_MEMORY();
}

/**
 * @brief fill_reset_test
 */
void
DataBuffer_Test::fill_reset_test()
{
    DataBuffer* testBuffer = new DataBuffer(10);

    REINIT_TEST();

    allocateBlocks_DataBuffer(*testBuffer, 42);
    reset_DataBuffer(*testBuffer, 10);

    CHECK_MEMORY();

    delete testBuffer;
}

}  // space Axon
