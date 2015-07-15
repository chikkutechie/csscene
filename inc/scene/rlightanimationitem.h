
#ifndef RLIGHTANIMATIONITEM_H
#define RLIGHTANIMATIONITEM_H

#include "ranimationitem.h"
#include "rlightanimation.h"

namespace chikkooos
{

class RLightAnimationItem: public RAnimationItem
{
public:
    RLightAnimationItem(RItem * parent = 0)
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
    RLightAnimation mAnimation;
};

}

#endif

