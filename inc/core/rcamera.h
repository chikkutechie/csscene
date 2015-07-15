
#ifndef RCAMERA_H
#define RCAMERA_H

#include "rvector.h"
#include "rtransformation.h"

namespace chikkooos
{

class RCamera
{
public:
    RCamera();

    RVector eye() const
    {
        return mEye;
    }

    void setEye(RVector const &v)
    {
        mEye = v;
        applyLookAt();
    }

    RVector up() const
    {
        return mUp;
    }

    void setUp(RVector const &v)
    {
        mUp = v;
        applyLookAt();
    }

    RVector center() const
    {
        return mCenter;
    }

    void setCenter(RVector const &v)
    {
        mCenter = v;
        applyLookAt();
    }

    void lookAt(RVector const & eye, RVector const & up, RVector const & center)
    {
        mEye = eye;
        mUp = up;
        mCenter = center;
        applyLookAt();
    }

    const RTransformation & transformation() const
    {
        return mTransformation;
    }

private:
    void applyLookAt();

private:
    RVector mEye;
    RVector mUp;
    RVector mCenter;
    RTransformation mTransformation;
};

}

#endif

