
#include "rscrollview.h"

namespace chikkooos
{

void RScrollView::setBoundedRect(float x, float y, float w, float h)
{
    RItem::setBoundedRect(x, y, w, h);
    mDirty = true;
}

void RScrollView::draw(RGc & gc) const
{
    if (mDirty) {
        const_cast<RScrollView *>(this)->update();
    }

    int childCount = mChilds.size();
    int si = mItemsPerView * mCurrentView;
    for (int i=si; i<childCount && i<si+mItemsPerView; ++i) {
        mChilds[i]->draw(gc);
    }
}

RItem * RScrollView::clone()
{
    return new RScrollView(*this);
}

void RScrollView::update()
{
    float x = mX + mLeftPadding;

    float w = (mWidth) - (mLeftPadding + mRightPadding);
    float h = (mHeight/(float)mItemsPerView) - (mTopPadding + mBottomPadding);

    if (w < 0.000001f) {
        w = 1.0f;
    }
    if (h < 0.000001f) {
        h = 1.0f;
    }

    float y = (mY + mHeight) - h;

    int childCount = mChilds.size();
    int si = mItemsPerView * mCurrentView;
    for (int i=si; i<childCount && i<si+mItemsPerView; ++i) {
        y -= mTopPadding;
        mChilds[i]->setBoundedRect(x, y, w, h);

        y -= h;
        y -= mBottomPadding;
    }

    mDirty = false;
}

void RScrollView::setProperties(RPropertyMap const & map, std::string const & element)
{
    RLayoutItem::setProperties(map, element);

    mItemsPerView = map.getInt("itemsperview");
    if (map.has("padding")) {
        mLeftPadding = map.getFloat("padding");
        mRightPadding = map.getFloat("padding");
        mTopPadding = map.getFloat("padding");
        mBottomPadding = map.getFloat("padding");
    } else {
        mLeftPadding = map.getFloat("leftpadding");
        mRightPadding = map.getFloat("rightpadding");
        mTopPadding = map.getFloat("toppadding");
        mBottomPadding = map.getFloat("bottompadding");
    }

    mDirty = true;
}

void RScrollView::onMouseEvent(int button, int state, int x, int y)
{}

void RScrollView::onTouchDown(int x, int y)
{}

void RScrollView::onTouchUp(int x, int y)
{}

void RScrollView::moveNext()
{
    mDirty = true;

    int childCount = mChilds.size();
    if (((mItemsPerView * mCurrentView) + mItemsPerView) < childCount) {
        ++mCurrentView;
    }
}

void RScrollView::movePrev()
{
    mDirty = true;

    if (((mItemsPerView * (mCurrentView-1)) + mItemsPerView) > 0) {
        --mCurrentView;
    }
}


}
