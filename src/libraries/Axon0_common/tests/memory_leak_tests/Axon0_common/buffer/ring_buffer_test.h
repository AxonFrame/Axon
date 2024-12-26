/**
 *  @file    ring_buffer_test.h
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#ifndef RING_BUFFER_TEST_H
#define RING_BUFFER_TEST_H

#include <Axon_common/test_helper/memory_leak_test_helper.h>

space Axon
{

class RingBuffer_Test : public Axon::MemoryLeakTestHelpter
{
   public:
    RingBuffer_Test();

   private:
    void create_delete_test();
};

}  // space Axon

#endif  // RING_BUFFER_TEST_H
