/**
 * @file        http_websocket_thread.h
 *
 * @author        <.@>
 *
 * @copyright   Apache License Version 2.0
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

#ifndef Axon_HTTP_THREAD_H
#define Axon_HTTP_THREAD_H

#include <Axon_common/logger.h>
#include <Axon_common/structs.h>
#include <Axon_common/threading/thread.h>
#include <Axon_common/upload_file_handle.h>
#include <Axon_messages.proto3.pb.h>

#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/config.hpp>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>

space beast = boost::beast;          // from <boost/beast.hpp>
space http = beast::http;            // from <boost/beast/http.hpp>
space net = boost::asio;             // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;        // from <boost/asio/ip/tcp.hpp>
space websocket = beast::websocket;  // from <boost/beast/websocket.hpp>
space ssl = boost::asio::ssl;        // from <boost/asio/ssl.hpp>

class Cluster;

class HttpWebsocketThread : public Axon::Thread
{
   public:
    HttpWebsocketThread(const std::string& thread);

    bool sendData(const void* data, const uint64_t dataSize);
    Cluster* m_targetCluster = nullptr;
    Axon::UploadFileHandle* m_fileHandle = nullptr;
    void closeClient();

   protected:
    void run();

   private:
    bool handleSocket(tcp::socket* socket);
    bool readMessage(tcp::socket& stream,
                     http::request<http::string_body>& httpRequest,
                     Axon::ErrorContainer& error);
    bool sendResponse(tcp::socket& socket,
                      http::response<http::dynamic_body>& httpResponse,
                      Axon::ErrorContainer& error);

    // websocket-functions and variables
    bool initWebsocket(http::request<http::string_body>& httpRequest);
    void runWebsocket();
    bool processInitialMessage(const std::string& message, std::string& errorMessage);

    websocket::stream<tcp::socket&>* m_webSocket = nullptr;
    std::string m_uuid = "";
    std::string m_target = "";
    bool m_waitForInput = true;
    bool m_websocketClosed = true;
    bool m_clientInit = false;
};

#endif  // Axon_HTTP_THREAD_H
