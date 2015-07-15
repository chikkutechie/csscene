
#ifndef RCPSHAPE_H
#define RCPSHAPE_H

#include "rtransformation.h"
#include "rutils.h"

#include <chipmunk/chipmunk.h>

namespace chikkooos
{

class RCPBody;

class RCPShape
{
public:
    enum Shape
    {
        Box,
        Circle,
        Segment
    };

public:
    RCPShape(RCPBody *body = 0);
    ~RCPShape();

    void setBody(RCPBody *body)
    {
        mBody = body;
    }

    RCPBody * body()
    {
        return mBody;
    }

    cpShape * shape()
    {
        return mShape;
    }

    void setShapeType(Shape s)
    {
        mShapeType = s;
    }

    Shape shapeType() const
    {
        return mShapeType;
    }

    void setSize(float w, float h)
    {
        mWidth = w;
        mHeight = h;
    }

    RSizeF size() const
    {
        return RSizeF(mWidth, mHeight);
    }

    void setRadius(float r)
    {
        mRadius = r;
    }

    float radius() const
    {
        return mRadius;
    }

    void setSegmentPos(float x1, float y1, float x2, float y2)
    {
        mA.set(x1, y1);
        mB.set(x2, y2);
    }

    RVector segmentStart() const
    {
        return mA;
    }

    RVector segmentEnd() const
    {
        return mB;
    }

    void setFriction(float f)
    {
        mFriction = f;
    }

    float friction() const
    {
        return mFriction;
    }

    void setElasticity(float e)
    {
        mElasticity = e;
    }

    float elasticity() const
    {
        return mElasticity;
    }

    void create();
    void destroy();

    float moment(float mass) const;

    bool isNull() const
    {
        return (mShape != 0);
    }

    void setUserData(cpDataPointer data);
    cpDataPointer userData()
    {
        return mUserData;
    }
    const cpDataPointer userData() const
    {
        return mUserData;
    }

    void setCollisionType(int t);

    int collisionType() const
    {
        return mCollisionType;
    }

protected:
    cpShape * mShape;
    RCPBody * mBody;
    cpDataPointer mUserData;

    Shape mShapeType;
    int mCollisionType;
    float mCollisionSlop;

    float mFriction;
    float mElasticity;

    RVector mA;
    RVector mB;
    float mWidth;
    float mHeight;
    float mRadius;
};

}

#endif
