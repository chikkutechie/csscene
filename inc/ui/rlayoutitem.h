
#ifndef RLAYOUTITEM_H
#define RLAYOUTITEM_H

#include "ruiitem.h"
#include "rfrustum.h"
#include "rcamera.h"
#include "rtransformation.h"

#include "scene/revent.h"

namespace chikkooos
{

class RLayoutItem: public RUIItem
{
public:
    virtual void setProperties(RPropertyMap const & map, std::string const & element)
    {
        RUIItem::setProperties(map, element);
    }
};

}

#endif
