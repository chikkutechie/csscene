
#include "rcameraanimationitem.h"

namespace chikkooos
{

void RCameraAnimationItem::draw(RGc & gc) const
{
    if (mAnimation.state() == RAnimation::None) {
        const_cast<RCameraAnimationItem *>(this)->mAnimation.start();
    } else if (mAnimation.state() == RAnimation::Running) {
        const_cast<RCameraAnimationItem *>(this)->mAnimation.step();
    }
    RCamera c = gc.camera();
    gc.setCamera(mAnimation.camera());
    RItem::draw(gc);
    gc.setCamera(c);
}

RItem * RCameraAnimationItem::clone()
{
    return new RCameraAnimationItem(*this);
}

void RCameraAnimationItem::setProperties(RPropertyMap const & map, std::string const & element)
{
    RAnimationItem::setProperties(map, element);

    mAnimation.setEye(map.getVector("startEye", mAnimation.startEye()),
           map.getVector("endEye", mAnimation.endEye()));
    mAnimation.setCenter(map.getVector("startCenter", mAnimation.startCenter()),
           map.getVector("endCenter", mAnimation.endCenter()));
    mAnimation.setUp(map.getVector("startUp", mAnimation.startUp()),
           map.getVector("endUp", mAnimation.endUp()));
}

}

