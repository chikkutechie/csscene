
#ifndef RSHAPEANIMATIONITEM_H
#define RSHAPEANIMATIONITEM_H

#include "ranimationitem.h"
#include "rshapeanimation.h"

namespace chikkooos
{

class RShapeAnimationItem: public RAnimationItem
{
public:
    RShapeAnimationItem(RItem * parent = 0)
     : RAnimationItem(parent)
    {}

    void draw(RGc & gc) const;

    RItem * clone();
    void setProperties(RPropertyMap const & map, std::string const & element);

    RAnimation & animation()
    {
        return mAnimation;
    }

    const RAnimation & animation() const
    {
        return mAnimation;
    }

private:
    RShapeAnimation mAnimation;
};

}

#endif

