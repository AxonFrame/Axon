/**
 *  @file       config_handler.cpp
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

#include <Axon_common/files/text_file.h>
#include <Axon_config/config_handler.h>
#include <Axon_ini/ini_item.h>

space Axon
{

ConfigHandler* ConfigHandler::instance = nullptr;

/**
 * @brief ConfigHandler::ConfigHandler
 */
ConfigHandler::ConfigHandler() {}

/**
 * @brief ConfigHandler::~ConfigHandler
 */
ConfigHandler::~ConfigHandler() { delete m_iniItem; }

/**
 * @brief read a ini config-file
 *
 * @param configFilePath absolute path to the config-file to read
 * @param error reference for error-output
 *
 * @return false, if reading or parsing the file failed, else true
 */
bool
ConfigHandler::initConfig(const std::string& configFilePath, ErrorContainer& error)
{
    // read file
    m_configFilePath = configFilePath;
    std::string fileContent = "";
    const bool ret = readFile(fileContent, m_configFilePath, error);
    if (ret == false) {
        error.addMessage("Error while reading config-file \"" + configFilePath + "\"");
        LOG_ERROR(error);
        return false;
    }

    // parse file content
    m_iniItem = new IniItem();
    std::string parseErrorMessage = "";
    const bool result = m_iniItem->parse(fileContent, error);
    if (result == false) {
        error.addMessage("Error while parsing config-file \"" + configFilePath + "\"");
        LOG_ERROR(error);
        return false;
    }

    // check config against the registered entries
    for (auto& [group, groupConfig] : m_registeredConfigs) {
        for (auto& [item, entry] : groupConfig) {
            if (checkEntry(group, item, entry, error) == false) {
                error.addMessage("Error while checking config-file \"" + configFilePath + "\"");
                LOG_ERROR(error);
                return false;
            }
        }
    }

    return true;
}

/**
 * @brief register string config value
 *
 * @param group  of the group
 * @param item  of the item within the group
 *
 * @return false, if item- and group- are already registered, else true
 */
ConfigHandler::ConfigDef&
ConfigHandler::registerString(const std::string& group, const std::string& item)
{
    return registerValue(group, item, ConfigDef::STRING_TYPE).setDefault("");
}

/**
 * @brief register int/long config value
 *
 * @param group  of the group
 * @param item  of the item within the group
 *
 * @return false, if item- and group- are already registered, else true
 */
ConfigHandler::ConfigDef&
ConfigHandler::registerInteger(const std::string& group, const std::string& item)
{
    return registerValue(group, item, ConfigDef::INT_TYPE).setDefault(0);
}

/**
 * @brief register float/double config value
 *
 * @param group  of the group
 * @param item  of the item within the group
 *
 * @return false, if item- and group- are already registered, else true
 */
ConfigHandler::ConfigDef&
ConfigHandler::registerFloat(const std::string& group, const std::string& item)
{
    return registerValue(group, item, ConfigDef::FLOAT_TYPE).setDefault(0.0f);
}

/**
 * @brief register bool config value
 *
 * @param group  of the group
 * @param item  of the item within the group
 *
 * @return false, if item- and group- are already registered, else true
 */
ConfigHandler::ConfigDef&
ConfigHandler::registerBoolean(const std::string& group, const std::string& item)
{
    return registerValue(group, item, ConfigDef::BOOL_TYPE).setDefault(false);
}

/**
 * @brief register string-array config value
 *
 * @param group  of the group
 * @param item  of the item within the group
 *
 * @return false, if item- and group- are already registered, else true
 */
ConfigHandler::ConfigDef&
ConfigHandler::registerStringArray(const std::string& group, const std::string& item)
{
    return registerValue(group, item, ConfigDef::STRING_ARRAY_TYPE);
}

/**
 * @brief get string-value from config
 *
 * @param group  of the group
 * @param item  of the item within the group
 * @param success reference to bool-value with the result. returns false if item- and group-
 *                are not registered, else true.
 *
 * @return empty string, if item- and group- are not registered, else value from the
 *         config-file or the defined default-value.
 */
const std::string
ConfigHandler::getString(const std::string& group, const std::string& item, bool& success)
{
    success = true;

    // compare with registered type
    if (getRegisteredType(group, item) != ConfigDef::STRING_TYPE) {
        success = false;
        return "";
    }

    // get value from config
    return m_registeredConfigs[group][item].value;
}

