
#ifndef RTEXTUREANIMATIONITEM_H
#define RTEXTUREANIMATIONITEM_H

#include "ranimationitem.h"
#include "rtextureanimation.h"

namespace chikkooos
{

class RTextureAnimationItem: public RAnimationItem
{
public:
    RTextureAnimationItem(RItem * parent = 0)
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
    RTextureAnimation mAnimation;
};

}

#endif

