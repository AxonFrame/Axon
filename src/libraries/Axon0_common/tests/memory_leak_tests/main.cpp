/**
 *  @file    main.cpp
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#include <Axon_common/buffer/data_buffer_test.h>
#include <Axon_common/buffer/item_buffer_test.h>
#include <Axon_common/buffer/ring_buffer_test.h>
#include <Axon_common/buffer/stack_buffer_reserve_test.h>
#include <Axon_common/buffer/stack_buffer_test.h>
#include <Axon_common/items/table_item_test.h>
#include <Axon_common/state_test.h>
#include <Axon_common/statemachine_test.h>
#include <Axon_common/threading/thread_test.h>

#include <iostream>

int
main()
{
    Axon::DataBuffer_Test();
    Axon::ItemBuffer_Test();
    Axon::RingBuffer_Test();
    Axon::StackBufferReserve_Test();
    Axon::StackBuffer_Test();

    Axon::State_Test();
    Axon::Statemachine_Test();

    Axon::TableItem_test();

    Axon::Thread_Test();
}
