
#ifndef REVENTMANAGER_H
#define REVENTMANAGER_H

#include <set>
#include <map>
#include <string>

#include "revent.h"
#include "rsmartpointer.h"

namespace chikkooos
{

class RItem;

class REventManager
{
public:
    typedef std::set<RItem *> Items;
    typedef Items::iterator ItemsIter;
    typedef Items::const_iterator ItemsContsIter;

    typedef std::map<std::string, RSmartPointer<REventListner> > EventCallbacks;
    typedef EventCallbacks::iterator EventCallbacksIter;
    typedef EventCallbacks::const_iterator EventCallbacksConstIter;

    typedef std::map<std::string, RSmartPointer<RCollisionEventListner> > CollisionEventCallbacks;
    typedef CollisionEventCallbacks::iterator CollisionEventCallbacksIter;
    typedef CollisionEventCallbacks::const_iterator CollisionEventCallbacksConstIter;

private:
    Items mItems;
    EventCallbacks mCallbacks;
    CollisionEventCallbacks mCollisionCallbacks;

public:
    REventManager();

    void addItem(RItem *item)
    {
        mItems.insert(item);
    }

    void removeItem(RItem *item)
    {
        mItems.erase(item);
    }

    Items items()
    {
        return mItems;
    }

    void registerCallback(std::string const & name, REventListner * listner)
    {
        mCallbacks.insert(std::make_pair(name, listner));
    }

    void deregisterCallback(std::string const & name)
    {
        mCallbacks.erase(name);
    }

    REventListner * getCallback(std::string const & name);


    void registerCollisionCallback(std::string const & name, RCollisionEventListner * listner)
    {
        mCollisionCallbacks.insert(std::make_pair(name, listner));
    }

    void deregisterCollisionCallback(std::string const & name)
    {
        mCollisionCallbacks.erase(name);
    }

    RCollisionEventListner * getCollisionCallback(std::string const & name);

    void fireSingleTap(int x, int y);

    void fireDoubleTap(int x, int y);

    void fireMouseEvent(int button, int state, int x, int y);

    void fireMouseMove(int x, int y);

    void fireKeyEvent(unsigned char key, int x, int y);

    void fireTouchDown(int x, int y);

    void fireTouchUp(int x, int y);
};

}

#endif
