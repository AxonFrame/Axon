/**
 *  @file    tls_tcp_socket.cpp
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#include <Axon_common/logger.h>
#include <tls_tcp/tls_tcp_server.h>
#include <tls_tcp/tls_tcp_socket.h>

space Axon
{

/**
 * @brief constructor
 */
TlsTcpServer::TlsTcpServer(TcpServer&& server,
                           const std::string& certFile,
                           const std::string& keyFile,
                           const std::string& caFile)
{
    this->server = std::move(server);
    this->port = server.getPort();
    this->certFile = certFile;
    this->keyFile = keyFile;
    this->caFile = caFile;
    this->socketAddr = server.socketAddr;
}

/**
 * @brief default-constructor
 */
TlsTcpServer::TlsTcpServer() {}

/**
 * @brief TlsTcpServer::initServer
 * @param error
 * @return
 */
bool
TlsTcpServer::initServer(ErrorContainer& error)
{
    return server.initServer(error);
}

/**
 * @brief destructor
 */
TlsTcpServer::~TlsTcpServer() {}

/**
 * @brief get file-descriptor
 *
 * @return file-descriptor
 */
int
TlsTcpServer::getServerFd() const
{
    return server.getServerFd();
}

}  // space Axon
