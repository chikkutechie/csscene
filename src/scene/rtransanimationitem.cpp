
#include "rtransanimationitem.h"

namespace chikkooos
{

void RTransAnimationItem::draw(RGc & gc) const
{
    if (mAnimation.state() == RAnimation::None) {
        const_cast<RTransAnimationItem *>(this)->mAnimation.start();
    } else if (mAnimation.state() == RAnimation::Running) {
        const_cast<RTransAnimationItem *>(this)->mAnimation.step();
    }
    gc.pushTransform();
    gc.multiplyTransformation(mAnimation.transformation());
    RItem::draw(gc);
    gc.popTransform();
}

RItem * RTransAnimationItem::clone()
{
    return new RTransAnimationItem(*this);
}

void RTransAnimationItem::setProperties(RPropertyMap const & map, std::string const & element)
{
    RAnimationItem::setProperties(map, element);

    if (element.compare("translateanimation") == 0) {
        mAnimation.setType(RTransAnimation::Translation);
    } else if (element.compare("scaleanimation") == 0) {
        mAnimation.setType(RTransAnimation::Scaling);
    } else if (element.compare("rotateanimation") == 0) {
        mAnimation.setType(RTransAnimation::Rotation);
        mAnimation.setAngles(map.getFloat("fromAngle"), map.getFloat("toAngle"));
    }

    float fromX = map.getFloat("fromX");
    float fromY = map.getFloat("fromY");
    float fromZ = map.getFloat("fromZ");
    float toX = map.getFloat("toX");
    float toY = map.getFloat("toY");
    float toZ = map.getFloat("toZ");

    mAnimation.setPoints(RVector(fromX, fromY, fromZ), RVector(toX, toY, toZ));
}

}

