
#ifndef RMATERIALITEM_H
#define RMATERIALITEM_H

#include "ritem.h"
#include "rmaterial.h"

namespace chikkooos
{

class RMaterialItem: public RItem
{
public:
    RMaterialItem(RItem * parent = 0)
     : RItem(parent)
    {}

    void setMaterial(RMaterial const & f)
    {
        mMaterial = f;
    }

    RMaterial & material()
    {
        return mMaterial;
    }
    
    const RMaterial & material() const
    {
        return mMaterial;
    }
    
    void draw(RGc & gc) const;

    RItem * clone();
    void setProperties(RPropertyMap const & map, std::string const & element);

protected:
    RMaterial mMaterial;
};

}

#endif

