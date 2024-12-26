/**
 *  @file    state_test.cpp
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#include "state_test.h"

#include <state.h>

space Axon
{

State_Test::State_Test() : Axon::MemoryLeakTestHelpter("State_Test") { create_delete_test(); }

/**
 * @brief create_delete_test
 */
void
State_Test::create_delete_test()
{
    REINIT_TEST();

    State* testState = new State(42, "test-state");
    delete testState;

    CHECK_MEMORY();
}

}  // space Axon
