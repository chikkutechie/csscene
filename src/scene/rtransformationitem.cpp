
#include "rtransformationitem.h"

namespace chikkooos
{

void RTransformationItem::draw(RGc & gc) const
{
    gc.pushTransform();

    gc.multiplyTransformation(mTransformation);

    RItem::draw(gc);

    gc.popTransform();
}

RItem * RTransformationItem::clone()
{
    return new RTransformationItem(*this);
}

void RTransformationItem::setProperties(RPropertyMap const & map, std::string const & element)
{
    if (element.compare("rotate") == 0) {
        float angle = map.getFloat("angle");
        float rx = map.getFloat("rx");
        float ry = map.getFloat("ry");
        float rz = map.getFloat("rz");
        mTransformation.rotate(angle, rx, ry, rz);
    } else if (element.compare("scale") == 0) {
        float sx = map.getFloat("sx");
        float sy = map.getFloat("sy");
        float sz = map.getFloat("sz");
        mTransformation.scale(sx, sy, sz);
    } else if (element.compare("translate") == 0) {
        float tx = map.getFloat("tx");
        float ty = map.getFloat("ty");
        float tz = map.getFloat("tz");
        mTransformation.translate(tx, ty, tz);
    }
}

}

