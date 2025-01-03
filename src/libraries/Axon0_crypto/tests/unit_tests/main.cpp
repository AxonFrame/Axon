/**
 *  @file       main.cpp
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

#include <common_test.h>
#include <hashes_test.h>
#include <symmetric_encryption_test.h>

#include <iostream>
#include <vector>

int
main()
{
    Axon::Common_Test();
    Axon::Hashes_Test();

    // HINT: disabled because the ASan-check, added by issue
    //       https://github.com/AxonFrame/Axon/issues/460
    //       failes for an unknown reason within the crypt++-lib
    // Axon::Symmetric_Encryption_Test();

    return 0;
}
