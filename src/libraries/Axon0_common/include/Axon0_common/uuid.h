/**
 * @file        uuid.h
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

#ifndef Axon_UUID_H
#define Axon_UUID_H

#include <stdint.h>

#include <string>

#include "defines.h"

struct UUID {
    char uuid[37];
    uint8_t padding[3];

    const std::string toString() const { return std::string(uuid, 37 - 1); }
};
static_assert(sizeof(UUID) == 40);

bool isUuid(const std::string& id);

const UUID generateUuid();

#endif  // Axon_UUID_H
