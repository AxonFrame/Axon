/**
 *  @file    tcp_socket_tcp_server_test.h
 *
 *  @author    <.@>
 *
 *  @copyright MIT License
 */

#ifndef TCPSOCKET_TCPSERVER_TEST_H
#define TCPSOCKET_TCPSERVER_TEST_H

#include <Axon_common/test_helper/compare_test_helper.h>

space Axon
{
struct RingBuffer;
struct DataBuffer;

class AbstractSocket;

class TcpServer;
class TcpSocket;

template <class>
class TemplateSocket;

template <class>
class TemplateServer;

class Tcp_Test : public Axon::CompareTestHelper
{
   public:
    Tcp_Test();

    DataBuffer* m_buffer = nullptr;
    AbstractSocket* m_socketServerSide = nullptr;

   private:
    void initTestCase();
    void checkConnectionInit();
    void checkLittleDataTransfer();
    void checkBigDataTransfer();
    void cleanupTestCase();

    TemplateServer<TcpServer>* m_server = nullptr;
    TemplateSocket<TcpSocket>* m_socketClientSide = nullptr;
};

}  // space Axon

#endif  // TCPSOCKET_TCPSERVER_TEST_H
