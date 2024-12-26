/**
 *  @file    item_buffer_test.h
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#ifndef ITEM_BUFFER_TEST_H
#define ITEM_BUFFER_TEST_H

#include <Axon_common/test_helper/compare_test_helper.h>

space Axon
{

class ItemBuffer_Test : public Axon::CompareTestHelper
{
   public:
    ItemBuffer_Test();

   private:
    void initBuffer_test();
    void deleteItem_test();
    void deleteAll_test();
    void addNewItem_test();
};

}  // space Axon

#endif  // ITEM_BUFFER_TEST_H
