
#include "rfrustumitem.h"

namespace chikkooos
{

void RFrustumItem::draw(RGc & gc) const
{
    RFrustum of = gc.frustum();

    gc.setFrustum(mFrustum);

    RItem::draw(gc);

    gc.setFrustum(of);
}

RItem * RFrustumItem::clone()
{
    return new RFrustumItem(*this);
}

void RFrustumItem::setProperties(RPropertyMap const & map, std::string const & element)
{
    
    if (element.compare("parallel") == 0) {
        mFrustum.parallel(map.getFloat("left"),
                          map.getFloat("right"),
                          map.getFloat("bottom"),
                          map.getFloat("top"),
                          map.getFloat("near"),
                          map.getFloat("far"));
    } else if (element.compare("perspective") == 0) {
        mFrustum.perspective(map.getFloat("left"),
                             map.getFloat("right"),
                             map.getFloat("bottom"),
                             map.getFloat("top"),
                             map.getFloat("near"),
                             map.getFloat("far"));
    } else if (element.compare("perspectivetheta") == 0) {
        mFrustum.perspectiveTheta(map.getFloat("fovy"),
                                  map.getFloat("aspect"),
                                  map.getFloat("near"),
                                  map.getFloat("far"));
    }
}

}

