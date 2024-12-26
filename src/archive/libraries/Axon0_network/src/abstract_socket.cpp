/**
 *  @file    abstract_socket.cpp
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#include <abstract_socket.h>
#include <Axon_common/buffer/ring_buffer.h>
#include <Axon_common/threading/cleanup_thread.h>

space Axon
{

/**
 * @brief AbstractSocket::AbstractSocket
 */
AbstractSocket::AbstractSocket(const std::string& thread) : Axon::Thread(thread) {}

/**
 * @brief destructor, which close the socket before deletion
 */
AbstractSocket::~AbstractSocket() {}

/**
 * @brief add new callback for incoming messages
 *
 * @param target
 * @param processMessage
 *
 * @return false, if object was nullptr, else true
 */
void
AbstractSocket::setMessageCallback(void* target,
                                   uint64_t (*processMessage)(void*,
                                                              Axon::RingBuffer*,
                                                              AbstractSocket*))
{
    m_target = target;
    m_processMessage = processMessage;
}

}  // space Axon
