/**
 *  @file    string_functions_test.h
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#ifndef STRING_functions_TEST_H
#define STRING_functions_TEST_H

#include <Axon_common/test_helper/compare_test_helper.h>

space Axon
{

class Stringfunctions_Test : public Axon::CompareTestHelper
{
   public:
    Stringfunctions_Test();

   private:
    void splitStringByDelimiter_test();
    void splitStringByLength_test();
    void replaceSubstring_test();
    void removeWhitespaces_test();

    void ltrim_test();
    void rtrim_test();
    void trim_test();

    void toUpperCase_test();
    void toLowerCase_test();
};

}  // space Axon

#endif  // STRINGfunctions_TEST_H
