
#ifndef RCAMERAANIMATION_H
#define RCAMERAANIMATION_H

#include "ranimation.h"
#include "rcamera.h"

namespace chikkooos
{

class RCameraAnimation: public RAnimation
{
public:
	RCameraAnimation();

    void setEye(const RVector se, const RVector & ee)
    {
        mStartEye = se;
        mEndEye = ee;
        mUpdateEye = (se != ee);
    }

    void setUp(const RVector su, const RVector & eu)
    {
        mStartUp = su;
        mEndUp = eu;
        mUpdateUp = (su != eu);
    }

    void setCenter(const RVector sc, const RVector & ec)
    {
        mStartCenter = sc;
        mEndCenter = ec;
        mUpdateCenter = (sc != ec);
    }

    const RCamera & camera() const
    {
        return mCamera;
    }

    const RVector & startEye() const
    {
        return mStartEye;
    }
    const RVector & endEye() const
    {
        return mEndEye;
    }

    const RVector & startCenter() const
    {
        return mStartCenter;
    }
    const RVector & endCenter() const
    {
        return mEndCenter;
    }

    const RVector & startUp() const
    {
        return mStartUp;
    }
    const RVector & endUp() const
    {
        return mEndUp;
    }

protected:
    void doReverse();

	void update( float elapsed);

protected:
    RVector mStartEye;
    RVector mEndEye;
    RVector mStartUp;
    RVector mEndUp;
    RVector mStartCenter;
    RVector mEndCenter;
    bool mUpdateEye;
    bool mUpdateCenter;
    bool mUpdateUp;
    RCamera mCamera;
};

}

#endif
