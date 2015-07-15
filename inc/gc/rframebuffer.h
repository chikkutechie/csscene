
#ifndef RFRAMEBUFFER_H
#define RFRAMEBUFFER_H

#include "rcommon.h"
#include "rframebufferimpl.h"

namespace chikkooos
{

class RFrameBuffer
{
public:
    RFrameBuffer(int width=64, int height=64)
     : mWidth(width),
       mHeight(height),
       mImpl(0)
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
    
    bool create();

    bool bind();

    void unbind()
    {
        mImpl->unbind();
    }

private:
    int mWidth;
    int mHeight;
    bool mCreated;
    RFrameBufferImpl * mImpl;
};

}

#endif

