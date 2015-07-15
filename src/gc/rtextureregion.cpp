
#include "rtextureregion.h"

namespace chikkooos
{

RTextureRegion::RTextureRegion(int textureWidth, int textureHeight, int x, int y, int width, int height)
 : mTextureWidth(textureWidth),
   mTextureHeight(textureHeight),
   mDirty(false)
{
    if (x < 0) {
        x = 0;
    }
    if (x < 0) {
        x = 0;
    }

    if (width > textureWidth) {
        width = textureWidth;
    }

    if (height > textureHeight) {
        height = textureHeight;
    }

    mX = x;
    mY = y;
    mWidth = width;
    mHeight = height;

    if (mX == 0 && mY == 0 && mWidth == mTextureWidth && mHeight == mTextureHeight) {
        mIdentity = true;
    } else {
        mIdentity = false;
    }

    if (!mIdentity) {
        createTransform();
    }
}

RTextureRegion::RTextureRegion(RTexture texture, int x, int y, int width, int height)
 : mTextureWidth(0),
   mTextureHeight(0),
   mX(x),
   mY(y),
   mWidth(width),
   mHeight(height),
   mTexture(texture),
   mIdentity(false),
   mDirty(true)
{}

const float * RTextureRegion::matrix3x3() const
{
    if (mDirty) {
        const_cast<RTextureRegion *>(this)->createTransform();
    }
    return &mMatrix3x3[0];
}

const float * RTextureRegion::matrix4x4() const
{
    if (mDirty) {
        const_cast<RTextureRegion *>(this)->createTransform();
    }

    return mMatrix4x4.data();
}

void RTextureRegion::createTransform()
{
    mDirty = false;

    if (mTextureWidth == 0) {
        if (!mTexture.isNull()) {
            mTextureWidth = mTexture.width();
        } else {
            mTextureWidth = mWidth;
        }
    }

    if (mTextureHeight == 0) {
        if (!mTexture.isNull()) {
            mTextureHeight = mTexture.height();
        } else {
            mTextureHeight = mHeight;
        }
    }

    float tx = (float)(mX - 0.0f) / (float)mTextureWidth;
    float ty = (float)(mY - 0.0f) / (float)mTextureHeight;

    float sx = (float)mWidth / (float)mTextureWidth;
    float sy = (float)mHeight / (float)mTextureHeight;


    mMatrix3x3[0] = sx;
    mMatrix3x3[1] = 0.0f;
    mMatrix3x3[2] = 0.0f;
    mMatrix3x3[3] = 0.0f;
    mMatrix3x3[4] = sy;
    mMatrix3x3[5] = 0.0f;
    mMatrix3x3[6] = tx;
    mMatrix3x3[7] = ty;
    mMatrix3x3[8] = 1.0f;

    mMatrix4x4.scale(sx, sy, 1.0f);
    mMatrix4x4.translate(tx, ty, 0.0f);
}

}
