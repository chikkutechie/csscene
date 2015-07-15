
#ifndef RFRAMEBUFFERITEM_H
#define RFRAMEBUFFERITEM_H

#include "ritem.h"
#include "rframebuffer.h"

namespace chikkooos
{

class RFrameBufferItem: public RItem
{
public:
    enum Type
    {
        Creator,
        Renderer
    };

public:
    RFrameBufferItem(Type type = Creator, RItem * parent = 0)
     : RItem(parent), 
       mType(type)
    {}

    void setFrameBuffer(RFrameBuffer const & f)
    {
        mFrameBuffer = f;
    }

    RFrameBuffer framebuffer() const
    {
        return mFrameBuffer;
    }
    
    Type type() const
    {
        return mType;
    }

    void draw(RGc & gc) const;

    RItem * clone();
    void setProperties(RPropertyMap const & map, std::string const & element);

protected:
    mutable RFrameBuffer mFrameBuffer;
    Type mType;
};

}

#endif

