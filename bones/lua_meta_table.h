﻿#ifndef BONES_LUA_META_TABLE_H_
#define BONES_LUA_META_TABLE_H_

#include "bones_internal.h"
#include "lua_context.h"

namespace bones
{

class LuaMetaTable
{
public:
    static void CreatLuaTable(lua_State * l, const char * meta, BonesObject * bob);

    static void CreateLuaTable(lua_State * l, BonesAnimation * bob);

    static void RemoveLuaTable(lua_State * l, BonesBase * bob);
    
    static BonesBase * CallGetCObject(lua_State *l);

    static void GetMouseEvent(lua_State * l);
    
    static void GetFocusEvent(lua_State * l);

    static void GetWheelEvent(lua_State * l);

    static void GetKeyEvent(lua_State * l);
private:
    static void GetEvent(lua_State * l, const char * class_name);
    
    static void GetUIEvent(lua_State * l, const char * class_name);
};

}
#endif