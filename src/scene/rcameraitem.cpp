
#include "rcameraitem.h"

namespace chikkooos
{

void RCameraItem::draw(RGc & gc) const
{
    RCamera oc = gc.camera();

    gc.setCamera(mCamera);

    RItem::draw(gc);

    gc.setCamera(oc);
}


RItem * RCameraItem::clone()
{
    return new RCameraItem(*this);
}

void RCameraItem::setProperties(RPropertyMap const & map, std::string const & element)
{
    mCamera.setEye(map.getVector("eye", mCamera.eye()));
    mCamera.setCenter(map.getVector("center", mCamera.center()));
    mCamera.setUp(map.getVector("up", mCamera.up()));
}

}

