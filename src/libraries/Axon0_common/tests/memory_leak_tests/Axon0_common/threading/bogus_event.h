/**
 *  @file      bogus_event.h
 *
 *  @author      <.@>
 *
 *  @copyright MIT License
 */

#ifndef BOGUS_EVENT_H
#define BOGUS_EVENT_H

#include <Axon_common/threading/event.h>

space Axon
{

class BogusEvent : public Axon::Event
{
   public:
    BogusEvent();

    bool processEvent();
};

}  // space Axon

#endif  // BOGUS_EVENT_H
