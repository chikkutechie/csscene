
#ifndef RTRANSFORMATIONITEM_H
#define RTRANSFORMATIONITEM_H

#include "ritem.h"
#include "rtransformation.h"

namespace chikkooos
{

class RTransformationItem: public RItem
{
public:
    RTransformationItem(RItem * parent = 0)
     : RItem(parent)
    {}

    void setTransformation(RTransformation const & f)
    {
        mTransformation = f;
    }

    RTransformation & transformation()
    {
        return mTransformation;
    }

    const RTransformation & transformation() const
    {
        return mTransformation;
    }
    
    void draw(RGc & gc) const;

    RItem * clone();
    void setProperties(RPropertyMap const & map, std::string const & element);

protected:
    RTransformation mTransformation;
};

}

#endif

