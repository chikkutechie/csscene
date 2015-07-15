
#include "rtransutils.h"
#include "rchikkooos.h"

namespace chikkooos
{


RVector RTransUtils::worldSpacePoint(const RFrustum & frustum, const RCamera & camera, const RTransformation & transformation, RVector fromPoint)
{
    RBinder &binder =  RBinder::instance();

    fromPoint.setX((2.0f * fromPoint.x() / (float)binder.getWidth()) - 1.0f);
    fromPoint.setY(1 - (2.0f * fromPoint.y() / (float)binder.getHeight()));
    fromPoint.setZ(fromPoint.z() * 2.0f - 1.0f);

    RMatrix mat = frustum.matrix().multiply(camera.transformation().matrix());
    mat = mat.multiply(transformation.matrix());

    fromPoint = mat.inverse().multiply(fromPoint);

    return fromPoint;
}

}
