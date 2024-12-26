/**
 *  @file       obj_parser_test.h
 *
 *  @author       <.@>
 *
 *  @copyright  MIT License
 */

#ifndef OBJPARSER_TEST_H
#define OBJPARSER_TEST_H

#include <Axon_common/test_helper/compare_test_helper.h>

#include <string>
#include <utility>
#include <vector>

class ObjItem_Test : public Axon::CompareTestHelper
{
   public:
    ObjItem_Test();

   private:
    void parse_test();
    void converter_test();

    const std::string getTestString();
    const std::string getCompareString();
};

#endif  // OBJPARSER_TEST_H
