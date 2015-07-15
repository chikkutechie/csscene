
#include "rcommon.h"
#include "rgc.h"
#include "rlog.h"

#include <stdexcept>

namespace chikkooos
{

RGc::RGc()
{}

RGc::~RGc()
{}

void RGc::save()
{
    data_p().mTrans.push();
}

void RGc::restore()
{
    data_p().mTrans.pop();
}

void RGc::setBackgroundColor(RColor const & color)
{
    if (color != data_p().mBackgroundColor) {
        data_p().mBackgroundColor = color;

        if (data_p().mInitialized) {
            glClearColor(backgroundColor().r(), backgroundColor().g(),
                         backgroundColor().b(), backgroundColor().a());
        }
    }
}

void RGc::setViewport(int x, int y, int width, int height)
{
    if (data_p().mViewX != x ||
        data_p().mViewY != y ||
        data_p().mViewWidth != width ||
        data_p().mViewHeight != height) {

        data_p().mViewX = x;
        data_p().mViewY = y;
        data_p().mViewWidth = width;
        data_p().mViewHeight = height;

        if (data_p().mInitialized) {
            glViewport(data_p().mViewX, data_p().mViewY,
                       data_p().mViewWidth, data_p().mViewHeight);
        }
    }
}

void RGc::clear()
{
    initialize();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void RGc::removeLight(const RLight * l)
{
    LightsIter iter = data_p().mLights.find(l);
    if (iter != data_p().mLights.end()) {
        data_p().mLights.erase(l);
    }
}

void RGc::bindTexture(RTexture const & t)
{
    if (data_p().mBoundTexture.isNull() ||
        (data_p().mBoundTexture != t)) {
        t.bind();
        data_p().mBoundTexture = t;
    }
}

void RGc::unbindTexture()
{
    if (!data_p().mBoundTexture.isNull()) {
        glBindTexture(GL_TEXTURE_2D, 0);
        data_p().mBoundTexture = RTexture();
    }
}

void RGc::flush()
{
    glFlush();
}

void RGc::finish()
{
    glFinish();
}

void RGc::enable(GLenum cap)
{
    glEnable(cap);
    RCheckGLError();
}

void RGc::disable(GLenum cap)
{
    glDisable(cap);
}

}

