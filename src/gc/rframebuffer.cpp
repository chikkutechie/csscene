
#include "rcommon.h"
#include "rframebuffer.h"
#include "rgles1framebufferimpl.h"
#include "rgles2framebufferimpl.h"
#include "rcontext.h"

namespace chikkooos
{

bool RFrameBuffer::create()
{
    if (!mImpl) {
        mImpl = RContext::instance().createFrameBufferImpl();
        mImpl->setSize(mWidth, mHeight);
        return mImpl->create();
    }
    return true;
}

bool RFrameBuffer::bind()
{
   if (!mImpl) {
        if (create()) {
            return mImpl->bind();
        }
    } else {
        return mImpl->bind();
    }
    return false;
}


}

