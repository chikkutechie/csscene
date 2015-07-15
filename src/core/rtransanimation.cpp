
#include "rtransanimation.h"
#include "rquaternion.h"

namespace chikkooos
{

void RTransAnimation::doReverse()
{
    float ta = mSA;
    mSA = mEA;
    mEA = ta;

    RVector tv = mSP;
    mSP = mEP;
    mEP = tv;
}

void RTransAnimation::update( float elapsed)
{
    float t = elapsed / mDuration;

    float dx = interpolate(mSP.x(), mEP.x(), t);
    float dy = interpolate(mSP.y(), mEP.y(), t);
    float dz = interpolate(mSP.z(), mEP.z(), t);

    mTrans.reset();

    switch (mType) {
        case Scaling: {
            mTrans.scale(dx, dy, dz);
            break;
        }

        case Translation: {
            mTrans.translate(dx, dy, dz);
            break;
        }

        case Rotation: {
            float da = interpolate(mSA, mEA, t);
            mTrans.rotate(da, dx, dy, dz);
            break;
        }
    }

}	

}

