
#include "rbinder.h"
#include "rview.h"

#include <stdlib.h>

namespace chikkooos
{

RBinder::~RBinder()
{
    mLastTime.start();
}

void RBinder::setRenderer(RView * r)
{
    if (!mRenderers.empty()) {
        mReplaceView = true;
        mOldView = mRenderers.top();
    }

    pushRenderer(r);
    mPauseView = false;
}

void RBinder::popRenderer()
{
    if (!mRenderers.empty()) {
        mReplaceView = true;
        mOldView = mRenderers.top();
        mRenderers.pop();

        if (!mRenderers.empty()) {
            RView *current = mRenderers.top();
            if (current) {
                rLogI() << "Screen Size (" << getWidth() << " x " << getHeight() << ")" << std::endl;
                current->onInit();
                current->onResume();
                current->onReshape(getWidth(), getHeight());
            }
        }
    }
}

void RBinder::pushRenderer(RView * r)
{
    if (!mRenderers.empty()) {
        mPauseView = true;
        mOldView = mRenderers.top();
    }

    mRenderers.push(RSmartPointer<RView>(r));
    if (mHasDrawn) {
        rLogI() << "Screen Size (" << getWidth() << " x " << getHeight() << ")" << std::endl;
        if (r->onInit()) {
            r->onResume();
            r->onReshape(getWidth(), getHeight());
        } else {
            popRenderer();
        }
    }
}

void RBinder::update()
{
    float dt = (float)mLastTime.elapsed() / 1000.0f;
    if (dt < 0.0f) {
        dt = 0.0f;
    }

    if (renderer()) {
        renderer()->onUpdate(dt);
        mHasDrawn = true;
    }

    mLastTime.start();
}

void RBinder::draw()
{
    if (mReplaceView && mOldView) {
        mPauseView = false;
        if (++mWaitCount > 5) {
            mReplaceView = false;
            mOldView->onPause();
            mOldView = 0;
            mWaitCount = 0;
        }
    } else if (mPauseView && mOldView) {
        if (++mWaitCount > 5) {
            mOldView->onPause();
            mPauseView = false;
            mWaitCount = 0;
        }
    }

    if (renderer()) {
        renderer()->onDisplay();
        mHasDrawn = true;
    }

}

void RBinder::swipeLeftToRight()
{
    if (renderer()) {
        renderer()->onSwipeLeftToRight();
    }
}

void RBinder::swipeRightToLeft()
{
    if (renderer()) {
        renderer()->onSwipeRightToLeft();
    }
}

void RBinder::swipeTopToBottom()
{
    if (renderer()) {
        renderer()->onSwipeTopToBottom();
    }
}

void RBinder::swipeBottomToTop()
{
    if (renderer()) {
        renderer()->onSwipeBottomToTop();
    }
}


void RBinder::singleTap(int x, int y)
{
    if (renderer()) {
        renderer()->onSingleTap(x, y);
    }
}

void RBinder::touchDown(int x, int y)
{
    if (renderer()) {
        renderer()->onTouchDown(x, y);
    }
}

void RBinder::touchUp(int x, int y)
{
    if (renderer()) {
        renderer()->onTouchUp(x, y);
    }
}

void RBinder::keyPress(int key, int x, int y)
{
    if (renderer()) {
        renderer()->onKeyEvent(key, x, y);
    }
}

void RBinder::mouseMove(int x, int y)
{
    if (renderer()) {
        renderer()->onMouseMove(x, y);
    }
}

void RBinder::touchScroll(int x, int y)
{
    mouseMove(x, y);
}

void RBinder::mouseEvent(int button, int state, int x, int y)
{
    if (renderer()) {
        renderer()->onMouseEvent(button, state, x, y);
    }
}

void RBinder::doubleTap(int x, int y)
{
    if (renderer()) {
        renderer()->onDoubleTap(x, y);
    }
}

void RBinder::pause()
{
    if (renderer()) {
        renderer()->onPause();
    }
}

void RBinder::resume()
{
    if (renderer()) {
        renderer()->onResume();
    }
}

}
