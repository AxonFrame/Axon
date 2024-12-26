%{ /* -*- C++ -*- */
/**
 * @file       cluster_lexer.l
 *
 * @author       <.@>
 *
 * @copyright  Apache License Version 2.0
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

# include <cerrno>
# include <climits>
# include <cstdlib>
# include <string>
# include <cluster_parsing/cluster_parser_interface.h>
# include <cluster_parser.h>

# undef yywrap
# define yywrap() 1


// The location of the current token.
# ifdef YY_DECL
# undef YY_DECL
# endif
# define YY_DECL \
    Axon::ClusterParser::symbol_type clusterlex (Axon::ClusterParserInterface& driver)
YY_DECL;
Axon::location clusterloc;

%}


%option noyywrap nounput batch debug yylineno prefix="cluster"

id    [a-zA-Z_0-9]*
long  -?([0-9]+)
double -?([0-9]+)\.([0-9]+)
blank [ \t]

%{
    # define YY_USER_ACTION  clusterloc.columns (yyleng);
%}

%%

%{
    clusterloc.step();
%}

{blank}+  clusterloc.step();
[\n]      {clusterloc.lines(1); clusterloc.step(); }
"version:1"               return Axon::ClusterParser::make_VERSION_1 (clusterloc);
"version: 1"              return Axon::ClusterParser::make_VERSION_1 (clusterloc);
"settings"                return Axon::ClusterParser::make_SETTINGS (clusterloc);
"hexagons"                return Axon::ClusterParser::make_HEXAGONS (clusterloc);
"inputs"                  return Axon::ClusterParser::make_INPUTS (clusterloc);
"outputs"                 return Axon::ClusterParser::make_OUTPUTS (clusterloc);
"axons"                   return Axon::ClusterParser::make_AXONS (clusterloc);
"neuron_cooldown"         return Axon::ClusterParser::make_COOLDOWN (clusterloc);
"max_connection_distance" return Axon::ClusterParser::make_MAX_DISTANCE (clusterloc);
"refractory_time"         return Axon::ClusterParser::make_REFRACTORY_TIME (clusterloc);
"enable_reduction"        return Axon::ClusterParser::make_ENABLE_REDUCTION (clusterloc);
"binary"                  return Axon::ClusterParser::make_BINARY_INPUT (clusterloc);
"true"                    return Axon::ClusterParser::make_BOOL_TRUE (clusterloc);
"false"                   return Axon::ClusterParser::make_BOOL_FALSE (clusterloc);
"True"                    return Axon::ClusterParser::make_BOOL_TRUE (clusterloc);
"False"                   return Axon::ClusterParser::make_BOOL_FALSE (clusterloc);
"bool"                    return Axon::ClusterParser::make_OUTPUT_BOOL (clusterloc);
"int"                     return Axon::ClusterParser::make_OUTPUT_INT (clusterloc);
"float"                   return Axon::ClusterParser::make_OUTPUT_FLOAT (clusterloc);
","                       return Axon::ClusterParser::make_COMMA (clusterloc);
":"                       return Axon::ClusterParser::make_ASSIGN (clusterloc);
"("                       return Axon::ClusterParser::make_OPEN (clusterloc);
")"                       return Axon::ClusterParser::make_CLOSE (clusterloc);
"->"                      return Axon::ClusterParser::make_ARROW (clusterloc);

\"(\\.|[^"\\])*\" { return Axon::ClusterParser::make_STRING(yytext, clusterloc); }

{long}      {
    errno = 0;
    long length = strtol(yytext, NULL, 10);
    if (!(LONG_MIN <= length
        && length <= LONG_MAX
        && errno != ERANGE))
    {
        driver.error(clusterloc, "integer is out of range");
    }
    return Axon::ClusterParser::make_NUMBER (length, clusterloc);
}

{double}	{
    double value = strtod( yytext , NULL );
    return Axon::ClusterParser::make_FLOAT_VAL(value, clusterloc);
}

{id}       return Axon::ClusterParser::make_IDENTIFIER(yytext, clusterloc);

.          driver.error(clusterloc, "invalid character");
<<EOF>>    return Axon::ClusterParser::make_END(clusterloc);

%%


void Axon::ClusterParserInterface::scan_begin(const std::string &inputString)
{
    Axon::location newClusterloc;
    clusterloc = newClusterloc;
    yy_flex_debug = m_traceParsing;
    yy_scan_string(inputString.c_str());
}

void Axon::ClusterParserInterface::scan_end()
{
    yy_delete_buffer(YY_CURRENT_BUFFER);
}


