
#include "rspriteitem.h"
#include "rdataprovider.h"
#include "rscene.h"
#include "rtransutils.h"

namespace chikkooos
{

RSpriteItem::RSpriteItem()
{
    mX = 0.0f;
    mY = 0.0f;
    mWidth = 1.0f;
    mHeight = 1.0f;
    mFlip = false;
    mIsPressed = false;

    mClickListner = 0;
}

void RSpriteItem::setBoundedRect(float x, float y, float w, float h)
{
    set(x, y, w, h, mFlip);
}

void RSpriteItem::set(float x, float y, float w, float h, bool flip)
{
    mX = x;
    mY = y;
    mWidth = w;
    mHeight = h;
    mFlip = flip;

    mShape.clear();

    mShape.setPrimitive(GL_TRIANGLE_FAN);

    mShape.addVertex(x, y, 0);
    mShape.addVertex(x+w, y, 0);
    mShape.addVertex(x+w, y+h, 0);
    mShape.addVertex(x, y+h, 0);

    if (flip) {
        mShape.addTexCoord(0, 0);
        mShape.addTexCoord(1, 0);
        mShape.addTexCoord(1, 1);
        mShape.addTexCoord(0, 1);
    } else {
        mShape.addTexCoord(0, 1);
        mShape.addTexCoord(1, 1);
        mShape.addTexCoord(1, 0);
        mShape.addTexCoord(0, 0);
    }
}

void RSpriteItem::draw(RGc & gc) const
{
    if (mTexture.isNull()) {
        gc.draw(mShape);
    } else {
        RTexture tex = gc.texture();

        gc.setTexture(mTexture);

        gc.draw(mShape);
        gc.setTexture(tex);
    }

    mProjection = gc.frustum();
    mCamera = gc.camera();
    mTransformation = gc.transformation();

    RItem::draw(gc);
}

RItem * RSpriteItem::clone()
{
    return new RSpriteItem();
}

void RSpriteItem::setProperties(RPropertyMap const & map, std::string const & element)
{
    RUIItem::setProperties(map, element);

    int flip = map.getInt("flip");

    setImage(map.getString("image"));

    set(mX, mY, mWidth, mHeight, flip);

    mClickListnerName = map.getString("onclick");
}

void RSpriteItem::setImage(std::string const &filename)
{
    if (!filename.empty()) {
        mTexture = RDataProvider::instance().texture(filename);
        if (mTexture.isNull()) {
            // try loading from atlas
        }
    }
}

void RSpriteItem::onClick(int x, int y)
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

void RSpriteItem::onMouseEvent(int button, int state, int x, int y)
{
    if (button == REvent::MouseLeftButton) {
        if (state == REvent::MouseDown) {
            RVector worldPoint = RTransUtils::worldSpacePoint(mProjection, mCamera, mTransformation, RVector(x, y));
            mIsPressed = false;

            if (worldPoint.x() > mX && worldPoint.x() < mX + mWidth &&
                worldPoint.y() > mY && worldPoint.y() < mY + mHeight) {
                mIsPressed = true;
            }

        } else {
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
}

void RSpriteItem::onSingleTap(int x, int y)
{
    RVector worldPoint = RTransUtils::worldSpacePoint(mProjection, mCamera, mTransformation, RVector(x, y));
    mIsPressed = false;

    if (worldPoint.x() > mX && worldPoint.x() < mX + mWidth &&
        worldPoint.y() > mY && worldPoint.y() < mY + mHeight) {
        onClick(x, y);
    }
}

}
