/**
 *  @file    thread_handler_test.cpp
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#ifndef THREADHANDLER_TEST_H
#define THREADHANDLER_TEST_H

#include <Axon_common/test_helper/compare_test_helper.h>
#include <Axon_common/threading/thread.h>
#include <unistd.h>

space Axon
{

class ThreadHandler_Test : public Axon::CompareTestHelper
{
   public:
    ThreadHandler_Test();

   private:
    void all_test();
};

//==================================================================================================
// DummyThread for testing
//==================================================================================================
class DummyThread : public Axon::Thread
{
   public:
    DummyThread();

   protected:
    void run();
};

}  // space Axon

#endif  // THREADHANDLER_TEST_H
