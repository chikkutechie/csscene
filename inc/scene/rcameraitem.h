
#ifndef RCAMERAITEM_H
#define RCAMERAITEM_H

#include "ritem.h"
#include "rcamera.h"

namespace chikkooos
{

class RCameraItem: public RItem
{
public:
    RCameraItem(RItem * parent = 0)
     : RItem(parent)
    {}

    void setCamera(RCamera const & f)
    {
        mCamera = f;
    }

    RCamera camera() const
    {
        return mCamera;
    }
    
    void draw(RGc & gc) const;

    RItem * clone();
    void setProperties(RPropertyMap const & map, std::string const & element);

protected:
    RCamera mCamera;
};

}

#endif