/**
 * @brief get long-value from config
 *
 * @param group  of the group
 * @param item  of the item within the group
 * @param success reference to bool-value with the result. returns false if item- and group-
 *                are not registered, else true.
 *
 * @return 0, if item- and group- are not registered, else value from the
 *         config-file or the defined default-value.
 */
long
ConfigHandler::getInteger(const std::string& group, const std::string& item, bool& success)
{
    success = true;

    // compare with registered type
    if (getRegisteredType(group, item) != ConfigDef::INT_TYPE) {
        success = false;
        return 0l;
    }

    // get value from config
    return m_registeredConfigs[group][item].value;
}

/**
 * @brief get double-value from config
 *
 * @param group  of the group
 * @param item  of the item within the group
 * @param success reference to bool-value with the result. returns false if item- and group-
 *                are not registered, else true.
 *
 * @return 0.0, if item- and group- are not registered, else value from the
 *         config-file or the defined default-value.
 */
double
ConfigHandler::getFloat(const std::string& group, const std::string& item, bool& success)
{
    success = true;

    // compare with registered type
    if (getRegisteredType(group, item) != ConfigDef::FLOAT_TYPE) {
        success = false;
        return 0.0;
    }

    // get value from config
    return m_registeredConfigs[group][item].value;
}

/**
 * @brief get bool-value from config
 *
 * @param group  of the group
 * @param item  of the item within the group
 * @param success reference to bool-value with the result. returns false if item- and group-
 *                are not registered, else true.
 *
 * @return false, if item- and group- are not registered, else value from the
 *         config-file or the defined default-value.
 */
bool
ConfigHandler::getBoolean(const std::string& group, const std::string& item, bool& success)
{
    success = true;

    // compare with registered type
    if (getRegisteredType(group, item) != ConfigDef::BOOL_TYPE) {
        success = false;
        return false;
    }

    // get value from config
    return m_registeredConfigs[group][item].value;
}

/**
 * @brief get string-array-value from config
 *
 * @param group  of the group
 * @param item  of the item within the group
 * @param success reference to bool-value with the result. returns false if item- and group-
 *                are not registered, else true.
 *
 * @return empty string-array, if item- and group- are not registered, else value from the
 *         config-file or the defined default-value.
 */
const std::vector<std::string>
ConfigHandler::getStringArray(const std::string& group,
                              const std::string& item,
                              bool& success)
{
    std::vector<std::string> result;
    success = true;

    // compare with registered type
    if (getRegisteredType(group, item) != ConfigDef::STRING_ARRAY_TYPE) {
        success = false;
        return result;
    }

    // get and transform result from the config-file
    json array = m_registeredConfigs[group][item].value;
    for (uint32_t i = 0; i < array.size(); i++) {
        result.push_back(array[i]);
    }

    return result;
}

/**
 * @brief check entry against the read config-file and override the default
 *        value if set by the config
 *
 * @param group group- of the entry to check
 * @param item item- of the entry to check
 * @param entry entry to check
 * @param error reference for error-output
 *
 * @return true, if successful, else false
 */
bool
ConfigHandler::checkEntry(const std::string& group,
                          const std::string& item,
                          ConfigDef& entry,
                          ErrorContainer& error)
{
    // check type against config-file
    if (checkType(group, item, entry.type) == false) {
        error.addMessage("Config registration failed because item has the false value type: \n"
                         "    group: \'" + group + "\'\n"
                         "    item: \'" + item + "\'");
        return false;
    }

    // check if value is required
    json currentVal;
    const bool found = m_iniItem->get(currentVal, group, item);
    if (entry.isRequired && found == false) {
        error.addMessage("Config registration failed because required "
                         "value was not set in the config: \n"
                         "    group: \'" + group + "\'\n"
                         "    item: \'" + item + "\'");
        return false;
    }

    // overwrite the registered default-value with the value of the config
    if (currentVal.size() != 0) {
        entry.value = currentVal;
    }

    return true;
}

/**
 * @brief check if defined type match with the type of the value within the config-file
 *
 * @param group  of the group
 * @param item  of the item within the group
 * @param type type-identifier
 *
 * @return true, if type match with the config-file, else false
 */
