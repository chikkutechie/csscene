
#ifndef RCAMERAANIMATIONITEM_H
#define RCAMERAANIMATIONITEM_H

#include "ranimationitem.h"
#include "rcameraanimation.h"

namespace chikkooos
{

class RCameraAnimationItem: public RAnimationItem
{
public:
    RCameraAnimationItem(RItem * parent = 0)
     : RAnimationItem(parent)
    {}

    void draw(RGc & gc) const;

    RItem * clone();
    void setProperties(RPropertyMap const & map, std::string const & element);

    RCameraAnimation & animation()
    {
        return mAnimation;
    }

    const RCameraAnimation & animation() const
    {
        return mAnimation;
    }

private:
    RCameraAnimation mAnimation;
};

}

#endif

