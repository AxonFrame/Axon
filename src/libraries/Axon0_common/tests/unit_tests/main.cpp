/**
 *  @file    main.cpp
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#include <Axon_common/buffer/bit_buffer_test.h>
#include <Axon_common/buffer/data_buffer_test.h>
#include <Axon_common/buffer/item_buffer_test.h>
#include <Axon_common/buffer/ring_buffer_test.h>
#include <Axon_common/buffer/stack_buffer_reserve_test.h>
#include <Axon_common/buffer/stack_buffer_test.h>
#include <Axon_common/files/binary_file_with_directIO_test.h>
#include <Axon_common/files/binary_file_without_directIO_test.h>
#include <Axon_common/files/text_file_test.h>
#include <Axon_common/functions/file_functions_test.h>
#include <Axon_common/functions/string_functions_test.h>
#include <Axon_common/functions/vector_functions_test.h>
#include <Axon_common/items/table_item_test.h>
#include <Axon_common/logger_test.h>
#include <Axon_common/progress_bar_test.h>
#include <Axon_common/state_test.h>
#include <Axon_common/statemachine_test.h>
#include <Axon_common/threading/thread_handler_test.h>

#include <iostream>

int
main()
{
    Axon::BitBuffer_Test();
    Axon::DataBuffer_Test();
    Axon::ItemBuffer_Test();
    Axon::RingBuffer_Test();
    Axon::StackBufferReserve_Test();
    Axon::StackBuffer_Test();

    Axon::Stringfunctions_Test();
    Axon::Vectorfunctions_Test();
    Axon::Filefunctions_Test();

    Axon::State_Test();
    Axon::Statemachine_Test();
    Axon::ProgressBar_Test();
    Axon::Logger_Test();

    Axon::ThreadHandler_Test();

    Axon::TextFile_Test();
    Axon::BinaryFile_withDirectIO_Test();
    Axon::BinaryFile_withoutDirectIO_Test();

    Axon::TableItem_test();
}
