
#include "rtoggle.h"
#include "rtransutils.h"
#include "rdataprovider.h"
#include "rscene.h"

namespace chikkooos
{

void RToggle::draw(RGc & gc) const
{
    if (mOnState) {
        mOnSprite.draw(gc);
    } else {
        mOffSprite.draw(gc);
    }

    mProjection = gc.frustum();
    mCamera = gc.camera();
    mTransformation = gc.transformation();
}

RItem * RToggle::clone()
{
    return new RToggle(*this);
}

void RToggle::setBoundedRect(float x, float y, float w, float h)
{
    mX = x;
    mY = y;
    mWidth = w;
    mHeight = h;

    mOnSprite.setBoundedRect(mX, mY, mWidth, mHeight);
    mOffSprite.setBoundedRect(mX, mY, mWidth, mHeight);
}

void RToggle::setProperties(RPropertyMap const & map, std::string const & element)
{
    RUIItem::setProperties(map, element);

    mOnSprite.setImage(map.getString("on"));
    mOffSprite.setImage(map.getString("off"));

    mOnSprite.set(mX, mY, mWidth, mHeight);
    mOffSprite.set(mX, mY, mWidth, mHeight);

    mClickListnerName = map.getString("onclick");
}

void RToggle::onClick(int x, int y)
{
    if (mClickListner) {
        mClickListner->handle(REvent(x, y, REvent::MouseUp, REvent::MouseLeft, this));
    } else if (!mClickListnerName.empty()) {
        mClickListner = RScene::currentScene()->getEventCallback(mClickListnerName);
        if (mClickListner) {
            mClickListner->handle(REvent(x, y, REvent::MouseUp, REvent::MouseLeft, this));
        }
    }
}

void RToggle::onMouseEvent(int button, int state, int x, int y)
{
    if (button == REvent::MouseLeftButton) {
        if (state == REvent::MouseDown) {
            RVector worldPoint = RTransUtils::worldSpacePoint(mProjection, mCamera, mTransformation, RVector(x, y));

            if (worldPoint.x() > mX && worldPoint.x() < mX + mWidth &&
                worldPoint.y() > mY && worldPoint.y() < mY + mHeight) {
                mIsPressed = true;
            }

        } else {
            if (mIsPressed) {
                RVector worldPoint = RTransUtils::worldSpacePoint(mProjection, mCamera, mTransformation, RVector(x, y));
                if (worldPoint.x() > mX && worldPoint.x() < mX + mWidth &&
                    worldPoint.y() > mY && worldPoint.y() < mY + mHeight) {

                    mOnState = !mOnState;
                    onClick(x, y);
                }
            }
            mIsPressed = false;
        }
    }
}

void RToggle::onSingleTap(int x, int y)
{
    RVector worldPoint = RTransUtils::worldSpacePoint(mProjection, mCamera, mTransformation, RVector(x, y));

    if (worldPoint.x() > mX && worldPoint.x() < mX + mWidth &&
        worldPoint.y() > mY && worldPoint.y() < mY + mHeight) {
        mOnState = !mOnState;
        onClick(x, y);
    }
}

}
