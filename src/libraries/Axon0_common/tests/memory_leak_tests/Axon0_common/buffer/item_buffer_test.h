/**
 *  @file    item_buffer_test.h
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#ifndef ITEM_BUFFER_TEST_H
#define ITEM_BUFFER_TEST_H

#include <Axon_common/test_helper/memory_leak_test_helper.h>

space Axon
{

class ItemBuffer_Test : public Axon::MemoryLeakTestHelpter
{
   public:
    ItemBuffer_Test();

   private:
    void create_delete_test();
};

}  // space Axon

#endif  // ITEM_BUFFER_TEST_H
