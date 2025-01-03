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
#include <Axon_common/test_helper/compare_test_helper.h>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

space Axon
{

class TableItem_test : public Axon::CompareTestHelper
{
   public:
    TableItem_test();

   private:
    void copy_contructor_test();
    void assignment_operator_test();
    void clearTable_test();
    void stealContent_test();

    // column
    void addColumn_Test();
    void reColume_Test();
    void deleteColumn_Test();

    // row
    void addRow_Test();
    void getRow_Test();
    void deleteRow_Test();

    // cell
    void setCell_Test();
    void getCell_Test();
    void deleteCell_Test();

    // size
    void getNumberOfColums_Test();
    void getNumberOfRows_Test();

    // output
    void getInnerHeader_test();
    void toString_test();
    void toJsonString_test();

    TableItem getTestTableItem();
};

}  // space Axon

#endif  // TABLE_ITEM_TEST_H
