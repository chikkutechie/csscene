
#ifndef RGLES2GC_H
#define RGLES2GC_H

#include "rgc.h"
#include "rshaderobject.h"

#include <set>
#include <sstream>
#include <string>

namespace chikkooos
{

class RGles2Gc: public RGc
{
public:
    typedef RGc::Lights Lights;
    typedef RGc::LightsIter LightsIter;
    typedef RGc::LightsConstIter LightsConstIter;

    class ShaderData
    {
    public:
        RShaderObject mShader;
        RShaderVariables mVariables;
    };

    typedef std::map<std::string, ShaderData> ProgramMap;
    typedef ProgramMap::iterator ProgramMapIter;
    typedef ProgramMap::const_iterator ProgramMapConstIter;

    class ProgramKey
    {
    public:
        ProgramKey()
         : mHasTexture(false),
           mHasTextureTransform(false),
           mLightCount(0),
           mHasDirLight(false),
           mHasSpotLight(false),
           mHasPointLight(false),
           mIsPointSprite(false),
           mHasPointSpriteAlpha(false)
        {}

        std::string toString() const
        {
            std::stringstream ss;

            ss << "shader:" <<
                  "t:"   << mHasTexture <<
                  "tt:"  << mHasTextureTransform <<
                  "l:"   << mLightCount <<
                  "dl:"  << mHasDirLight <<
                  "sl:"  << mHasSpotLight <<
                  "pl:"  << mHasPointLight <<
                  "ps:"  << mIsPointSprite <<
                  "psa:" << mHasPointSpriteAlpha;

            return ss.str();
        }

    public:
        bool mHasTexture;
        bool mHasTextureTransform;
        int mLightCount;
        bool mHasDirLight;
        bool mHasSpotLight;
        bool mHasPointLight;
        bool mIsPointSprite;
        bool mHasPointSpriteAlpha;
    };

public:
    RGles2Gc();
    ~RGles2Gc();

    virtual void draw(RShape const & s);
    virtual void draw(RParticles const & ps);
    virtual void drawShadow(RShape const & s);

protected:
    std::string createVertexShader(ProgramKey const & k) const;
    std::string createFragmentShader(ProgramKey const & k) const;

    ShaderData getProgram(ProgramKey * key=0);
    ShaderData getProgramUsingKey(ProgramKey const & key);

    void draw(RShape const & s, ShaderData & d, ProgramKey const & key);
    void drawSimple(RShape const & s, ShaderData const & d);
    void drawTexture(RShape const & s, ShaderData const & d);
    void drawLight(RShape const & s, ShaderData const & d);
    void drawShadow(const RShapePlane & s, RVector const & lp);

    virtual bool doInitialize();

    ProgramMap mProgramMap;
};

}

#endif

