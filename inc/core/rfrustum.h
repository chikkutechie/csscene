
#ifndef RFRUSTUM_H
#define RFRUSTUM_H

#include "rcommon.h"
#include "rvector.h"
#include "rmatrix.h"

#include <cstring>
#include <cmath>
#include <stack>

namespace chikkooos
{

class RFrustum
{
public:
    enum Type
    {
        Parallel,
        Perspective
    };

public:
    const RMatrix & matrix() const
    {
        return mMatrix;
    }

    RMatrix & matrix()
    {
        return mMatrix;
    }

    void perspectiveTheta(float fovy, float aspect, float near, float far)
    {
    	mType = Perspective;
        mNear = near;
        mFar = far;
        mFovy = fovy;
        mAspect = aspect;

    	mMatrix = RMatrix::createPerspective(fovy, aspect, near, far);
    }

    void parallel(float left, float right, float bottom, float top, float near, float far)
    {
    	mType = Parallel;
        mNear = near;
        mFar = far;
    	mLeft = left;
        mRight = right;
        mTop = top;
        mBottom = bottom;

    	mMatrix = RMatrix::createOrthographic(left, right, bottom, top, near, far);
    }

    void perspective(float left, float right, float bottom, float top, float near, float far)
    {
    	mType = Perspective;
        mNear = near;
        mFar = far;
    	mLeft = left;
        mRight = right;
        mTop = top;
        mBottom = bottom;

    	mMatrix = RMatrix::createPerspective(left, right, bottom, top, near, far);
    }

    void reset()
    {
        mMatrix.reset();
    }

    Type type() const
    {
        return mType;
    }

    float near() const
    {
        return mNear;
    }

    float far() const
    {
        return mFar;
    }

    float fovy() const
    {
        return mFovy;
    }

    float top() const
    {
        return mTop;
    }

    float bottom() const
    {
        return mBottom;
    }

    float left() const
    {
        return mLeft;
    }

    float right() const
    {
        return mRight;
    }

    float aspect() const
    {
        return mAspect;
    }

private:
    float mNear;
    float mFar;
    float mFovy;
    float mAspect;
    float mLeft;
    float mRight;
    float mTop;
    float mBottom;
    Type mType;

    RMatrix mMatrix;
};

}

#endif

