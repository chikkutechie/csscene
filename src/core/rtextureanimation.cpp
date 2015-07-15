
#include "rtextureanimation.h"
#include "rlog.h"

namespace chikkooos
{


void RTextureAnimation::addImage(std::string const & filename)
{
    RTexture t;
    t.set(filename);
    addTexture(t);
}

void RTextureAnimation::doReverse()
{
    if (mGoBackward) {
        mGoBackward = false;
    } else {
        mGoBackward = true;
    }
}

void RTextureAnimation::update(float elapsed)
{
    if (mTextures.size() == 0) {
        return;
    }

    float t = elapsed / mDuration;
    
    mIndex = interpolate(0, mTextures.size(), t);
    if ((unsigned int)mIndex >= mTextures.size()) {
        mIndex = mTextures.size() - 1;
    }
}

}

