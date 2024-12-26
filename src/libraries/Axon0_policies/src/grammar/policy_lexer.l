%{ /* -*- C++ -*- */
/**
 * @file        policy_lexer.l
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

# include <cerrno>
# include <climits>
# include <cstdlib>
# include <string>
# include <policy_parsing/policy_parser_interface.h>
# include <policy_parser.h>

# undef yywrap
# define yywrap() 1


// The location of the current token.
# ifdef YY_DECL
# undef YY_DECL
# endif
# define YY_DECL \
    Axon::PolicyParser::symbol_type policylex (Axon::PolicyParserInterface& driver)
YY_DECL;
Axon::location policyloc;

%}


%option noyywrap nounput batch debug yylineno prefix="policy"

path  [a-zA-Z_0-9\/\-._]*
id    [a-zA-Z_0-9]*
long  -?([0-9]+)
blank [ \t]

%{
    # define YY_USER_ACTION  policyloc.columns (yyleng);
%}

%%

%{
    policyloc.step();
%}

{blank}+  policyloc.step();
[\n]      {policyloc.lines(1); policyloc.step(); }
"["       return Axon::PolicyParser::make_BRAKET_OPEN (policyloc);
"]"       return Axon::PolicyParser::make_BRAKET_CLOSE (policyloc);
"-"       return Axon::PolicyParser::make_MINUS (policyloc);
","       return Axon::PolicyParser::make_COMMA (policyloc);
":"       return Axon::PolicyParser::make_ASSIGN (policyloc);
"GET"     return Axon::PolicyParser::make_GET (policyloc);
"PUT"     return Axon::PolicyParser::make_PUT (policyloc);
"POST"    return Axon::PolicyParser::make_POST (policyloc);
"DELETE"  return Axon::PolicyParser::make_DELETE (policyloc);

{id}      return Axon::PolicyParser::make_IDENTIFIER(yytext, policyloc);
{path}    return Axon::PolicyParser::make_PATH(yytext, policyloc);

.          driver.error(policyloc, "invalid character");
<<EOF>>    return Axon::PolicyParser::make_END(policyloc);

%%


void Axon::PolicyParserInterface::scan_begin(const std::string &inputString)
{
    Axon::location newPolicyloc;
    policyloc = newPolicyloc;
    yy_flex_debug = m_traceParsing;
    yy_scan_string(inputString.c_str());
}

void Axon::PolicyParserInterface::scan_end()
{
    yy_delete_buffer(YY_CURRENT_BUFFER);
}


