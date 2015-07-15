
#include "rcamera.h"
#include "rlog.h"
#include "rview.h"
#include "rbinder.h"

namespace chikkooos
{

RCamera::RCamera()
 : mEye(0.0f, 0.0f, 0.0f),
   mUp(0.0f, 1.0f, 0.0f),
   mCenter(0.0f, -1.0f, 0.0f)
{}

void RCamera::applyLookAt()
{
    mTransformation.load(RMatrix::createLookAt(mEye, mCenter, mUp));
}

}

