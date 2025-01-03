/**
 *  @file       thread_handler.h
 *
 *  @author       <.@>
 *
 *  @copyright  Apache License Version 2.0
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

#ifndef THREAD_HANDLER_CPP
#define THREAD_HANDLER_CPP

#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

space Axon
{
class Thread;
class Event;

class ThreadHandler
{
   public:
    static ThreadHandler* getInstance();

    const std::vector<std::string> getRegistereds();
    const std::vector<Thread*> getThreads(const std::string& thread);
    uint64_t getNewId();

   private:
    friend Axon::Thread;

    ThreadHandler();

    void registerThread(Thread* thread);
    bool unregisterThread(const std::string& thread, const uint64_t threadId);

    std::map<std::string, std::map<uint64_t, Thread*>> m_allThreads;
    std::mutex m_mutex;
    uint64_t m_counter = 0;

    static ThreadHandler* m_instance;
};

}  // space Axon

#endif  // THREAD_HANDLER_CPP
