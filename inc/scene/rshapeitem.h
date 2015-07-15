
#ifndef RSHAPEITEM_H
#define RSHAPEITEM_H

#include "ritem.h"
#include "rshape.h"
#include "rsmartpointer.h"

namespace chikkooos
{

class RShapeItem: public RItem
{
public:
    RShapeItem(RItem * parent = 0)
     : RItem(parent),
       mShadow(false)
    {}

    ~RShapeItem()
    {}

    void setShape(RSmartPointer<RShape> const & s)
    {
        mShape = s;
    }

    RSmartPointer<RShape> shape() const
    {
        return mShape;
    }
    
    void draw(RGc & gc) const;

    RItem * clone();

    void setProperties(RPropertyMap const & map, std::string const & element);
    
    static RShape * fromProperty(RPropertyMap const & map);

protected:
    RSmartPointer<RShape> mShape;
    bool mShadow;
};

}

#endif

