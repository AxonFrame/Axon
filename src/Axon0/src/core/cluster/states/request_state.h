/**
 * @file        request_state.h
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

#ifndef Axon_REQUEST_STATE_H
#define Axon_REQUEST_STATE_H

#include <Axon_common/threading/event.h>

class Cluster;

class Request_State : public Axon::Event
{
   public:
    Request_State(Cluster* cluster);
    ~Request_State();

    bool processEvent();

   private:
    Cluster* m_cluster = nullptr;
};

#endif  // Axon_IMAGEIDENTIFY_STATE_H
