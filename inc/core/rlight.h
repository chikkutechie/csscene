
#ifndef RLIGHT_H
#define RLIGHT_H

#include "rvector.h"
#include "rcolor.h"

namespace chikkooos
{

class RLight
{
public:
    RLight()
    {
        reset();
    }

    bool operator==(RLight const & oth) const
    {
       return
           mAmbient == oth.mAmbient &&
           mDiffuse == oth.mDiffuse &&
           mSpecular == oth.mSpecular &&
           mPosition == oth.mPosition &&
           mSpotDirection == oth.mSpotDirection &&
           mSpotExponent == oth.mSpotExponent &&
           mSpotCutoff == oth.mSpotCutoff &&
           mConstAttenuation == oth.mConstAttenuation &&
           mLinearAttenuation == oth.mLinearAttenuation &&
           mQuadAttenuation == oth.mQuadAttenuation;
    }

    bool operator!=(RLight const & oth) const
    {
        return !(*this == oth);
    }

    bool isDirectionLight() const
    {
        return mPosition.w() == 0.0f;
    }

    bool isSpotLight() const
    {
        return mSpotCutoff < 180.0f;
    }

    bool isPointLight() const
    {
        return !isDirectionLight() && !isSpotLight(); 
    }

    RColor ambient() const
    {
        return mAmbient;
    }
    void setAmbient(RColor const & v)
    {
        mAmbient = v;
    }

    RColor diffuse() const
    {
        return mDiffuse;
    }
    void setDiffuse(RColor const & v)
    {
        mDiffuse = v;
    }

    RColor specular() const
    {
        return mSpecular;
    }
    void setSpecular(RColor const & v)
    {
        mSpecular = v;
    }

    RVector position() const
    {
        return mPosition;
    }
    void setPosition(RVector const & v)
    {
        mPosition = v;
    }

    RVector direction() const
    {
        return mSpotDirection;
    }
    void setDirection(RVector const & v)
    {
        mSpotDirection = v;
    }

    float spotExponent() const
    {
        return mSpotExponent;
    }
    void setSpotExponent(float v)
    {
        mSpotExponent = v;
    }

    float spotCutoff() const
    {
        return mSpotCutoff;
    }
    void setSpotCutoff(float v)
    {
        mSpotCutoff = v;
    }

    float constAttenuation() const
    {
        return mConstAttenuation;
    }
    void setConstAttenuation(float v)
    {
        mConstAttenuation = v;
    }

    float linearAttenuation() const
    {
        return mLinearAttenuation;
    }
    void setLinearAttenuation(float v)
    {
        mLinearAttenuation = v;
    }

    float quadAttenuation() const
    {
        return mQuadAttenuation;
    }
    void setQuadAttenuation(float v)
    {
        mQuadAttenuation = v;
    }

    void reset()
    {
        mAmbient.set(0.0f, 0.0f, 0.0f, 1.0f);

        mDiffuse.set(1.0f, 1.0f, 1.0f, 1.0f);
        mSpecular.set(1.0f, 1.0f, 1.0f, 1.0f);

        mPosition.set(0.0f, 0.0f, 1.0f, 0.0f);
        mSpotDirection.set(0.0f, 0.0f, -1.0f, 1.0f);

        mSpotExponent = 0.0f;
        mSpotCutoff = 180.0f;

        mConstAttenuation = 1.0f;
        mLinearAttenuation = 0.0f;
        mQuadAttenuation = 0.0f;
    }

private:
    RColor mAmbient;
    RColor mDiffuse;
    RColor mSpecular;
    RVector mPosition;
    RVector mSpotDirection;
    float mSpotExponent;
    float mSpotCutoff;
    float mConstAttenuation;
    float mLinearAttenuation;
    float mQuadAttenuation;
};

}

#endif

