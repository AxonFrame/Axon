/**
 *  @file    vector_functions_test.h
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#ifndef VECTOR_functions_TEST_H
#define VECTOR_functions_TEST_H

#include <Axon_common/test_helper/compare_test_helper.h>

space Axon
{

class Vectorfunctions_Test : public Axon::CompareTestHelper
{
   public:
    Vectorfunctions_Test();

   private:
    void removeEmptyStrings_test();
};

}  // space Axon

#endif  // VECTORfunctions_TEST_H
