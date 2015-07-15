
#include "rgcsettings.h"

namespace chikkooos
{

RGCSettings::RGCSettings()
 : mDepthTest(-1),
   mBlending(-1),
   mCulling(-1)
{}

void RGCSettings::draw(RGc & gc) const
{
    if (mDepthTest == 1) {
        gc.enable(GL_DEPTH_TEST);
    } else if (mDepthTest == 0) {
        gc.disable(GL_DEPTH_TEST);
    }

    if (mBlending == 1) {
        gc.enable(GL_BLEND);
    } else if (mBlending == 0) {
        gc.disable(GL_BLEND);
    }

    if (mCulling == 1) {
        gc.enable(GL_CULL_FACE);
    } else if (mCulling == 0) {
        gc.disable(GL_CULL_FACE);
    }

    const_cast<RGCSettings *>(this)->mDepthTest = -1;
    const_cast<RGCSettings *>(this)->mCulling = -1;
    const_cast<RGCSettings *>(this)->mBlending = -1;
}

RItem * RGCSettings::clone()
{
    return new RGCSettings();
}

void RGCSettings::setProperties(RPropertyMap const & map, std::string const & element)
{
    if (element.compare("depthtest") == 0) {
        mDepthTest = map.getInt("enable", -1);
    } else if (element.compare("blending") == 0) {
        mBlending = map.getInt("enable", -1);
    } else if (element.compare("culling") == 0) {
        mCulling = map.getInt("enable", -1);
    }
}

}
