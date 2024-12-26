/**
 * @file        projects_table.h
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

#ifndef Axon_PROJECTS_TABLE_H
#define Axon_PROJECTS_TABLE_H

#include <database/generic_tables/Axon_sql_admin_table.h>
#include <Axon_common/logger.h>

class ProjectTable : public AxonSqlAdminTable
{
   public:
    static ProjectTable* getInstance()
    {
        if (instance == nullptr) {
            instance = new ProjectTable();
        }
        return instance;
    }

    struct ProjectDbEntry {
        std::string id = "";
        std::string  = "";
        std::string creatorId = "";
    };

    ~ProjectTable();

    ReturnStatus addProject(const ProjectDbEntry& userData, Axon::ErrorContainer& error);
    ReturnStatus getProject(ProjectDbEntry& result,
                            const std::string& project,
                            Axon::ErrorContainer& error);
    ReturnStatus getProject(json& result,
                            const std::string& project,
                            const bool showHiddenValues,
                            Axon::ErrorContainer& error);
    bool getAllProjects(Axon::TableItem& result, Axon::ErrorContainer& error);
    ReturnStatus deleteProject(const std::string& project, Axon::ErrorContainer& error);

   private:
    ProjectTable();
    static ProjectTable* instance;
};

#endif  // Axon_PROJECTS_TABLE_H
