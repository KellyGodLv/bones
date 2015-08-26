﻿#ifndef BONES_LUA_ROOT_H_
#define BONES_LUA_ROOT_H_

#include "lua_object.h"
#include "core/root.h"

namespace bones
{

class LuaRoot : public LuaObject<BonesRoot, Root>, 
                public Root::Delegate
{
public:
    LuaRoot(Root *);

    ~LuaRoot();

    void addNotify(const char * notify_name, const char * mod, const char * func);

    void setListener(Listener * listener) override;

    bool isDirty() const override;

    BonesRect getDirtyRect() const override;

    void draw() override;

    HDC dc() const override;

    void handleMouse(UINT msg, WPARAM wparam, LPARAM lparam) override;

    void handleKey(UINT msg, WPARAM wparam, LPARAM lparam) override;

    void handleFocus(UINT msg, WPARAM wparam, LPARAM lparam) override;

    void handleComposition(UINT msg, WPARAM wparam, LPARAM lparam) override;

    void handleWheel(UINT msg, WPARAM wparam, LPARAM lparam) override;

    void requestFocus(Ref * sender) override;

    void invalidRect(Ref * sender, const Rect & rect) override;

    void changeCursor(Ref * sender, Cursor cursor) override;

    void onSizeChanged(Ref * sender, const Size & size) override;

    void onPositionChanged(Ref * sender, const Point & loc) override;
private:
    Listener * listener_;
};


}


#endif