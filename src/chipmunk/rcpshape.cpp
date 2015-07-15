
#include "rcpshape.h"
#include "rcpbody.h"
#include "rcpworld.h"

namespace chikkooos
{

RCPShape::RCPShape(RCPBody *body)
 : mShape(0),
   mBody(body),
   mUserData(0),
   mShapeType(Box),
   mCollisionType(0),
   mCollisionSlop(0.0f),
   mFriction(0.5f),
   mElasticity(0.01f),
   mWidth(0),
   mHeight(0),
   mRadius(0)
{
}

RCPShape::~RCPShape()
{
    destroy();
}

void RCPShape::create()
{
    cpSpace * space = RCPWorld::instance()->space();

    if (mBody != 0 && mBody->body() != 0) {

        switch (mShapeType) {
            case Box:
            mShape = cpSpaceAddShape(space, cpBoxShapeNew(mBody->body(), mWidth, mHeight, 0.0));
            break;

            case Circle:
            mShape = cpSpaceAddShape(space, cpCircleShapeNew(mBody->body(), mRadius, cpvzero));
            break;

            case Segment:
            mShape = cpSpaceAddShape(space, cpSegmentShapeNew(mBody->body(), cpv(mA.x(), mA.y()), cpv(mB.x(), mB.y()), mRadius));
            break;
        }
    }

    if (mShape) {
        cpShapeSetElasticity(mShape, mElasticity);
        cpShapeSetFriction(mShape, mFriction);
    }

    setUserData(mUserData);
    setCollisionType(mCollisionType);
}

void RCPShape::setCollisionType(int t)
{
    mCollisionType = t;
    if (mShape) {
        cpShapeSetCollisionType(mShape, mCollisionType);
    }
}

void RCPShape::destroy()
{
    if (mShape) {

        if (RCPWorld::instance()) {
            cpSpace * space = RCPWorld::instance()->space();

            if (space) {
                cpSpaceRemoveShape(space, mShape);
                cpShapeFree(mShape);
            }
        }
        mShape = 0;
    }
}

void RCPShape::setUserData(cpDataPointer data)
{
    mUserData = data;
    if (mShape) {
        cpShapeSetUserData(mShape, mUserData);
    }
}

float RCPShape::moment(float mass) const
{
    float m = 0.0f;

    switch (mShapeType) {
        case Box:
        m = cpMomentForBox(mass, mWidth, mHeight);
        break;

        case Circle:
        m = cpMomentForCircle(mass, 0, mRadius, cpvzero);
        break;

        case Segment:
        m = cpMomentForSegment(mass, cpv(mA.x(), mA.y()), cpv(mB.x(), mB.y()), mRadius);
        break;
    }

    return m;
}

}
