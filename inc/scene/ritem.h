
#ifndef RITEM_H
#define RITEM_H

#include "rgc.h"
#include "rpropertymap.h"

#include <set>

namespace chikkooos
{

class RScene;

class RItem
{
public:
    typedef std::vector< RSmartPointer<RItem> > Items;
    typedef Items::iterator ItemsIter;
    typedef Items::const_iterator ItemsConstIter;

protected:
    typedef std::map<std::string, std::string> AttribMap;
    typedef AttribMap::iterator AttribMapIter;
    typedef AttribMap::const_iterator AttribMapConstIter;

public:
    RItem(RItem * parent = 0);
    virtual ~RItem();

    int id() const
    {
        return mId;
    }

    void setId(int id)
    {
        mId = id;
    }

    std::string name() const
    {
        return mName;
    }

    void setName(std::string const & name)
    {
        mName = name;
    }

    RItem * findItemById(int id);

    virtual void add(RItem * item);
    virtual RSmartPointer<RItem> remove(RItem * item);

    void safeRemove(RItem *item);

    void setVisible(bool v)
    {
        mVisible = v;
    }

    bool visible() const
    {
        return mVisible;
    }

    void setParent(RItem * p);

    RItem * root();
    const RItem * root() const;

    RItem * parent()
    {
        return mParent;
    }

    const RItem * parent() const
    {
        return mParent;
    }

    void clear();
    bool needToDraw() const;

    virtual void setBoundedRect(float x, float y, float w, float h)
    {
        mX = x;
        mY = y;
        mWidth = w;
        mHeight = h;
    }

    virtual RSizeF size() const
    {
        return RSizeF(mWidth, mHeight);
    }

    virtual RVector position2d() const
    {
        return RVector(mX, mY);
    }

    virtual void update(float dt);

    virtual void draw(RGc & gc) const;

    virtual RItem * clone();

    virtual void setProperties(RPropertyMap const & map, std::string const & element);

    virtual void onSingleTap(int x, int y);

    virtual void onDoubleTap(int x, int y);

    virtual void onMouseEvent(int button, int state, int x, int y);

    virtual void onMouseMove(int x, int y);

    virtual void onKeyEvent(unsigned char key, int x, int y);

    virtual void onReshape(int w, int h);

    virtual void onTouchDown(int x, int y);

    virtual void onTouchUp(int x, int y);

    std::string customMsg() const
    {
        return mCustomMsg;
    }

    bool isLeaf() const
    {
        return mChilds.empty();
    }

    void setScene(RScene * s)
    {
        mScene = s;
    }

    RScene * scene();
    const RScene * scene() const;

    Items & children()
    {
        return mChilds;
    }

    const Items & children() const
    {
        return mChilds;
    }

    RSmartPointer<RItem> childAt(unsigned int index)
    {
        if (index < mChilds.size()) {
            return mChilds[index];
        }
        return RSmartPointer<RItem>();
    }

protected:
    std::string mName;
    int mId;
    bool mVisible;
    Items mChilds;
    RItem * mParent;
    RScene * mScene;
    float mX;
    float mY;
    float mWidth;
    float mHeight;

    std::string mCustomMsg;
};

}

#endif
