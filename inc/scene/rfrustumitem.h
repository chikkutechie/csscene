
#ifndef RFRUSTUMITEM_H
#define RFRUSTUMITEM_H

#include "ritem.h"
#include "rfrustum.h"

namespace chikkooos
{

class RFrustumItem: public RItem
{
public:
    RFrustumItem(RItem * parent = 0)
     : RItem(parent)
    {}

    void setFrustum(RFrustum const & f)
    {
        mFrustum = f;
    }

    RFrustum & frustum()
    {
        return mFrustum;
    }
    
    const RFrustum & frustum() const
    {
        return mFrustum;
    }

    void draw(RGc & gc) const;

    RItem * clone();
    void setProperties(RPropertyMap const & map, std::string const & element);

protected:
    RFrustum mFrustum;
};

}

#endif

