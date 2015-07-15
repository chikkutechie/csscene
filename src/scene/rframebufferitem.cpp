
#include "rframebufferitem.h"

#include <map>

namespace chikkooos
{

void RFrameBufferItem::draw(RGc & gc) const
{
    if (type() == Creator) {
        mFrameBuffer.create();
    }
    mFrameBuffer.bind();
    RItem::draw(gc);
    mFrameBuffer.unbind();
}

RItem * RFrameBufferItem::clone()
{
    return new RFrameBufferItem(type());
}

void RFrameBufferItem::setProperties(RPropertyMap const & map, std::string const & element)
{
}

}

