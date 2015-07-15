
#ifndef RTEXTUREREGION_H
#define RTEXTUREREGION_H

#include "rtexture.h"
#include "rtexturetransform.h"
#include "rmatrix.h"

namespace chikkooos
{

class RTextureRegion: public RTextureTransform
{
protected:
	int mTextureWidth;
	int mTextureHeight;

	int mX;
	int mY;
	int mWidth;
	int mHeight;

    RTexture mTexture;

	bool mIdentity;

    bool mDirty;


    float mMatrix3x3[9];
    RMatrix mMatrix4x4;

public:
	RTextureRegion()
	 : mIdentity(true),
	   mDirty(false)
	{
	    mMatrix3x3[0] = 1.0f;
	    mMatrix3x3[1] = 0.0f;
	    mMatrix3x3[2] = 0.0f;
	    mMatrix3x3[3] = 0.0f;
	    mMatrix3x3[4] = 1.0f;
	    mMatrix3x3[5] = 0.0f;
	    mMatrix3x3[6] = 0.0f;
	    mMatrix3x3[7] = 0.0f;
	    mMatrix3x3[8] = 1.0f;
	}

	RTextureRegion(int textureWidth, int textureHeight, int x, int y, int width, int height);

	RTextureRegion(RTexture texutre, int x, int y, int width, int height);

    const float * matrix3x3() const;
    const float * matrix4x4() const;

    bool isIdentity() const
    {
        return mIdentity;
    }

private:
    void createTransform();

};

}

#endif
