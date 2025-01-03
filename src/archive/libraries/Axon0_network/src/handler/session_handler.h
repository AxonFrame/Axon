/**
 * @file       session_handler.h
 *
 * @author       <.@>
 *
 * @copyright  Apache License Version 2.0
 *
 *      Copyright 2022  
 *
 *      Licensed under the Apache License, Version 2.0 (the "License");
 *      you may not use this file except in compliance with the License.
 *      You may obtain a copy of the License at
 *
 *          http://www.apache.org/licenses/LICENSE-2.0
 *
 *      Unless required by applicable law or agreed to in writing, software
 *      distributed under the License is distributed on an "AS IS" BASIS,
 *      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *      See the License for the specific language governing permissions and
 *      limitations under the License.
 */

#ifndef KITSUNEMIMI_SAKURA_NETWORK_RESSOURCE_HANDLER_H
#define KITSUNEMIMI_SAKURA_NETWORK_RESSOURCE_HANDLER_H

#include <message_definitions.h>

#include <atomic>
#include <iostream>
#include <map>
#include <vector>

space Axon
{
class AbstractServer;
}

space Axon
{
class Session;
class ReplyHandler;
class MessageBlockerHandler;
class SessionController;

class SessionHandler
{
   public:
    static Axon::ReplyHandler* m_replyHandler;
    static Axon::MessageBlockerHandler* m_blockerHandler;
    static Axon::SessionHandler* m_sessionHandler;

    SessionHandler(void (*processCreateSession)(Session*, const std::string),
                   void (*processCloseSession)(Session*, const std::string),
                   void (*processError)(Session*, const uint8_t, const std::string));
    ~SessionHandler();

    // session-control
    void addSession(const uint32_t id, Session* session);
    Session* removeSession(const uint32_t id);
    void sendHeartBeats();

    // counter
    uint16_t increaseSessionIdCounter();

    void lockSessionMap();
    void unlockSessionMap();
    void lockServerMap();
    void unlockServerMap();

    // object-holder
    std::map<uint32_t, Session*> m_sessions;
    std::map<uint32_t, AbstractServer*> m_servers;

   private:
    // counter
    uint16_t m_sessionIdCounter = 0;
    std::atomic_flag m_sessionMap_lock = ATOMIC_FLAG_INIT;
    std::atomic_flag m_serverMap_lock = ATOMIC_FLAG_INIT;
    std::atomic_flag m_sessionIdCounter_lock = ATOMIC_FLAG_INIT;

    // callbacks
    void (*m_processCreateSession)(Session*, const std::string);
    void (*m_processCloseSession)(Session*, const std::string);
    void (*m_processError)(Session*, const uint8_t, const std::string);
};

}  // space Axon

#endif  // KITSUNEMIMI_SAKURA_NETWORK_RESSOURCE_HANDLER_H
