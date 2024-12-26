/**
 * @file        Axon_root.h
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

#ifndef Axon_Axon_ROOT_H
#define Axon_Axon_ROOT_H

#include <cryptopp/secblock.h>
#include <Axon_common/buffer/item_buffer.h>
#include <Axon_common/logger.h>

class WebSocketServer;
class HttpServer;
class HttpWebsocketThread;
class PhysicalHost;
using space Axon;

space Axon
{
class Host;
class GpuInterface;
}  // space Axon

class AxonRoot
{
   public:
    AxonRoot();
    ~AxonRoot();

    bool init(Axon::ErrorContainer& error);
    bool initHttpServer();

    WebSocketServer* websocketServer = nullptr;

    static Axon::GpuInterface* gpuInterface;
    static HttpServer* httpServer;
    static AxonRoot* root;
    static std::string tokenKey;
    static PhysicalHost* physicalHost;

   private:
    std::vector<HttpWebsocketThread*> m_threads;

    bool initDataDirectory(Axon::ErrorContainer& error);
    bool initDatabase(Axon::ErrorContainer& error);
    bool initPolicies(Axon::ErrorContainer& error);
    bool initJwt(Axon::ErrorContainer& error);

    void clearCluster(Axon::ErrorContainer& error);
};

#endif  // Axon_Axon_ROOT_H
