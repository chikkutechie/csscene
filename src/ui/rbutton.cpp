
#include "rbutton.h"
#include "rtransutils.h"
#include "rdataprovider.h"
#include "rscene.h"

namespace chikkooos
{

void RButton::update(float dt)
{
    if (!mCreated) {
        create();
    }
}

void RButton::draw(RGc & gc) const
{
    if (mIsPressed) {
        mPressedSprite->draw(gc);
    } else {
        mNormalSprite->draw(gc);
    }

    mProjection = gc.frustum();
    mCamera = gc.camera();
    mTransformation = gc.transformation();
}

void RButton::create()
{
    if (RPropertyMap::hasPositionMarker(mNormalItemName)) {
        mNormalSprite = childAt(RPropertyMap::getPositionFromString(mNormalItemName));
    } else {
        RSpriteItem * sitem = new RSpriteItem();
        sitem->setImage(mNormalItemName);
        mNormalSprite = sitem;
    }

    if (RPropertyMap::hasPositionMarker(mPressedItemName)) {
        mPressedSprite = childAt(RPropertyMap::getPositionFromString(mPressedItemName));
    } else {
        RSpriteItem * sitem = new RSpriteItem();
        sitem->setImage(mPressedItemName);
        mPressedSprite = sitem;
    }

    mPressedSprite->setBoundedRect(mX, mY, mWidth, mHeight);
    mNormalSprite->setBoundedRect(mX, mY, mWidth, mHeight);

    mCreated = true;
}

void RButton::create(std::string const & pressed, std::string const & normal)
{
    mNormalItemName = normal;
    mPressedItemName = pressed;
}


RItem * RButton::clone()
{
    return new RButton();
}

void RButton::setBoundedRect(float x, float y, float w, float h)
{
    RItem::setBoundedRect(x, y, w, h);

    if (!mPressedSprite.isNull()) {
        mPressedSprite->setBoundedRect(mX, mY, mWidth, mHeight);
        mNormalSprite->setBoundedRect(mX, mY, mWidth, mHeight);
    }
}

void RButton::setProperties(RPropertyMap const & map, std::string const & element)
{
    RUIItem::setProperties(map, element);

    mNormalItemName = map.getString("normal");
    mPressedItemName = map.getString("pressed");

    mClickListnerName = map.getString("onclick");
}

void RButton::onClick(int x, int y)
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

void RButton::onMouseEvent(int button, int state, int x, int y)
{
    if (button == REvent::MouseLeftButton) {
        if (state == REvent::MouseDown) {
            onTouchDown(x, y);

        } else {
            onTouchUp(x, y);
        }
    }
}

void RButton::onTouchDown(int x, int y)
{
    RVector worldPoint = RTransUtils::worldSpacePoint(mProjection, mCamera, mTransformation, RVector(x, y));

    if (worldPoint.x() > mX && worldPoint.x() < mX + mWidth &&
        worldPoint.y() > mY && worldPoint.y() < mY + mHeight) {
        mIsPressed = true;
    }
}

void RButton::onTouchUp(int x, int y)
{
    if (mIsPressed) {
        RVector worldPoint = RTransUtils::worldSpacePoint(mProjection, mCamera, mTransformation, RVector(x, y));

        if (worldPoint.x() > mX && worldPoint.x() < mX + mWidth &&
            worldPoint.y() > mY && worldPoint.y() < mY + mHeight) {
            onClick(x, y);
        }
    }

    mIsPressed = false;
}

}
