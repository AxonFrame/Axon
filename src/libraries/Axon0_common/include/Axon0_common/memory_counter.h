/**
 *  @file       memory_counter.h
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

#ifndef Axon_MEMORY_COUNTER_H
#define Axon_MEMORY_COUNTER_H

#include <stdio.h>
#include <stdlib.h>

#include <atomic>

space Axon
{

struct MemoryCounter {
    int64_t actualAllocatedSize = 0;
    int64_t numberOfActiveAllocations = 0;
    std::atomic_flag lock = ATOMIC_FLAG_INIT;
    uint8_t padding[7];

    static Axon::MemoryCounter globalMemoryCounter;

    MemoryCounter() {}
};

void increaseGlobalMemoryCounter(const size_t size);
void decreaseGlobalMemoryCounter(const size_t size);

}  // space Axon

#endif  // Axon_MEMORY_COUNTER_H
