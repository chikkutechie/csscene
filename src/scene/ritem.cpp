
#include "ritem.h"
#include "rview.h"
#include "rscene.h"

#include <algorithm>

namespace chikkooos
{

static long IdStart = 0;

RItem::RItem(RItem * parent)
 : mId(0),
   mVisible(true),
   mParent(parent),
   mScene(0)
{
    setParent(parent);
    mId = IdStart;
}

RItem::~RItem()
{
    clear();
}

void RItem::clear()
{
    // clear all childrens before destroying itself
    for (ItemsIter iter = mChilds.begin(); iter != mChilds.end(); ++iter) {
        (*iter)->clear();
    }
    mChilds.clear();
}

void RItem::add(RItem * item)
{
    if (item) {
        mChilds.push_back(item);
        item->mParent = this;
    }
}

RSmartPointer<RItem> RItem::remove(RItem * item)
{
    RSmartPointer<RItem> removedItem;

    ItemsIter iter = std::find(mChilds.begin(), mChilds.end(), item);
    if (iter != mChilds.end()) {
        removedItem = *iter;
        mChilds.erase(iter);
        item->mParent = 0;
    }

    return removedItem;
}

void RItem::safeRemove(RItem *item) {
    if (scene()) {
        scene()->safeRemove(item);
    }
}

RItem * RItem::root()
{
    if (mParent) {
        return mParent->root();
    } else {
        return this;
    }
}

const RItem * RItem::root() const
{
    if (mParent) {
        return mParent->root();
    } else {
        return this;
    }
}

RScene * RItem::scene()
{
    if (mScene) {
        return mScene;
    }
    RItem * r = root();
    if (r) {
        return r->mScene;
    }

    return 0;
}

const RScene * RItem::scene() const
{
    if (mScene) {
        return mScene;
    }
    const RItem * r = root();
    if (r) {
        return r->mScene;
    }

    return 0;
}

void RItem::setParent(RItem * p)
{
    if (parent() != 0) {
        parent()->remove(this);
    }

    mParent = p;
    if (p) {
        p->add(this);
    }
}

bool RItem::needToDraw() const
{
    if (visible()) {
        return true;
    }

    return false;
}

RItem * RItem::findItemById(int i)
{
    if (id() == i) {
        return this;
    }

    RItem * item = 0;
    for (ItemsIter iter = mChilds.begin(); iter != mChilds.end() && !item; ++iter) {
        item = (*iter)->findItemById(i);
    }
    return item;
}

void RItem::update(float dt)
{
    if (visible()) {
        for (ItemsIter iter = mChilds.begin(); iter != mChilds.end(); ++iter) {
            (*iter)->update(dt);
        }
    }
}

void RItem::draw(RGc & gc) const
{
    for (ItemsConstIter iter = mChilds.begin(); iter != mChilds.end(); ++iter) {
        if (needToDraw()) {
            (*iter)->draw(gc);
        }
    }
}

void RItem::onSingleTap(int x, int y)
{
    if (visible()) {
        for (ItemsIter iter = mChilds.begin(); iter != mChilds.end(); ++iter) {
            if ((*iter)->visible()) {
                (*iter)->onSingleTap(x, y);
            }
        }
    }
}

void RItem::onDoubleTap(int x, int y)
{
    if (visible()) {
        for (ItemsIter iter = mChilds.begin(); iter != mChilds.end(); ++iter) {
            if ((*iter)->visible()) {
                (*iter)->onDoubleTap(x, y);
            }
        }
    }
}

void RItem::onMouseEvent(int button, int state, int x, int y)
{
    if (visible()) {
        for (ItemsIter iter = mChilds.begin(); iter != mChilds.end(); ++iter) {
            if ((*iter)->visible()) {
                (*iter)->onMouseEvent(button, state, x, y);
            }
        }
    }
}

void RItem::onMouseMove(int x, int y)
{
    if (visible()) {
        for (ItemsIter iter = mChilds.begin(); iter != mChilds.end(); ++iter) {
            if ((*iter)->visible()) {
                (*iter)->onMouseMove(x, y);
            }
        }
    }
}

void RItem::onKeyEvent(unsigned char key, int x, int y)
{
    if (visible()) {
        for (ItemsIter iter = mChilds.begin(); iter != mChilds.end(); ++iter) {
            if ((*iter)->visible()) {
                (*iter)->onKeyEvent(key, x, y);
            }
        }
    }
}

void RItem::onReshape(int w, int h)
{
    for (ItemsIter iter = mChilds.begin(); iter != mChilds.end(); ++iter) {
        if ((*iter)->visible()) {
            (*iter)->onReshape(w, h);
        }
    }
}

void RItem::onTouchDown(int x, int y)
{
    if (visible()) {
        for (ItemsIter iter = mChilds.begin(); iter != mChilds.end(); ++iter) {
            if ((*iter)->visible()) {
                (*iter)->onTouchDown(x, y);
            }
        }
    }
}

void RItem::onTouchUp(int x, int y)
{
    if (visible()) {
        for (ItemsIter iter = mChilds.begin(); iter != mChilds.end(); ++iter) {
            if ((*iter)->visible()) {
                (*iter)->onTouchUp(x, y);
            }
        }
    }
}

RItem * RItem::clone()
{
    return new RItem(*this);
}

void RItem::setProperties(RPropertyMap const & map, std::string const & element)
{
    int withEvent = map.getInt("event");
    if (withEvent) {
        RScene::currentScene()->registerEvent(this);
    }

    mCustomMsg = map.getString("custommsg");

    RVector rect = map.getVector("boundedrect");
    mX = rect.x();
    mY = rect.y();
    mWidth = rect.z();
    mHeight = rect.w();

    std::string align = map.getString("align");
    if (align.compare("center") == 0) {
        RItem *p = parent();

        float px = 0.0f;
        float py = 0.0f;
        float pw = 0.0f;
        float ph = 0.0f;

        if (p) {
            px = p->mX;
            py = p->mY;
            pw = p->mWidth;
            ph = p->mHeight;
        }

        if (pw < Epsilon || ph < Epsilon) {
            RScene *s = scene();
            if (s) {
                pw = s->view()->getWidth();
                ph = s->view()->getHeight();
            }
        }

        if (pw > Epsilon && ph > Epsilon) {
            mX = px + (pw - mWidth) / 2.0f;
            mY = py + (ph - mHeight) / 2.0f;
        }

    }

}

}

