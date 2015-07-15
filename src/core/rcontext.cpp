
#include "rcommon.h"
#include "rcontext.h"
#include "rlog.h"

#if defined(R_ES) || defined(RGL_FULL)
#include "rgles1gc.h"
#include "rgles1framebufferimpl.h"
#endif

#if defined(R_ES2) || defined(RGL_FULL)
#include "rgles2gc.h"
#include "rgles2framebufferimpl.h"
#endif

namespace chikkooos
{

RContext::RContext()
 : mContext("gles2")
{}

RContext & RContext::instance()
{
    static RContext context;
    return context;
}

void RContext::setContext(std::string const & name)
{
    if (name.compare("gles1") == 0) {
        mContext = name;
    } else if (name.compare("gles2") == 0) {
        mContext = name;
    } else {
        mContext = "gles2";
    }
}

RGc * RContext::createGc()
{

#if defined(R_ES)
    rLogI() << "GC : gles1" << std::endl;
    return new RGles1Gc();
#elif defined(R_ES2)
    rLogI() << "GC : gles2" << std::endl;
    return new RGles2Gc();
#else

    rLogI() << "GC : " << mContext << std::endl;
    if (mContext.compare("gles1") == 0) {
        return new RGles1Gc();
    } else if (mContext.compare("gles2") == 0) {
        return new RGles2Gc();
    } else {
        return new RGles2Gc();
    }

#endif

    rLogE() << "gc creation failed : " << mContext << std::endl;
    return 0;
}

RFrameBufferImpl * RContext::createFrameBufferImpl()
{
    if (mContext.compare("gles1") == 0) {
#if defined(R_ES) || defined(RGL_FULL)
        return new RGles1FrameBufferImpl();
#endif
    } else if (mContext.compare("gles2") == 0) {
#if defined(R_ES2) || defined(RGL_FULL) 
        return new RGles2FrameBufferImpl();
#endif
    } else {
#if defined(R_ES2) || defined(RGL_FULL)
        return new RGles2FrameBufferImpl();
#endif
    }
    rLogE() << "framebuffer implementation creation failed" << std::endl;
    return 0;
}

}

