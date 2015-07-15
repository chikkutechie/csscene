
#ifndef RLIGHTITEM_H
#define RLIGHTITEM_H

#include "ritem.h"
#include "rlight.h"

namespace chikkooos
{

class RLightItem: public RItem
{
public:
    RLightItem(RItem * parent = 0)
     : RItem(parent)
    {}

    void setLight(RLight const & f)
    {
        mLight = f;
    }

    RLight light() const
    {
        return mLight;
    }
    
    void draw(RGc & gc) const;

    RItem * clone();
    void setProperties(RPropertyMap const & map, std::string const & element);

protected:
    RLight mLight;
};

}

#endif

