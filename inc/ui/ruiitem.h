
#ifndef RUIITEM_H
#define RUIITEM_H

#include "ritem.h"
#include "revent.h"
#include "reventmanager.h"

namespace chikkooos
{

class RUIItem: public RItem
{
protected:
    REventListner * mClickListner;
    std::string mClickListnerName;

public:
    RUIItem()
     : mClickListner(0)
    {}

    virtual void draw(RGc & gc) const;
    virtual void setProperties(RPropertyMap const & map, std::string const & element);

};

}

#endif
