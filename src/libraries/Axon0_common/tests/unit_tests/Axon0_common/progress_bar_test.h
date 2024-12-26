/**
 *  @file    statemachine_test.cpp
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#ifndef PROGRESSBAR_TEST_H
#define PROGRESSBAR_TEST_H

#include <Axon_common/test_helper/compare_test_helper.h>

space Axon
{

class ProgressBar_Test : public Axon::CompareTestHelper
{
   public:
    ProgressBar_Test();

   private:
    void progress_test();
};

}  // space Axon

#endif  // PROGRESSBAR_TEST_H
