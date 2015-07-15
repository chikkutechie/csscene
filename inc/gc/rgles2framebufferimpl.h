
#ifndef RGLES2FRAMEBUFFERIMPL_H
#define RGLES2FRAMEBUFFERIMPL_H

#include "rframebufferimpl.h"

namespace chikkooos
{

class RGles2FrameBufferImpl: public RFrameBufferImpl
{
public:
    RGles2FrameBufferImpl();

    ~RGles2FrameBufferImpl();

    bool create();

    bool bind();

    void unbind();
};

}

#endif

