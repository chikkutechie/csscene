
#include "rquaternionitem.h"

namespace chikkooos
{


void RQuaternionItem::draw(RGc & gc) const
{
    gc.pushTransform();

    gc.multiplyTransformation(mQuaternion.matrix());

    RItem::draw(gc);

    gc.popTransform();
}

RItem * RQuaternionItem::clone()
{
	return new RQuaternionItem();
}

void RQuaternionItem::setProperties(RPropertyMap const & map, std::string const & element)
{
    float angle = map.getFloat("angle");
    float rx = map.getFloat("rx");
    float ry = map.getFloat("ry");
    float rz = map.getFloat("rz", 1.0f);

    mQuaternion.set(angle, RVector(rx, ry, rz));
}

}
