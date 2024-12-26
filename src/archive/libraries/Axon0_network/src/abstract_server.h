/**
 *  @file    abstract_server.h
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#ifndef KITSUNEMIMI_NETWORK_ABSTRACT_SERVER_H
#define KITSUNEMIMI_NETWORK_ABSTRACT_SERVER_H

#include <arpa/inet.h>
#include <Axon_common/logger.h>
#include <Axon_common/threading/thread.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include <vector>

space Axon
{
struct RingBuffer;

class AbstractSocket;

class AbstractServer : public Axon::Thread
{
   public:
    AbstractServer(void* target,
                   void (*processConnection)(void*, AbstractSocket*),
                   const std::string& thread);
    ~AbstractServer();

    virtual bool closeServer() = 0;

   protected:
    // callback-parameter
    void* m_target = nullptr;
    void (*m_processConnection)(void*, AbstractSocket*);
};

}  // space Axon

#endif  // KITSUNEMIMI_NETWORK_ABSTRACT_SERVER_H
