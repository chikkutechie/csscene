
#ifndef RTRANANIMATIONITEM_H
#define RTRANANIMATIONITEM_H

#include "ranimationitem.h"
#include "rtransanimation.h"

namespace chikkooos
{

class RTransAnimationItem: public RAnimationItem
{
public:
    RTransAnimationItem(RItem * parent = 0)
     : RAnimationItem(parent)
    {}

    void draw(RGc & gc) const;

    RItem * clone();
    void setProperties(RPropertyMap const & map, std::string const & element);

    RTransAnimation & animation()
    {
        return mAnimation;
    }

    const RTransAnimation & animation() const
    {
        return mAnimation;
    }

private:
    RTransAnimation mAnimation;
};

}

#endif

