
#include "rview.h"
#include "rcontext.h"

namespace chikkooos
{

RView::RView()
{}

RView::~RView()
{}

RGc * RView::gc()
{
    if (mGc.isNull()) {
        mGc = RContext::instance().createGc();
    }

    return mGc;
}

void RView::onReshape(int w, int h)
{
    if (!mScene.isNull()) {
        mScene->onReshape(w, h);
    }
}

void RView::onMouseEvent(int button, int state, int x, int y)
{
    if (!mScene.isNull()) {
        mScene->onMouseEvent(button, state, x, y);
    }
}

void RView::onMouseMove(int x, int y)
{
    if (!mScene.isNull()) {
        mScene->onMouseMove(x, y);
    }
}

void RView::onUpdate(float dt)
{
    if (!mScene.isNull()) {
        mScene->update(dt);
    }
}

void RView::onDisplay() const
{
    if (!mScene.isNull()) {
        mScene->draw(*const_cast<RView *>(this)->gc());
    }
}

void RView::onTouchDown(int x, int y)
{
    if (!mScene.isNull()) {
        mScene->onTouchDown(x, y);
    }
}

void RView::onTouchUp(int x, int y)
{
    if (!mScene.isNull()) {
        mScene->onTouchUp(x, y);
    }
}

void RView::onSingleTap(int x, int y)
{
    if (!mScene.isNull()) {
        mScene->onSingleTap(x, y);
    }
}

void RView::onDoubleTap(int x, int y)
{
    if (!mScene.isNull()) {
        mScene->onDoubleTap(x, y);
    }
}

void RView::onKeyEvent(unsigned char key, int x, int y)
{
    if (!mScene.isNull()) {
        mScene->onKeyEvent(key, x, y);
    }
}

void RView::onPause()
{
    mGc = 0;
}

void RView::onResume()
{}

}

