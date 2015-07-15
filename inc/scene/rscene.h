
#ifndef RSCENE_H
#define RSCENE_H

#include <vector>

#include "rgc.h"
#include "ritem.h"
#include "rsmartpointer.h"
#include "reventmanager.h"
#include "revent.h"

class TiXmlNode;
class TiXmlElement;
class TiXmlAttribute;

namespace chikkooos
{

class RView;
class RItem;

class RScene
{
public:
    RScene(RView *view);
    virtual ~RScene();

    virtual void update(float dt);
    virtual void draw(RGc & gc) const;

    bool load(std::string const & filename);

    bool loadFromData(const char * data);

    void setRootItem(RItem * item)
    {
        mRootItem = item;
        mRootItem->setScene(this);
    }

    RItem * findItemById(int id)
    {
        return mRootItem->findItemById(id);
    }

    virtual void onSingleTap(int x, int y)
    {
        mEventManager.fireSingleTap(x, y);
    }

    virtual void onDoubleTap(int x, int y)
    {
        mEventManager.fireDoubleTap(x, y);
    }

    virtual void onMouseEvent(int button, int state, int x, int y)
    {
        mEventManager.fireMouseEvent(button, state, x, y);
    }

    virtual void onMouseMove(int x, int y)
    {
        mEventManager.fireMouseMove(x, y);
    }

    virtual void onKeyEvent(unsigned char key, int x, int y)
    {
        mEventManager.fireKeyEvent(key, x, y);
    }

    virtual void onTouchDown(int x, int y)
    {
        mEventManager.fireTouchDown(x, y);
    }

    virtual void onTouchUp(int x, int y)
    {
        mEventManager.fireTouchUp(x, y);
    }

    virtual void onReshape(int w, int h)
    {
        if (!mRootItem.isNull()) {
            mRootItem->onReshape(w, h);
        }
    }

    void registerEvent(RItem *item)
    {
        mEventManager.addItem(item);
    }

    void deregisterEvent(RItem *item)
    {
        mEventManager.removeItem(item);
    }

    void registerEventCallback(std::string const & name, REventListner * listner)
    {
        mEventManager.registerCallback(name, listner);
    }

    void deregisterEventCallback(std::string const & name)
    {
        mEventManager.deregisterCallback(name);
    }

    REventListner * getEventCallback(std::string const & name)
    {
        return mEventManager.getCallback(name);
    }

    void registerCollisionEventCallback(std::string const & name, RCollisionEventListner * listner)
    {
        mEventManager.registerCollisionCallback(name, listner);
    }

    void deregisterCollisionEventCallback(std::string const & name)
    {
        mEventManager.deregisterCollisionCallback(name);
    }

    RCollisionEventListner * getEventCollisionCallback(std::string const & name)
    {
        return mEventManager.getCollisionCallback(name);
    }

    RView * view()
    {
        return mView;
    }

    void safeRemove(RItem *item) {
        mItemToRemove.insert(mItemToRemove.begin(), item);
    }

    static RScene * currentScene();

private:
    RItem * createScene(TiXmlNode* node);
    void createResource(TiXmlNode* node);
    RItem * createItems(TiXmlNode* node, RItem * parent);
    RItem * load(TiXmlNode* node);
    void loadItems(RItem * item, TiXmlElement* element);
    RPropertyMap toPropertyMap(TiXmlAttribute* attrib);

protected:
    RSmartPointer<RItem>  mRootItem;
    REventManager mEventManager;
    RView * mView;

    std::vector<RItem *> mItemToRemove;
};

}

#endif

