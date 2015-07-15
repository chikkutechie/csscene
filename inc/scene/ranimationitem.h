
#ifndef RANIMATIONITEM_H
#define RANIMATIONITEM_H

#include "ritem.h"
#include "ranimation.h"

namespace chikkooos
{

class RAnimationItem: public RItem
{
public:
    RAnimationItem(RItem * parent = 0)
     : RItem(parent)
    {}

    void setProperties(RPropertyMap const & map, std::string const & element);

    virtual RAnimation & animation() = 0;
    virtual const RAnimation & animation() const = 0;
};

}

#endif

