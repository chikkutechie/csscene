
#ifndef RPHYSICSANIMATIONITEM_H
#define RPHYSICSANIMATIONITEM_H

#include "ranimationitem.h"
#include "rphysicsanimation.h"

namespace chikkooos
{

class RPhysicsAnimationItem: public RAnimationItem
{
public:
    RPhysicsAnimationItem();

    RItem * clone();
    void draw(RGc & gc) const;
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
    RPhysicsAnimation mAnimation;
};

}

#endif

