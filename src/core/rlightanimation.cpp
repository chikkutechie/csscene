
#include "rlightanimation.h"

namespace chikkooos
{

void RLightAnimation::doReverse()
{
    RLight t = mFromLight;
    mFromLight = mToLight;
    mToLight = t;
}

void RLightAnimation::update(float elapsed)
{
    float t = elapsed / mDuration;

    mLight.setAmbient(interpolate(mFromLight.ambient(), mToLight.ambient(), t));
    mLight.setDiffuse(interpolate(mFromLight.diffuse(), mToLight.diffuse(), t));
    mLight.setSpecular(interpolate(mFromLight.specular(), mToLight.specular(), t));

    if (mFromLight.position() != mToLight.position()) {
        mLight.setPosition(interpolate(mFromLight.position(), mToLight.position(), t));
    }

    if (mFromLight.spotExponent() != mToLight.spotExponent()) {
        mLight.setSpotExponent(interpolate(mFromLight.spotExponent(), mToLight.spotExponent(), t));
    }

    if (mFromLight.spotCutoff() != mToLight.spotCutoff()) {
        mLight.setSpotCutoff(interpolate(mFromLight.spotCutoff(), mToLight.spotCutoff(), t));
    }

    if (mFromLight.linearAttenuation() != mToLight.linearAttenuation()) {
        mLight.setLinearAttenuation(interpolate(mFromLight.linearAttenuation(), mToLight.linearAttenuation(), t));
    }

    if (mFromLight.quadAttenuation() != mToLight.quadAttenuation()) {
        mLight.setQuadAttenuation(interpolate(mFromLight.quadAttenuation(), mToLight.quadAttenuation(), t));
    }
}	

}

