
#include "ranimationitem.h"

namespace chikkooos
{

void RAnimationItem::setProperties(RPropertyMap const & map, std::string const &)
{
    animation().reset();

    if (map.has("interval")) {
        animation().setInterval(map.getFloat("interval"));
    }
    
    if (map.has("duration")) {
        animation().setDuration(map.getFloat("duration"));
    }
    
    if (map.has("repeat")) {
        animation().setRepeat(map.getInt("repeat"));
    }
    
    if (map.has("reverse")) {
        animation().setReverse(map.getInt("reverse"));
    }
    
    REasingCurve ec;
    std::string easing = map.getString("easing", "linear");
    if (easing.compare("linear") == 0) {
        ec.setType(REasingCurve::Linear);
    } else if (easing.compare("quadin") == 0) {
        ec.setType(REasingCurve::QuadIn);
    } else if (easing.compare("cubicin") == 0) {
        ec.setType(REasingCurve::CubicIn);
    }
    animation().setEasingCurve(ec);
}

}

