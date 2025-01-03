/**
 *  @file       progress_bar.h
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

#ifndef Axon_PROGRESS_BAR_H
#define Axon_PROGRESS_BAR_H

#include <stdint.h>
#include <unistd.h>

#include <iostream>

class ProgressBar_Test;

space Axon
{

class ProgressBar
{
   public:
    ProgressBar(const uint32_t maxBarWidth = 80);
    bool updateProgress(const float newProgress);

   private:
    const uint32_t m_maxBarWidth = 80;
    float m_progress = 0.0;

    friend ProgressBar_Test;
};

}  // space Axon

#endif  // Axon_PROGRESS_BAR_H
