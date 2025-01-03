﻿/**
 * @file        generate_rest_api_docu.cpp
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

#include "generate_rest_api_docu.h"

#include <api/endpoint_processing/blossom.h>
#include <api/endpoint_processing/http_processing/http_processing.h>
#include <api/endpoint_processing/http_server.h>
#include <api/endpoint_processing/http_websocket_thread.h>
#include <Axon_common/functions/file_functions.h>
#include <Axon_common/functions/string_functions.h>
#include <Axon_crypto/common.h>
#include <Axon_root.h>

std::map<HttpResponseTypes, std::string> responseMessage = {
    {OK_RTYPE, "Successful response."},
    {CONFLICT_RTYPE, "Resource with  or id already exist."},
    {BAD_REQUEST_RTYPE, "Request has invalid syntax."},
    {UNAUTHORIZED_RTYPE, "Information for authentication are missing or are invalid"},
    {NOT_FOUND_RTYPE, "The requested resource was not found."},
    {INTERNAL_SERVER_ERROR_RTYPE,
     "Something internally went wrong. "
     "Check the server-internal logs for more information."},
};

/**
 * @brief generate OpenAPI-documentation from source
 *
 * @param docu reference to the resulting documenation-output
 */
void
createOpenApiDocumentation(std::string& docu)
{
    AxonRoot::httpServer = new HttpServer("0.0.0.0", 12345);

    json result;
    result["openapi"] = "3.0.0";

    json info;
    info["title"] = "API documentation";
    info["version"] = "unreleased";
    result["info"] = info;

    json contact;
    contact[""] = " ";
    contact[""] = ".@";
    result["contact"] = contact;

    json license;
    license[""] = "Apache 2.0";
    license["url"] = "https://www.apache.org/licenses/LICENSE-2.0.html";
    result["license"] = license;

    json paths;
    generateEndpointDocu(paths);
    result["paths"] = paths;

    docu = result.dump(4, ' ');
}

/**
 * @brief convert responses of endpoints to open-API-json and add it to the output
 *
 * @param responses reference to the output
 * @param blossom pointer to the endpoints to read the reponses of the endpoint
 */
void
addResponsess(json& responses, Blossom* blossom)
{
    json resp200;
    resp200["description"] = responseMessage[OK_RTYPE];
    json content;
    json jsonApplication;
    json schema;
    schema["type"] = "object";
    createBodyParams(schema, blossom->getOutputValidationMap(), false);
    jsonApplication["schema"] = schema;
    content["application/json"] = jsonApplication;
    resp200["content"] = content;
    responses["200"] = resp200;

    for (const HttpResponseTypes code : blossom->errorCodes) {
        json errorResponse;
        errorResponse["description"] = responseMessage[code];
        json content;
        json jsonApplication;
        json schema;
        schema["type"] = "string";
        jsonApplication["schema"] = schema;
        content["text/plain"] = jsonApplication;
        errorResponse["content"] = content;
        responses[std::to_string(code)] = errorResponse;
    }
}

/**
 * @brief add token-requirement to documeation, if endpoint requires a token for access
 *
 * @param parameters reference to the output
 */
void
addTokenRequirement(json& parameters)
{
    json param;
    param["in"] = "header";
    param["description"] = "JWT-Token for authentication";
    param[""] = "X-Auth-Token";
    param["required"] = true;

    json schema;
    schema["type"] = "string";

    param["schema"] = schema;
    parameters.push_back(param);
}

/**
 * @brief convert query-parameters
 *
 * @param parameters reference to the output of the parameters
 * @param defMap map with all field to ducument
 */
void
createQueryParams(json& parameters, const std::map<std::string, FieldDef>* defMap)
{
    for (const auto& [field, fieldDef] : *defMap) {
        const FieldType fieldType = fieldDef.fieldType;
        const std::string comment = fieldDef.comment;
        const bool isRequired = fieldDef.isRequired;
        const json defaultVal = fieldDef.defaultVal;
        const json matchVal = fieldDef.match;
        std::string regexVal = fieldDef.regex;
        const long lowerLimit = fieldDef.lowerLimit;
        const long upperLimit = fieldDef.upperLimit;

        json param;
        param["in"] = "query";
        param[""] = field;

        // required
        if (isRequired) {
            param["required"] = isRequired;
        }

        // comment
        if (comment != "") {
            param["description"] = comment;
        }

        json schema;

        // type
        if (fieldType == SAKURA_MAP_TYPE) {
            schema["type"] = "object";
        }
        else if (fieldType == SAKURA_ARRAY_TYPE) {
            schema["type"] = "array";
        }
        else if (fieldType == SAKURA_BOOL_TYPE) {
            schema["type"] = "boolean";
        }
        else if (fieldType == SAKURA_INT_TYPE) {
            schema["type"] = "integer";
        }
        else if (fieldType == SAKURA_FLOAT_TYPE) {
            schema["type"] = "number";
        }
        else if (fieldType == SAKURA_STRING_TYPE) {
            schema["type"] = "string";
        }

        // default
        if (defaultVal != nullptr && isRequired == false) {
            schema["default"] = defaultVal;
        }

        // match
        if (regexVal != "") {
            schema["pattern"] = regexVal;
        }

        // border
        if (lowerLimit != 0 || upperLimit != 0) {
            if (fieldType == SAKURA_INT_TYPE) {
                schema["minimum"] = std::to_string(lowerLimit);
                schema["maximum"] = std::to_string(upperLimit);
            }
            if (fieldType == SAKURA_STRING_TYPE) {
                schema["minLength"] = std::to_string(lowerLimit);
                schema["maxLength"] = std::to_string(upperLimit);
            }
        }

        // match
        if (matchVal != nullptr) {
            json match;
            std::string content = matchVal;
            match.push_back(content);
            schema["enum"] = match;
        }

        param["schema"] = schema;
        parameters.push_back(param);
    }
}

