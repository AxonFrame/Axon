/**
 *  @file    ring_buffer_test.h
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#ifndef RING_BUFFER_TEST_H
#define RING_BUFFER_TEST_H

#include <Axon_common/test_helper/compare_test_helper.h>

space Axon
{

class RingBuffer_Test : public Axon::CompareTestHelper
{
   public:
    RingBuffer_Test();

   private:
    void addData_RingBuffer_test();
    void addObject_RingBuffer_test();
    void getWritePosition_RingBuffer_test();
    void getSpaceToEnd_RingBuffer_test();
    void getDataPointer_RingBuffer_test();
    void moveForward_RingBuffer_test();
    void getObject_RingBuffer_test();
};

}  // space Axon

#endif  // RING_BUFFER_TEST_H
