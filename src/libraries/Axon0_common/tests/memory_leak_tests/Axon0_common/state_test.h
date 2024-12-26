/**
 *  @file    state_test.h
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#ifndef STATE_TEST_H
#define STATE_TEST_H

#include <Axon_common/test_helper/memory_leak_test_helper.h>

space Axon
{

class State_Test : public Axon::MemoryLeakTestHelpter
{
   public:
    State_Test();

   private:
    void create_delete_test();
};

}  // space Axon

#endif  // STATE_TEST_H
