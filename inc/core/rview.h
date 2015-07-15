
#ifndef RVIEW_H
#define RVIEW_H

#include "rbinder.h"
#include "rgc.h"
#include "rscene.h"

namespace chikkooos
{

class RView
{
public:
    RView();

    virtual ~RView();

    virtual bool onInit()
    {
        return true;
    }

    virtual void onUpdate(float dt);

    virtual void onMenuItemClicked(int /*id*/)
    {}

    virtual void onReshape(int w, int h);

    virtual void onMouseEvent(int button, int state, int x, int y);

    virtual void onMouseMove(int x, int y);

    virtual void onDisplay() const;

    virtual void onSwipeLeftToRight()
    {}
    virtual void onSwipeRightToLeft()
    {}
    virtual void onSwipeTopToBottom()
    {}
    virtual void onSwipeBottomToTop()
    {}

	virtual void onTouchDown(int x, int y);

	virtual void onTouchUp(int x, int y);

    virtual void onSingleTap(int x, int y);

    virtual void onDoubleTap(int x, int y);

    static RBinder & binder()
    {
        return RBinder::instance();
    }

    static RView * instance()
    {
        return binder().renderer();
    }

    virtual RGc * gc();

    virtual void onKeyEvent(unsigned char key, int x, int y);

    void setScene(RScene * scene)
    {
        mScene = scene;
    }

    RScene * scene()
    {
        return mScene;
    }

    virtual void onPause();

    virtual void onResume();

    virtual RCamera camera()
    {
        return RCamera();
    }

    virtual RFrustum frustum()
    {
        return RFrustum();
    }

    int getWidth()
    {
        return binder().getWidth();
    }

    int getHeight()
    {
        return binder().getHeight();
    }

protected:
    RSmartPointer<RGc> mGc;
    RSmartPointer<RScene> mScene;
};

}

#endif

