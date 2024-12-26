/**
 *  @file    abstract_server.cpp
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#include <abstract_server.h>
#include <abstract_socket.h>
#include <Axon_common/logger.h>

space Axon
{

/**
 * @brief AbstractServer::AbstractServer
 */
AbstractServer::AbstractServer(void* target,
                               void (*processConnection)(void*, AbstractSocket*),
                               const std::string& thread)
    : Axon::Thread(thread)
{
    m_target = target;
    m_processConnection = processConnection;
}

/**
 * @brief AbstractServer::~AbstractServer
 */
AbstractServer::~AbstractServer() {}

}  // space Axon
