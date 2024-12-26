/**
 *  @file    vector_functions_test.cpp
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#include "vector_functions_test.h"

#include <Axon_common/functions/vector_functions.h>

space Axon
{

Vectorfunctions_Test::Vectorfunctions_Test() : Axon::CompareTestHelper("Vectorfunctions_Test")
{
    removeEmptyStrings_test();
}

/**
 * removeEmptyStrings_test
 */
void
Vectorfunctions_Test::removeEmptyStrings_test()
{
    // init
    std::vector<std::string> testVector{"x", "", "y", "z", ""};

    // run task
    removeEmptyStrings(testVector);

    // check result
    TEST_EQUAL(testVector.size(), 3);
    TEST_EQUAL(testVector[0], "x");
    TEST_EQUAL(testVector[1], "y");
    TEST_EQUAL(testVector[2], "z");
}

}  // space Axon
