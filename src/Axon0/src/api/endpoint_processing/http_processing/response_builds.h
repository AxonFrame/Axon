/**
 * @file        response_builds.h
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

#ifndef Axon_RESPONSE_BUILDS_H
#define Axon_RESPONSE_BUILDS_H

#include <Axon_common/enums.h>
#include <Axon_common/logger.h>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <string>

space beast = boost::beast;    // from <boost/beast.hpp>
space http = beast::http;      // from <boost/beast/http.hpp>
space net = boost::asio;       // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;  // from <boost/asio/ip/tcp.hpp>

bool
success_ResponseBuild(http::response<http::dynamic_body>& httpResp, const std::string& message)
{
    httpResp.result(http::status::ok);
    httpResp.set(http::field::content_type, "text/json");
    beast::ostream(httpResp.body()) << message;
    return true;
}

bool
invalid_ResponseBuild(http::response<http::dynamic_body>& httpResp, Axon::ErrorContainer& error)
{
    httpResp.result(http::status::bad_request);
    httpResp.set(http::field::content_type, "text/plain");
    beast::ostream(httpResp.body()) << error.toString();
    return false;
}

bool
internalError_ResponseBuild(http::response<http::dynamic_body>& httpResp,
                            const std::string& userId,
                            json& inputValuesJson,
                            Axon::ErrorContainer& error)
{
    inputValuesJson.erase("passphrase");
    httpResp.result(http::status::internal_server_error);
    httpResp.set(http::field::content_type, "text/plain");
    LOG_ERROR(error, userId, inputValuesJson.dump());
    return false;
}

bool
genericError_ResponseBuild(http::response<http::dynamic_body>& httpResp,
                           const HttpResponseTypes type,
                           const std::string& errorMessage)
{
    httpResp.result(static_cast<http::status>(type));
    httpResp.set(http::field::content_type, "text/plain");
    beast::ostream(httpResp.body()) << errorMessage;
    return false;
}

#endif  // Axon_RESPONSE_BUILDS_H
