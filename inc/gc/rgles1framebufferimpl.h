
#ifndef RGLES1FRAMEBUFFERIMPL_H
#define RGLES1FRAMEBUFFERIMPL_H

#include "rframebufferimpl.h"

namespace chikkooos
{

class RGles1FrameBufferImpl: public RFrameBufferImpl
{
public:
    RGles1FrameBufferImpl();

    ~RGles1FrameBufferImpl();

    bool create();

    bool bind();

    void unbind();

};

}

#endif

