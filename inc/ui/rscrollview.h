
#ifndef RSCROLLVIEW_H
#define RSCROLLVIEW_H

#include "rlayoutitem.h"

namespace chikkooos
{

class RScrollView: public RLayoutItem
{
public:
    RScrollView()
     : mItemsPerView(1),
       mCurrentView(0),
       mDirty(true),
       mLeftPadding(0.0f),
       mRightPadding(0.0f),
       mTopPadding(0.0f),
       mBottomPadding(0.0f)
    {}

    virtual void setBoundedRect(float x, float y, float w, float h);

    virtual void draw(RGc & gc) const;

    virtual RItem * clone();

    virtual void setProperties(RPropertyMap const & map, std::string const & element);

    virtual void onMouseEvent(int button, int state, int x, int y);

    virtual void onTouchDown(int x, int y);

    virtual void onTouchUp(int x, int y);

    void moveNext();

    void movePrev();

    void add(RItem * item)
    {
        RItem::add(item);
        mDirty = true;
    }

    RSmartPointer<RItem> remove(RItem * item)
    {
        RSmartPointer<RItem> removedItem = RItem::remove(item);
        mDirty = true;
        return removedItem;
    }

protected:
    void update();

protected:
    RFrustum mProjection;
    RCamera mCamera;
    RTransformation mTransformation;

    int mItemsPerView;
    int mCurrentView;
    bool mDirty;
    float mLeftPadding;
    float mRightPadding;
    float mTopPadding;
    float mBottomPadding;
};

}

#endif
