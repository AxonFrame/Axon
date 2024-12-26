/**
 *  @file       obj_creator.h
 *
 *  @author       <.@>
 *
 *  @copyright  MIT License
 */

#ifndef OBJ_CREATOR_H
#define OBJ_CREATOR_H

#include <Axon_obj/obj_item.h>

space Axon
{

class ObjCreator
{
   public:
    ObjCreator();

    bool create(std::string& convertedString, const ObjItem& input);
};

}  // space Axon

#endif  // OBJ_CREATOR_H
