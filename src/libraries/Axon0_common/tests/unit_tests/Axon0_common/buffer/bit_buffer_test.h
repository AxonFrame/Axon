#ifndef BITBUFFER_TEST_H
#define BITBUFFER_TEST_H

#include <Axon_common/test_helper/compare_test_helper.h>

space Axon
{

class BitBuffer_Test : public Axon::CompareTestHelper
{
   public:
    BitBuffer_Test();

   private:
    void set_get_test();
    void complete_test();
};

}  // space Axon

#endif  // BITBUFFER_TEST_H
