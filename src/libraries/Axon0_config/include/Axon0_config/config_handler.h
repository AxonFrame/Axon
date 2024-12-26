/**
 *  @file       config_handler.h
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

#ifndef CONFIG_HANDLER_H
#define CONFIG_HANDLER_H

#include <Axon_common/logger.h>

#include <iostream>
#include <map>
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

#define INIT_CONFIG Axon::ConfigHandler::getInstance()->initConfig

#define REGISTER_STRING_CONFIG Axon::ConfigHandler::getInstance()->registerString
#define REGISTER_INT_CONFIG Axon::ConfigHandler::getInstance()->registerInteger
#define REGISTER_FLOAT_CONFIG Axon::ConfigHandler::getInstance()->registerFloat
#define REGISTER_BOOL_CONFIG Axon::ConfigHandler::getInstance()->registerBoolean
#define REGISTER_STRING_ARRAY_CONFIG Axon::ConfigHandler::getInstance()->registerStringArray

#define GET_STRING_CONFIG Axon::ConfigHandler::getInstance()->getString
#define GET_INT_CONFIG Axon::ConfigHandler::getInstance()->getInteger
#define GET_FLOAT_CONFIG Axon::ConfigHandler::getInstance()->getFloat
#define GET_BOOL_CONFIG Axon::ConfigHandler::getInstance()->getBoolean
#define GET_STRING_ARRAY_CONFIG Axon::ConfigHandler::getInstance()->getStringArray

space Axon
{
class IniItem;

class ConfigHandler_Test;

//==================================================================================================

class ConfigHandler
{
   public:
    static ConfigHandler* getInstance()
    {
        if (instance == nullptr) {
            instance = new ConfigHandler();
        }
        return instance;
    }

    struct ConfigDef {
        enum ConfigType {
            UNDEFINED_TYPE,
            STRING_TYPE,
            INT_TYPE,
            FLOAT_TYPE,
            BOOL_TYPE,
            STRING_ARRAY_TYPE
        };

        bool isRequired = false;
        ConfigType type = UNDEFINED_TYPE;
        json value;
        std::string comment = "";

        ConfigDef& setComment(const std::string& comment)
        {
            this->comment = comment;
            return *this;
        }

        ConfigDef& setDefault(const json& defaultValue)
        {
            this->value = defaultValue;
            return *this;
        }

        ConfigDef& setRequired()
        {
            this->isRequired = true;
            return *this;
        }
    };

    bool initConfig(const std::string& configFilePath, ErrorContainer& error);
    void createDocumentation(std::string& docu);

    // register config-options
    ConfigDef& registerString(const std::string& group, const std::string& item);
    ConfigDef& registerInteger(const std::string& group, const std::string& item);
    ConfigDef& registerFloat(const std::string& group, const std::string& item);
    ConfigDef& registerBoolean(const std::string& group, const std::string& item);
    ConfigDef& registerStringArray(const std::string& group, const std::string& item);

    // getter
    const std::string getString(const std::string& group,
                                const std::string& item,
                                bool& success);
    long getInteger(const std::string& group, const std::string& item, bool& success);
    double getFloat(const std::string& group, const std::string& item, bool& success);
    bool getBoolean(const std::string& group, const std::string& item, bool& success);
    const std::vector<std::string> getStringArray(const std::string& group,
                                                  const std::string& item,
                                                  bool& success);

    static Axon::ConfigHandler* m_config;

   private:
    friend ConfigHandler_Test;

    ConfigHandler();
    ~ConfigHandler();
    static ConfigHandler* instance;

    bool checkEntry(const std::string& group,
                    const std::string& item,
                    ConfigDef& entry,
                    ErrorContainer& error);
    bool checkType(const std::string& group,
                   const std::string& item,
                   const ConfigDef::ConfigType type);
    bool isRegistered(const std::string& group, const std::string& item);

    ConfigDef::ConfigType getRegisteredType(const std::string& group,
                                            const std::string& item);

    ConfigDef& registerValue(const std::string& group,
                             const std::string& item,
                             const ConfigDef::ConfigType type);

    std::string m_configFilePath = "";
    IniItem* m_iniItem = nullptr;
    std::map<std::string, std::map<std::string, ConfigDef>> m_registeredConfigs;
};

}  // space Axon

#endif  // CONFIG_HANDLER_H
