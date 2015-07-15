
#include "rlightitem.h"

namespace chikkooos
{

void RLightItem::draw(RGc & gc) const
{
    gc.addLight(&mLight);

    RItem::draw(gc);

    gc.removeLight(&mLight);
}

RItem * RLightItem::clone()
{
    return new RLightItem(*this);
}

void RLightItem::setProperties(RPropertyMap const & map, std::string const & element)
{
    mLight.setAmbient(map.getVector("ambient", mLight.ambient()));
    mLight.setDiffuse(map.getVector("diffuse", mLight.diffuse()));
    mLight.setSpecular(map.getVector("specular", mLight.specular()));
    mLight.setPosition(map.getVector("position", mLight.position()));
    mLight.setDirection(map.getVector("direction", mLight.direction()));
    mLight.setSpotExponent(map.getFloat("exponent", mLight.spotExponent()));
    mLight.setSpotCutoff(map.getFloat("cutoff", mLight.spotCutoff()));
    mLight.setConstAttenuation(map.getFloat("constatten", mLight.constAttenuation()));
    mLight.setLinearAttenuation(map.getFloat("linearatten", mLight.linearAttenuation()));
    mLight.setQuadAttenuation(map.getFloat("quadatten", mLight.quadAttenuation()));
}

}

