
#include "rgles1framebufferimpl.h"

#if defined(R_ES)

#define GL_RENDERBUFFER GL_RENDERBUFFER_OES
#define GL_DEPTH_COMPONENT16 GL_DEPTH_COMPONENT16_OES
#define GL_FRAMEBUFFER GL_FRAMEBUFFER_OES
#define GL_COLOR_ATTACHMENT0 GL_COLOR_ATTACHMENT0_OES
#define GL_DEPTH_ATTACHMENT GL_DEPTH_ATTACHMENT_OES

#define glGenFramebuffers glGenFramebuffersOES
#define glGenRenderbuffers glGenRenderbuffersOES
#define glBindFramebuffer glBindFramebufferOES
#define glFramebufferTexture2D glFramebufferTexture2DOES
#define glFramebufferRenderbuffer glFramebufferRenderbufferOES
#define glBindRenderbuffer glBindRenderbufferOES
#define glRenderbufferStorage glRenderbufferStorageOES

#endif

namespace chikkooos
{

RGles1FrameBufferImpl::RGles1FrameBufferImpl()
{}

RGles1FrameBufferImpl::~RGles1FrameBufferImpl()
{}

bool RGles1FrameBufferImpl::create()
{
    if (!mCreated) {
        glGenFramebuffers(1, &mFrameBuffer);
        glGenRenderbuffers(1, &mDepthBuffer);

	    mColorTextureBuffer.set(mWidth, mHeight, 0, 0, 0, GL_RGBA);

        mColorTextureBuffer.bind();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glBindRenderbuffer(GL_RENDERBUFFER, mDepthBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, mWidth, mHeight);

        glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffer);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                               mColorTextureBuffer.handle(), 0);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                                  GL_RENDERBUFFER, mDepthBuffer);

        mColorTextureBuffer.unbind();
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        mCreated = true;
    }
    return mCreated;
}

bool RGles1FrameBufferImpl::bind()
{
    if (mCreated) {
        glBindFramebuffer(GL_FRAMEBUFFER, mFrameBuffer);
    } else {
        return false;
    }
    return true;
}

void RGles1FrameBufferImpl::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

}


