
#include "rcameraanimation.h"

namespace chikkooos
{


RCameraAnimation::RCameraAnimation()
 : mStartEye(0.0f, 0.0f, 0.0f),
   mEndEye(0.0f, 0.0f, 0.0f),
   mStartUp(0.0f, 1.0f, 0.0f),
   mEndUp(0.0f, 1.0f, 0.0f),
   mStartCenter(0.0f, -1.0f, 0.0f),
   mEndCenter(0.0f, -1.0f, 0.0f),
   mUpdateEye(false),
   mUpdateCenter(false),
   mUpdateUp(false)
{}

void RCameraAnimation::doReverse()
{
    setEye(mEndEye, mStartEye);
    setCenter(mEndCenter, mStartCenter);
    setUp(mEndUp, mStartUp);
}

void RCameraAnimation::update(float elapsed)
{
    float t = elapsed / mDuration;

    RVector eye = mStartEye;
    RVector center = mStartCenter;
    RVector up = mStartUp;

    if (mUpdateEye) {
        eye = interpolate(mStartEye, mEndEye, t);
    }
    if (mUpdateCenter) {
        center = interpolate(mStartCenter, mEndCenter, t);
    }
    if (mUpdateUp) {
        up = interpolate(mStartUp, mEndUp, t);
    }

    mCamera.lookAt(eye, up, center);
}

}

