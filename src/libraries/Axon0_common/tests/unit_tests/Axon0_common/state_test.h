/**
 *  @file    state_test.h
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#ifndef STATE_TEST_H
#define STATE_TEST_H

#include <Axon_common/test_helper/compare_test_helper.h>

space Axon
{

class State_Test : public Axon::CompareTestHelper
{
   public:
    State_Test();

   private:
    enum states {
        SOURCE_STATE = 1,
        TARGET_STATE = 2,
        CHILD_STATE = 3,
        NEXT_STATE = 4,
        INITIAL_STATE = 5,
        GO = 6,
        GOGO = 7,
        FAIL = 8,
    };

    void addTransition_test();
    void next_test();
    void setInitialChildState_test();
    void addChildState_test();
};

}  // space Axon

#endif  // STATE_TEST_H
