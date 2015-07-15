
#ifndef RBINDER_H
#define RBINDER_H

#include <stack>

#include "rcommon.h"
#include "rtime.h"

namespace chikkooos
{

class RView;

class RBinder
{
public:
    RBinder()
     : mGc("gles1"),
       mHasDrawn(false),
       mPauseView(false),
       mReplaceView(false),
       mWaitCount(0)
    {}

    virtual ~RBinder();

    static RBinder & instance();

    virtual bool initialize() = 0;
    virtual bool initialize(int argc, char **argv) = 0;
    virtual int exec() = 0;
    virtual void destroy() = 0;
    //virtual void addTimer(unsigned int delay = chikkooos::TimerDelay)
    //{}
    virtual void redraw()
    {}

    virtual int getWidth() = 0;
    virtual int getHeight() = 0;

    RView * renderer()
    {
        if (mRenderers.empty()) {
            return 0;
        }
        return mRenderers.top().data();
    }

    const RView * renderer() const
    {
        if (mRenderers.empty()) {
            return 0;
        }
        return mRenderers.top().data();
    }

    void setRenderer(RView * r);

    void popRenderer();

    void pushRenderer(RView * r);

    std::string gc() const
    {
        return mGc;
    }

    void swipeLeftToRight();
    void swipeRightToLeft();
    void swipeTopToBottom();
    void swipeBottomToTop();

    void singleTap(int x, int y);
    void doubleTap(int x, int y);

    void touchDown(int x, int y);
    void touchUp(int x, int y);
    void touchScroll(int x, int y);

    void keyPress(int key, int x, int y);

    void mouseMove(int x, int y);
    void mouseEvent(int button, int state, int x, int y);

    void pause();
    void resume();

protected:
    virtual void draw();
    virtual void update();

protected:
    std::stack< RSmartPointer<RView> > mRenderers;
    std::string mGc;

    bool mHasDrawn;

    bool mPauseView;
    bool mReplaceView;
    RSmartPointer<RView> mOldView;
    int mWaitCount;

    int mWidth;
    int mHeight;

    RTime mLastTime;
};

}

#endif

