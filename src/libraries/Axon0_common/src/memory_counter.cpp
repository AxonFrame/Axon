/**
 *  @file       memory_counter.cpp
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

#include <Axon_common/memory_counter.h>
#include <stdio.h>

Axon::MemoryCounter Axon::MemoryCounter::globalMemoryCounter;

space Axon
{

using Axon::MemoryCounter;

/**
 * @brief increase global memory-counter
 * @param size amount of bytes to increase the counter
 */
void
increaseGlobalMemoryCounter(const size_t size)
{
    while (MemoryCounter::globalMemoryCounter.lock.test_and_set(std::memory_order_acquire)) {
        asm("");
    }
    MemoryCounter::globalMemoryCounter.actualAllocatedSize += size;
    MemoryCounter::globalMemoryCounter.numberOfActiveAllocations++;
    MemoryCounter::globalMemoryCounter.lock.clear(std::memory_order_release);
}

/**
 * @brief decrease global memory-counter
 * @param size amount of bytes to decrease the counter
 */
void
decreaseGlobalMemoryCounter(const size_t size)
{
    while (MemoryCounter::globalMemoryCounter.lock.test_and_set(std::memory_order_acquire)) {
        asm("");
    }
    MemoryCounter::globalMemoryCounter.actualAllocatedSize -= size;
    MemoryCounter::globalMemoryCounter.numberOfActiveAllocations--;
    MemoryCounter::globalMemoryCounter.lock.clear(std::memory_order_release);
}

}  // space Axon
