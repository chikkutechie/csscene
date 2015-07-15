
#ifndef VIEWER_h
#define VIEWER_h

#include "rbulletutil.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "rcommon.h"
#include "rtime.h"
#include "rview.h"
#include "rtransformationitem.h"
#include "rfrustumitem.h"
#include "rbulletworld.h"
#include "rdataprovider.h"
#include "rb2dworld.h"
#include "rcpworld.h"

using std::isfinite;

namespace chikkooos
{

class ViewerRenderer: public RView
{
public:
    ~ViewerRenderer()
    {}
    
    ViewerRenderer()
     : RView(),
       mSceneFile("data/physics.xml")
    {}

    void setSceneMap(std::string const & s)
    {
        mSceneFile = s;
    }

private:

    void onReshape(int w, int h)
    {
        mWidth = w;
        mHeight = h;

        gc()->setViewport(0, 0, mWidth, mHeight);

    }

    void onMouseEvent(int /*button*/, int /*state*/, int /*x*/, int /*y*/)
    {}

    void onDisplay() const
    {
        RView::onDisplay();
    }

    bool onInit()
    {
        onResume();

        if (mScene.isNull()) {
            return false;
        }

        mLastTime.start();

        return true;
    }

    void onPause()
    {
        RView::onPause();
        mScene = 0;
        mBulletWorld = 0;
    }

    void onResume()
    {
        if (mScene.isNull()) {

            gc()->setBackgroundColor(RColor(0.0f, 0.0f, 0.0f, 0.0f));

            mBulletWorld = RBulletWorld::instance();
    
            mScene = new RScene(this);

            RDataProvider::FileData *sceneData = RDataProvider::instance().fileData(mSceneFile);
            if (!sceneData) {
                rLogE() << "error in reading scene : " << mSceneFile << std::endl;
                onPause();
                return;
            }
        
            if (!mScene->loadFromData(sceneData->mData)) {
                rLogE() << "error in loading scene : " << mSceneFile << std::endl;
                delete sceneData;
                onPause();
                return;
            }

            delete sceneData;

            onReshape(mWidth, mHeight);
            mLastTime.start();
        }
    }

private:
    RBulletWorld* mBulletWorld;

    std::string mSceneFile;

	RTime mLastTime;
    int mWidth;
    int mHeight;
};

}

#endif

