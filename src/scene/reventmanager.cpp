
#include "reventmanager.h"
#include "ritem.h"

namespace chikkooos
{

REventManager::REventManager()
{
}

REventListner * REventManager::getCallback(std::string const & name)
{
    EventCallbacksIter iter = mCallbacks.find(name);
    if (iter != mCallbacks.end()) {
        return iter->second;
    } else {
        return 0;
    }
}

RCollisionEventListner * REventManager::getCollisionCallback(std::string const & name)
{
    CollisionEventCallbacksIter iter = mCollisionCallbacks.find(name);
    if (iter != mCollisionCallbacks.end()) {
        return iter->second;
    } else {
        return 0;
    }
}

void REventManager::fireSingleTap(int x, int y)
{
    for (ItemsIter iter=mItems.begin(); iter != mItems.end(); ++iter) {
        (*iter)->onSingleTap(x, y);
    }
}

void REventManager::fireDoubleTap(int x, int y)
{
    for (ItemsIter iter=mItems.begin(); iter != mItems.end(); ++iter) {
        (*iter)->onDoubleTap(x, y);
    }
}

void REventManager::fireMouseEvent(int button, int state, int x, int y)
{
    for (ItemsIter iter=mItems.begin(); iter != mItems.end(); ++iter) {
        (*iter)->onMouseEvent(button, state, x, y);
    }
}

void REventManager::fireMouseMove(int x, int y)
{
    for (ItemsIter iter=mItems.begin(); iter != mItems.end(); ++iter) {
        (*iter)->onMouseMove(x, y);
    }
}

void REventManager::fireKeyEvent(unsigned char key, int x, int y)
{
    for (ItemsIter iter=mItems.begin(); iter != mItems.end(); ++iter) {
        (*iter)->onKeyEvent(key, x, y);
    }
}

void REventManager::fireTouchDown(int x, int y)
{
    for (ItemsIter iter=mItems.begin(); iter != mItems.end(); ++iter) {
        (*iter)->onTouchDown(x, y);
    }
}

void REventManager::fireTouchUp(int x, int y)
{
    for (ItemsIter iter=mItems.begin(); iter != mItems.end(); ++iter) {
        (*iter)->onTouchUp(x, y);
    }
}

}
