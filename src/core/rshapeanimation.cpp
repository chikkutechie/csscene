
#include "rshapeanimation.h"
#include "rlog.h"

namespace chikkooos
{

void RShapeAnimation::doReverse()
{
    if (mGoBackward) {
        mGoBackward = false;
    } else {
        mGoBackward = true;
    }
}

void RShapeAnimation::update(float elapsed)
{
    if (mShapes.size() == 0) {
        return;
    }

    float t = elapsed / mDuration;
    
    mIndex = interpolate(0, mShapes.size(), t);
    if ((unsigned int)mIndex >= mShapes.size()) {
        mIndex = mShapes.size() - 1;
    }
}

}

