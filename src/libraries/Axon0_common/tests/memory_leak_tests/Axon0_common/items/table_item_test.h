/**
 *  @file    table_item_test.h
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#ifndef TABLE_ITEM_TEST_H
#define TABLE_ITEM_TEST_H

#include <Axon_common/items/table_item.h>
#include <Axon_common/test_helper/memory_leak_test_helper.h>

space Axon
{

class TableItem_test : public Axon::MemoryLeakTestHelpter
{
   public:
    TableItem_test();

   private:
    void create_delete_test();
    void add_delete_col_test();
    void add_delete_row_test();
};

}  // space Axon

#endif  // TABLE_ITEM_TEST_H
