/**
 * @file        processing_test.cpp
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

#include "processing_test.h"

#include <core/cluster/cluster.h>
#include <core/cluster/cluster_init.h>
#include <core/cluster/objects.h>
#include <core/processing/cpu/processing.h>

Processing_Test::Processing_Test() : Axon::CompareTestHelper("Processing_Test") {}