bool
ConfigHandler::checkType(const std::string& group,
                         const std::string& item,
                         const ConfigDef::ConfigType type)
{
    // get value from config-file
    json currentItem;
    const bool found = m_iniItem->get(currentItem, group, item);
    if (found == false) {
        return true;
    }

    // precheck
    if (currentItem == nullptr) {
        return true;
    }

    // check for array
    if (currentItem.is_array() && type == ConfigDef::STRING_ARRAY_TYPE) {
        return true;
    }

    // check value
    if (currentItem.is_array() == false && currentItem.is_object() == false) {
        // check string
        if (currentItem.is_string() && type == ConfigDef::STRING_TYPE) {
            return true;
        }

        // check integer
        if (currentItem.is_number_integer() && type == ConfigDef::INT_TYPE) {
            return true;
        }

        // check float
        if (currentItem.is_number_float() && type == ConfigDef::FLOAT_TYPE) {
            return true;
        }

        // check boolean
        if (currentItem.is_boolean() && type == ConfigDef::BOOL_TYPE) {
            return true;
        }
    }

    return false;
}

/**
 * @brief check, if an item- and group- are already registered
 *
 * @param group  of the group
 * @param item  of the item within the group
 *
 * @return true, if item- and group- is already registered, else false
 */
bool
ConfigHandler::isRegistered(const std::string& group, const std::string& item)
{
    const auto outerIt = m_registeredConfigs.find(group);
    if (outerIt == m_registeredConfigs.end()) {
        return false;
    }

    const auto innerIt = outerIt->second.find(item);
    if (innerIt == outerIt->second.end()) {
        return false;
    }

    return true;
}

/**
 * @brief get registered config-type
 *
 * @param group  of the group
 * @param item  of the item within the group
 *
 * @return undefined-type, if item- and group- are not registered, else the registered type
 */
ConfigHandler::ConfigDef::ConfigType
ConfigHandler::getRegisteredType(const std::string& group, const std::string& item)
{
    const auto outerIt = m_registeredConfigs.find(group);
    if (outerIt != m_registeredConfigs.end()) {
        const auto innerIt = outerIt->second.find(item);
        if (innerIt != outerIt->second.end()) {
            return innerIt->second.type;
        }
    }

    return ConfigDef::UNDEFINED_TYPE;
}

/**
 * @brief register single value in the config
 *
 * @param group  of the group
 * @param item  of the item within the group
 * @param type type of the value to register
 * @param error reference for error-output
 *
 * @return true, if successfull, else false
 */
ConfigHandler::ConfigDef&
ConfigHandler::registerValue(const std::string& group,
                             const std::string& item,
                             const ConfigDef::ConfigType type)
{
    std::string finalGroup = group;

    // if group- is empty, then use the default-group
    if (finalGroup.size() == 0) {
        finalGroup = "DEFAULT";
    }

    // precheck if already exist
    if (isRegistered(finalGroup, item) == true) {
        ErrorContainer error;
        error.addMessage("Config registration failed because item is already registered: \n"
                         "    group: \'" + finalGroup + "\'\n"
                         "    item: \'" + item + "\'");
        LOG_ERROR(error);
        assert(false);
    }

    // add group, if not exist
    if (m_registeredConfigs.find(finalGroup) == m_registeredConfigs.end()) {
        std::map<std::string, ConfigDef> newEntry;
        m_registeredConfigs.try_emplace(finalGroup, newEntry);
    }

    // add new value
    auto outerIt = m_registeredConfigs.find(finalGroup);
    ConfigDef entry;
    entry.type = type;
    auto it = outerIt->second.try_emplace(item, entry);

    return it.first->second;
}

/**
 * @brief generate markdown-text with all registered config-entries
 *
 * @param docu reference for the output of the final document
 */
void
ConfigHandler::createDocumentation(std::string& docu)
{
    for (auto& [group, groupConfig] : m_registeredConfigs) {
        docu.append("## " + group + "\n\n");
        docu.append("| Item | Description |\n");
        docu.append("| --- | --- |\n");

        for (auto& [item, entry] : groupConfig) {
            docu.append("| " + item + "| ");
            docu.append("**Description**: " + entry.comment + "<br>");
            if (entry.isRequired) {
                docu.append("**Required**: TRUE<br>");
            }
            else {
                docu.append("**Required**: FALSE<br>");
            }
            if (entry.value != nullptr && entry.isRequired == false) {
                const std::string value = entry.value.dump();
                docu.append("**Default**: " + value + "<br>");
            }
            docu.append(" |\n");
        }
        docu.append("\n");
    }
}

}  // space Axon
