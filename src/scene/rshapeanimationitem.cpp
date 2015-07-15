
#include "rshapeanimationitem.h"
#include "rresource.h"

namespace chikkooos
{

void RShapeAnimationItem::draw(RGc & gc) const
{
    if (mAnimation.state() == RAnimation::None) {
        const_cast<RShapeAnimationItem *>(this)->mAnimation.start();
    } else if (mAnimation.state() == RAnimation::Running) {
        const_cast<RShapeAnimationItem *>(this)->mAnimation.step();
    }

    gc.draw(*(mAnimation.shape().data()));
}

RItem * RShapeAnimationItem::clone()
{
    return new RShapeAnimationItem(*this);
}

void RShapeAnimationItem::setProperties(RPropertyMap const & map, std::string const & element)
{
    RAnimationItem::setProperties(map, element);

    if (map.has("shapes")) {
        int t;
        std::stringstream is(map.getString("shapes"));
        while (is >> t) {
            mAnimation.addShape(RResource::instance()->shape(t));
        }
    }
}

}

