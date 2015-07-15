
#ifndef RTRANSUTILS_H
#define RTRANSUTILS_H

#include "rvector.h"
#include "rcamera.h"

namespace chikkooos
{

class RTransUtils
{
public:
    static RVector worldSpacePoint(const RFrustum & frustum, const RCamera & camera, const RTransformation & transformation, RVector fromPoint);
private:
    RTransUtils()
    {}
};

}

#endif