/**
 * @brief generate documenation for all fields
 *
 * @param docu reference to the complete document
 * @param defMap map with all field to ducument
 * @param isRequest true to say that the actual field is a request-field
 */
void
createBodyParams(json& schema, const std::map<std::string, FieldDef>* defMap, const bool isRequest)
{
    std::vector<std::string> requiredFields;

    json properties;
    for (const auto& [id, fieldDef] : *defMap) {
        json temp;

        const std::string field = id;
        const FieldType fieldType = fieldDef.fieldType;
        const std::string comment = fieldDef.comment;
        const bool isRequired = fieldDef.isRequired;
        const json defaultVal = fieldDef.defaultVal;
        const json matchVal = fieldDef.match;
        std::string regexVal = fieldDef.regex;
        const long lowerLimit = fieldDef.lowerLimit;
        const long upperLimit = fieldDef.upperLimit;

        // type
        if (fieldType == SAKURA_MAP_TYPE) {
            temp["type"] = "object";
        }
        else if (fieldType == SAKURA_ARRAY_TYPE) {
            temp["type"] = "array";
            json array;
            array["type"] = "string";

            // match
            if (matchVal != nullptr) {
                json match = json::parse(matchVal.dump(), nullptr, false);
                if (match.is_discarded()) {
                    array["enum"] = json(match);
                }
                else {
                    array["enum"] = match;
                }
            }

            temp["items"] = array;
        }
        else if (fieldType == SAKURA_BOOL_TYPE) {
            temp["type"] = "boolean";
        }
        else if (fieldType == SAKURA_INT_TYPE) {
            temp["type"] = "integer";
        }
        else if (fieldType == SAKURA_FLOAT_TYPE) {
            temp["type"] = "number";
        }
        else if (fieldType == SAKURA_STRING_TYPE) {
            temp["type"] = "string";
        }

        // comment
        if (comment != "") {
            temp["description"] = comment;
        }

        if (isRequest) {
            // required
            if (isRequired) {
                requiredFields.push_back(field);
            }

            // default
            if (defaultVal != nullptr && isRequired == false) {
                temp["default"] = defaultVal;
            }

            // match
            if (regexVal != "") {
                temp["pattern"] = regexVal;
            }

            // border
            if (lowerLimit != 0 || upperLimit != 0) {
                if (fieldType == SAKURA_INT_TYPE) {
                    temp["minimum"] = std::to_string(lowerLimit);
                    temp["maximum"] = std::to_string(upperLimit);
                }
                if (fieldType == SAKURA_STRING_TYPE) {
                    temp["minLength"] = std::to_string(lowerLimit);
                    temp["maxLength"] = std::to_string(upperLimit);
                }
            }

            // match
            if (matchVal != nullptr) {
                json match;
                std::string content = matchVal;
                Axon::replaceSubstring(content, "\"", "\\\"");
                match.push_back(content);
                temp["enum"] = match;
            }
        }

        properties[field] = temp;
    }

    if (properties.is_null() == false) {
        schema["properties"] = properties;
    }

    if (isRequest) {
        json required;
        for (const std::string& field : requiredFields) {
            required.push_back(field);
        }
        schema["required"] = required;
    }
}

/**
 * @brief generate docu of all endpoints
 *
 * @param result reference for the output
 */
void
generateEndpointDocu(json& result)
{
    HttpProcessing* httpProcessing = AxonRoot::httpServer->httpProcessing;
    for (const auto& [endpointPath, httpDef] : httpProcessing->endpointRules) {
        // add endpoint
        json endpoint;

        for (const auto& [type, endpointEntry] : httpDef) {
            json endpointType;

            Blossom* blossom
                = AxonRoot::httpServer->httpProcessing->mapEndpoint(endpointPath, type);
            if (blossom == nullptr) {
                // TODO: handle error
                return;
            }

            // add comment/describtion
            endpointType["summary"] = blossom->comment;

            json tags;
            tags.push_back(blossom->tag);
            endpointType["tags"] = tags;

            json parameters;

            if (blossom->requiresAuthToken) {
                addTokenRequirement(parameters);
            }

            if (type == POST_TYPE || type == PUT_TYPE) {
                json requestBody;
                requestBody["required"] = true;
                json content;
                json jsonApplication;
                json schema;
                schema["type"] = "object";
                createBodyParams(schema, blossom->getInputValidationMap(), true);
                jsonApplication["schema"] = schema;
                content["application/json"] = jsonApplication;
                requestBody["content"] = content;
                endpointType["requestBody"] = requestBody;
            }

            if (type == GET_TYPE || type == DELETE_TYPE) {
                createQueryParams(parameters, blossom->getInputValidationMap());
            }

            if (parameters.is_null() == false) {
                endpointType["parameters"] = parameters;
            }

            // add response-codes
            json responses;
            addResponsess(responses, blossom);
            endpointType["responses"] = responses;

            // add http-type
            if (type == GET_TYPE) {
                endpoint["get"] = endpointType;
            }
            else if (type == POST_TYPE) {
                endpoint["post"] = endpointType;
            }
            else if (type == DELETE_TYPE) {
                endpoint["delete"] = endpointType;
            }
            else if (type == PUT_TYPE) {
                endpoint["put"] = endpointType;
            }
        }

        result[endpointPath] = endpoint;
    }
}
