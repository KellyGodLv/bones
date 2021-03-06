﻿
#include "mouse_controller.h"
#include "root.h"
#include "event_dispatcher.h"
#include "view.h"
#include "rect.h"



namespace bones
{

MouseController::MouseController(Root * root)
:root_(root)
{
    ;
}


void MouseController::removed(View * n)
{
    if (n->contains(capture_.get()))
        shiftCapture(nullptr);

    if (n->contains(over_.get()))
        shiftOver(nullptr);
}

void MouseController::shiftIfNecessary()
{
    if (capture_ &&
        (!capture_->isMouseable() || !root_->contains(capture_.get())))
        shiftCapture(nullptr);
    if (over_ &&
        (!over_->isMouseable() || !root_->contains(over_.get())))
        shiftOver(nullptr);

    auto target = getTargetByPos(last_mouse_point_, false);
    if ((target != over_.get()))
    {
        shiftOver(target);
        if (!target)
            return;
        MouseEvent e(kET_MOUSE_MOVE, kMB_NONE, target, target->mapToLocal(last_mouse_point_), last_mouse_point_, 0);
        EventDispatcher::Push(e);
    }
}

void MouseController::handleEvent(MouseEvent & e)
{
    clearIfNecessary();
    if ( e.type() < kET_MOUSE_ENTER || e.type() > kET_MOUSE_LEAVE) 
        return;

    if (kET_MOUSE_LEAVE == e.type())
    {
        shiftCapture(nullptr);
        shiftOver(nullptr);
        last_mouse_point_.set(-1, -1);
        return;
    }
    else if (kET_MOUSE_ENTER == e.type())
    {
        shiftOver(root_);
        last_mouse_point_.set(0, 0);
        return;
    }

    View * target = e.target();
    assert(target == root_);
    if (target == root_)
    {
        target = getTargetByPos(e.getLoc(), false);
        //注意处理target == null的情况
        last_mouse_point_ = e.getLoc();
    }

    if (kET_MOUSE_DOWN == e.type())
    {
        //鼠标按下则发生焦点切换事件
        root_->shiftFocus(target);
        //如果是左键按下 自动capture
        if (e.isLeftMouse())
            shiftCapture(target);
    }
    shiftOver(target);
    if (target)
    {
        MouseEvent me(e.type(), e.button(), target, target->mapToLocal(e.getLoc()),
            e.getLoc(), e.getFlags());
        EventDispatcher::Push(me);
    }
        
    if (kET_MOUSE_UP == e.type() && e.isLeftMouse())
    {//左键弹起 取消capture
        shiftCapture(nullptr);
        //由于capture的原因 弹起时鼠标已经进入其它控件 其它控件需要有个明确的mouse move消息
        shiftIfNecessary();
    }
}

void MouseController::handleWheel(WheelEvent & e)
{//滚动是忽略capture
    clearIfNecessary();

    View * target = e.target();
    if (target == root_)
        target = getTargetByPos(e.getLoc(), true);
    if (!target)
        return;

    WheelEvent we(e.type(), target, e.dx(), e.dy(),
        target->mapToLocal(e.getLoc()), e.getLoc(),
        e.getFlags());
    EventDispatcher::Push(we);

    shiftIfNecessary();
    //暂时先这么处理 因为滚动的时候可能离开控件所以 需要改变鼠标样式之类
    //MouseEvent me(kET_MOUSE_MOVE, kMB_NONE, root_, root_->mapToLocal(last_mouse_point_), last_mouse_point_, 0);
    //handleEvent(me);
    //if (!capture_)
    //{//如果没有capture 可能滚动到新的view里 需要shiftOver
    //    shiftIfNecessary();
    //}
}

void MouseController::shiftOver(View * n)
{
    RefPtr<View> target;
    target.reset(n);
    if (over_ != target)
    {
        EventDispatcher dispatcher;
        EventDispatcher::Path old_path;
        EventDispatcher::GetPath(over_.get(), old_path);
        EventDispatcher::Path new_path;
        EventDispatcher::GetPath(n, new_path);
        if (over_)
        {
            Point empty;
            MouseEvent me(kET_MOUSE_LEAVE, kMB_NONE, over_.get(), empty, empty, 0);
            dispatcher.run(me, old_path);
        }
        root_->restoreCursor();
        over_ = target;

        if (over_)
        {
            Point empty;
            MouseEvent me(kET_MOUSE_ENTER, kMB_NONE, over_.get(), empty, empty, 0);
            dispatcher.run(me, new_path);
        }
    }
}

View * MouseController::getTargetByPos(const Point & pt, bool ignore_capture)
{
    View * target = capture_.get();
    if (!target || ignore_capture)
        target = root_->hitTest(pt);
    //mouse target 不能为root
    if (target == root_)
        target = nullptr;
    return target;
}

void MouseController::shiftCapture(View * n)
{
    capture_.reset(n);
}

View * MouseController::capture() const
{
    return capture_.get();
}

View * MouseController::over() const
{
    return over_.get();
}

void MouseController::clearIfNecessary()
{
    if (capture_ && 
        (!capture_->isMouseable() || !root_->contains(capture_.get())))
        shiftCapture(nullptr);
    if (over_ && 
        (!over_->isMouseable() || !root_->contains(over_.get())))
        shiftOver(nullptr);
}

}