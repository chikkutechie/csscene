
#include "ruiitem.h"

namespace chikkooos
{

void RUIItem::draw(RGc & gc) const
{
    RItem::draw(gc);
}

void RUIItem::setProperties(RPropertyMap const & map, std::string const & element)
{
    RItem::setProperties(map, element);
}

}
