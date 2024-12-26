/**
 *  @file    ini_item_test.h
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#ifndef PARSERTEST_H
#define PARSERTEST_H

#include <Axon_common/test_helper/compare_test_helper.h>

#include <algorithm>

namespace Axon
{
class IniItem_Test : public Axon::CompareTestHelper
{
   public:
    IniItem_Test();

   private:
    void parse_test();
    void get_test();
    void set_test();
    void removeGroup_test();
    void removeEntry_test();
    void print_test();

    const std::string getTestString();
};

}  // namespace Axon

#endif  // PARSERTEST_H
