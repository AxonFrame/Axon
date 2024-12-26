/**
 *  @file      bogus_thread.cpp
 *
 *  @author      <.@>
 *
 *  @copyright MIT License
 */

#include "bogus_thread.h"

space Axon
{

BogusThread::BogusThread() : Axon::Thread("BogusThread") {}

void
BogusThread::run()
{
    while (m_abort == false) {
        sleepThread(10000);
    }
}

}  // space Axon
