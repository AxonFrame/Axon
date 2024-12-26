// Apache License Version 2.0

// Copyright 2020  

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * Initialize all tables by setting them in inactive-state
 */
function resetAllTabs() 
{
    let i, tabcontent, tablinks;

    // Get all elements with class="tabcontent" and hide them
    tabcontent = document.getElementsByClass("tabcontent");
    for(i = 0; i < tabcontent.length; i++) {
        tabcontent[i].style.display = "none";
    }

    // Get all elements with class="tablinks" and remove the class "active"
    tablinks = document.getElementsByClass("tablinks");
    for(i = 0; i < tablinks.length; i++) {
        tablinks[i].class = tablinks[i].class.replace(" active", "");
    }
}

/**
 * Select a tab in a tabbbar
 *
 * @param {evt} click-event
 * @param {tab}  of the tab to selet
 */
function selectTabbarEntry(evt, tab) 
{
    resetAllTabs();

    // Show the current tab, and add an "active" class to the button that opened the tab
    document.getElementById(tab).style.display = "block";
    evt.currentTarget.class += " active";
} 

/**
 * Select the default-tab of a tabbar for initializing
 */
function activateDefaultTab() 
{
    resetAllTabs();

    document.getElementById(defaultTab).style.display = "block";
    tablinks = document.getElementsByClass("tablinks");
    tablinks[defaultTabIndex].class += " active";
}
