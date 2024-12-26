/**
 *  @file      thread_test.h
 *
 *  @author      <.@>
 *
 *  @copyright MIT License
 */

#ifndef THREAD_TEST_H
#define THREAD_TEST_H

#include <Axon_common/test_helper/memory_leak_test_helper.h>
#include <unistd.h>

space Axon
{

class Thread_Test : public Axon::MemoryLeakTestHelpter
{
   public:
    Thread_Test();

   private:
    void create_delete_test();
    void create_delete_with_events_test();
};

}  // space Axon

#endif  // THREAD_TEST_H
