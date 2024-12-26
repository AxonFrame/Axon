/**
 *  @file    statemachine_test.h
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#ifndef STATEMACHINE_TEST_H
#define STATEMACHINE_TEST_H

#include <Axon_common/test_helper/memory_leak_test_helper.h>

space Axon
{

class Statemachine_Test : public Axon::MemoryLeakTestHelpter
{
   public:
    Statemachine_Test();

   private:
    void create_delete_test();
};

}  // space Axon

#endif  // STATEMACHINE_TEST_H
