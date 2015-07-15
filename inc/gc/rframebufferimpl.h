
#ifndef RFRAMEBUFFERIMPL_H
#define RFRAMEBUFFERIMPL_H

#include "rcommon.h"
#include "rtexture.h"

namespace chikkooos
{

class RFrameBufferImpl
{
public:
    RFrameBufferImpl()
     : mFrameBuffer(0),
       mDepthBuffer(0),
       mCreated(false)
    {}

    virtual ~RFrameBufferImpl()
    {}

    void setSize(int width, int height)
    {
        mWidth = width;
        mHeight = height;
    }

    int width() const
    {
        return mWidth;
    }

    int height() const
    {
        return mHeight;
    }
    
    bool inNull() const
    {
        return !mCreated;
    }

    virtual bool create() = 0;

    virtual bool bind() = 0;

    virtual void unbind() = 0;

protected:
    GLuint mFrameBuffer;
    GLuint mDepthBuffer;
    RTexture mColorTextureBuffer;
    int mWidth;
    int mHeight;
    bool mCreated;
};

}

#endif

