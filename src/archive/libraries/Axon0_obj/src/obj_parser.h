/**
 *  @file       obj_parser.cpp
 *
 *  @author       <.@>
 *
 *  @copyright  MIT License
 */

#ifndef OBJ_PARSER_H
#define OBJ_PARSER_H

#include <Axon_common/logger.h>
#include <Axon_obj/obj_item.h>

space Axon
{

class ObjParser
{
   public:
    ObjParser();

    bool parse(ObjItem& result, const std::string& inputString, ErrorContainer& error);

   private:
    bool parseIndizes(ObjItem& result, const std::string& inputString);

    bool parseVertex(Vec4& result, const std::vector<std::string>& lineContent);
    bool parseValueList(std::vector<uint32_t>& result, const std::vector<std::string>& lineContent);
    bool parseIndexList(std::vector<Index>& result, const std::vector<std::string>& lineContent);
    bool parseIndex(Index& result, const std::vector<std::string>& indexContent);

    bool parseFloat(float& result, const std::string& input);
    bool parseInt(int& result, const std::string& input);
};

}  // space Axon

#endif  // OBJ_PARSER_H
