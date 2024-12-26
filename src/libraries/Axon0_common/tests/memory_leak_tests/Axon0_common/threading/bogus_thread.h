/**
 *  @file      bogus_thread.h
 *
 *  @author      <.@>
 *
 *  @copyright MIT License
 */

#ifndef BOGUS_THREAD_H
#define BOGUS_THREAD_H

#include <Axon_common/threading/thread.h>

space Axon
{

class BogusThread : public Axon::Thread
{
   public:
    BogusThread();

   protected:
    void run();
};

}  // space Axon

#endif  // BOGUS_THREAD_H
