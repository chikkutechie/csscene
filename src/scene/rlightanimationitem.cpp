
#include "rlightanimationitem.h"

namespace chikkooos
{

void RLightAnimationItem::draw(RGc & gc) const
{
    if (mAnimation.state() == RAnimation::None) {
        const_cast<RLightAnimationItem *>(this)->mAnimation.start();
    } else if (mAnimation.state() == RAnimation::Running) {
        const_cast<RLightAnimationItem *>(this)->mAnimation.step();
    }
    gc.addLight(&(mAnimation.light()));
    RItem::draw(gc);
    gc.removeLight(&(mAnimation.light()));
}

RItem * RLightAnimationItem::clone()
{
    return new RLightAnimationItem(*this);
}

void RLightAnimationItem::setProperties(RPropertyMap const & map, std::string const & element)
{
    RAnimationItem::setProperties(map, element);

    RLight & fromL = mAnimation.fromLight();

    fromL.setAmbient(map.getVector("fromambient", fromL.ambient()));
    fromL.setDiffuse(map.getVector("fromdiffuse", fromL.diffuse()));
    fromL.setSpecular(map.getVector("fromspecular", fromL.specular()));
    fromL.setPosition(map.getVector("fromposition", fromL.position()));
    fromL.setDirection(map.getVector("fromdirection", fromL.direction()));
    fromL.setSpotExponent(map.getFloat("fromexponent", fromL.spotExponent()));
    fromL.setSpotCutoff(map.getFloat("fromcutoff", fromL.spotCutoff()));
    fromL.setConstAttenuation(map.getFloat("fromconstatten", fromL.constAttenuation()));
    fromL.setLinearAttenuation(map.getFloat("fromlinearatten", fromL.linearAttenuation()));
    fromL.setQuadAttenuation(map.getFloat("fromquadatten", fromL.quadAttenuation()));

    RLight & toL = mAnimation.toLight();

    toL.setAmbient(map.getVector("toambient", toL.ambient()));
    toL.setDiffuse(map.getVector("todiffuse", toL.diffuse()));
    toL.setSpecular(map.getVector("tospecular", toL.specular()));
    toL.setPosition(map.getVector("toposition", toL.position()));
    toL.setDirection(map.getVector("todirection", toL.direction()));
    toL.setSpotExponent(map.getFloat("toexponent", toL.spotExponent()));
    toL.setSpotCutoff(map.getFloat("tocutoff", toL.spotCutoff()));
    toL.setConstAttenuation(map.getFloat("toconstatten", toL.constAttenuation()));
    toL.setLinearAttenuation(map.getFloat("tolinearatten", toL.linearAttenuation()));
    toL.setQuadAttenuation(map.getFloat("toquadatten", toL.quadAttenuation()));
}

}

