
#ifndef RGC_H
#define RGC_H

#include "rcommon.h"
#include "rcamera.h"
#include "rfrustum.h"
#include "rtransformation.h"
#include "rlight.h"
#include "rmaterial.h"
#include "rtexture.h"
#include "rtextureregion.h"
#include "rsharedobject.h"
#include "rshape.h"
#include "rparticles.h"

#include <set>
#include <sstream>
#include <string>

namespace chikkooos
{

class RGcState
{
public:
    typedef std::set<const RLight *> Lights;
    typedef Lights::iterator LightsIter;
    typedef Lights::const_iterator LightsConstIter;

public:
    RGcState()
     : mForegroundColor(1.0f, 1.0f, 1.0f, 1.0f),
       mBackgroundColor(0.0f, 0.0f, 0.0f, 0.0f),
       mGlobalAmbientColor(0.2f, 0.2f, 0.2f, 1.0f),
       mTextureTransform(0),
       mViewX(0),
       mViewY(0),
       mViewWidth(1),
       mViewHeight(1),
       mInitialized(false)
    {}

public:
    RCamera mCamera;
    RFrustum mFrustum;
    RTransformation mTrans;
    RMaterial mMaterial;
    RTexture mTexture;
    Lights mLights;
    RTexture mBoundTexture;
    RColor mForegroundColor;
    RColor mBackgroundColor;
    RColor mGlobalAmbientColor;
    const RTextureTransform * mTextureTransform;
    int mViewX;
    int mViewY;
    int mViewWidth;
    int mViewHeight;
    bool mInitialized;
};

class RGc: public RSharedObject<RGcState>
{
public:
    typedef RGcState::Lights Lights;
    typedef RGcState::LightsIter LightsIter;
    typedef RGcState::LightsConstIter LightsConstIter;

public:
    RGc();
    virtual ~RGc();

    RColor backgroundColor() const
    {
        return data_p().mBackgroundColor;
    }

    void setBackgroundColor(RColor const & color);

    RColor foregroundColor() const
    {
        return data_p().mForegroundColor;
    }

    void setForegroundColor(RColor const & color)
    {
        data_p().mForegroundColor = color;
    }

    RColor globalAmbientColor() const
    {
        return data_p().mGlobalAmbientColor;
    }

    void setGlobalAmbientColor(RColor const & color)
    {
        data_p().mGlobalAmbientColor = color;
    }

    RMaterial material() const
    {
        return data_p().mMaterial;
    }

    void setMaterial(RMaterial const & m)
    {
        data_p().mMaterial = m;
    }

    RTexture texture() const
    {
        return data_p().mTexture;
    }

    void setTexture(RTexture const & t)
    {
        data_p().mTexture = t;
    }

    const RTextureTransform * textureTransform() const
    {
        return data_p().mTextureTransform;
    }

    void setTextureTransform(const RTextureTransform * t)
    {
        data_p().mTextureTransform = t;
    }

    void bindTexture(RTexture const & t);
    void unbindTexture();

    void enable(GLenum cap);
    void disable(GLenum cap);

    RCamera camera() const
    {
        return data_p().mCamera;
    }

    void setCamera(RCamera const & c)
    {
        data_p().mCamera = c;
    }

    RFrustum frustum() const
    {
        return data_p().mFrustum;
    }

    void setFrustum(RFrustum const & c)
    {
        data_p().mFrustum = c;
    }

    void setViewport(int x, int y, int width, int height);

    void clear();

    void pushTransform()
    {
        data_p().mTrans.push();
    }

    void popTransform()
    {
        data_p().mTrans.pop();
    }

    void setTransformation(RTransformation const &s)
    {
        data_p().mTrans.load(s.matrix());
    }

    RTransformation transformation() const
    {
        return data_p().mTrans;
    }

    void multiplyTransformation(RTransformation const & t)
    {
        RTransformation r = data_p().mTrans.multiply(t);
        data_p().mTrans.load(r.matrix());
    }

    virtual void save();
    virtual void restore();

    void addLight(const RLight *l)
    {
        data_p().mLights.insert(l);
    }
    void removeLight(const RLight * l);

    bool initialize()
    {
        if (!data_p().mInitialized) {
            return doInitialize();
        }
        return true;
    }

    void flush();
    void finish();

    virtual void draw(RShape const & s) = 0;
    virtual void draw(RParticles const & ps) = 0;
    virtual void drawShadow(RShape const & s) = 0;

protected:
    virtual bool doInitialize() = 0;
};

}

#endif

