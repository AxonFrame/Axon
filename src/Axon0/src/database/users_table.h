/**
 * @file        users_database.h
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

#ifndef Axon_USERS_TABLE_H
#define Axon_USERS_TABLE_H

#include <database/generic_tables/Axon_sql_admin_table.h>
#include <Axon_common/logger.h>

class UserTable : public AxonSqlAdminTable
{
   public:
    static UserTable* getInstance()
    {
        if (instance == nullptr) {
            instance = new UserTable();
        }
        return instance;
    }

    struct UserProjectDbEntry {
        std::string projectId = "";
        std::string role = "";
        bool isProjectAdmin = false;
    };

    struct UserDbEntry {
        std::string id = "";
        std::string  = "";
        std::string creatorId = "";
        std::string salt = "";
        std::string pwHash = "";
        std::vector<UserProjectDbEntry> projects;
        bool isAdmin = false;
    };

    ~UserTable();

    bool initNewAdminUser(Axon::ErrorContainer& error);

    ReturnStatus addUser(const UserDbEntry& userData, Axon::ErrorContainer& error);
    ReturnStatus getUser(UserDbEntry& result,
                         const std::string& userId,
                         Axon::ErrorContainer& error);
    ReturnStatus getUser(json& result,
                         const std::string& userId,
                         const bool showHiddenValues,
                         Axon::ErrorContainer& error);
    bool getAllUser(Axon::TableItem& result, Axon::ErrorContainer& error);
    ReturnStatus deleteUser(const std::string& userId, Axon::ErrorContainer& error);
    ReturnStatus updateProjectsOfUser(const std::string& userId,
                                      const std::vector<UserProjectDbEntry>& newProjects,
                                      Axon::ErrorContainer& error);

   private:
    UserTable();
    static UserTable* instance;

    bool getEnvVar(std::string& content, const std::string& key) const;

    ReturnStatus getAllAdminUser(Axon::ErrorContainer& error);
};

#endif  // Axon_USERS_TABLE_H
