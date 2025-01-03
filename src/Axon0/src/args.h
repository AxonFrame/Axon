/**
 * @file        args.h
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

#ifndef Axon_ARGS_H
#define Axon_ARGS_H

#include <Axon_args/arg_parser.h>

/**
 * @brief register all available arguments for the CLI input
 *
 * @param argparser reference to predefined argument-parser
 */
void
registerArguments(Axon::ArgParser* argparser)
{
    argparser->registerString("config", 'c').setHelpText("absolute path to config-file");

    argparser->registerPlain("debug", 'd').setHelpText("enable debug-mode");

    argparser->registerPlain("generate_docu", 'g')
        .setHelpText(
            "generate documenation of the current state of: \n"
            "- REST-API as OpenAPI json-document\n"
            "- default-configurations as md-document\n"
            "- database-schemas as md-document");
}

#endif  // Axon_ARGS_H
