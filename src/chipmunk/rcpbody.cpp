
#include "rcpbody.h"
#include "rcpworld.h"

namespace chikkooos
{

RCPBody::RCPBody()
 : mBody(0),
   mUserData(0),
   mType(Dynamic),
   mAngle(0),
   mMass(0),
   mMoment(0.0f)
{}

RCPBody::~RCPBody()
{
    destroy();
}

void RCPBody::create()
{
    if (RCPWorld::instance()) {
        cpSpace * space = RCPWorld::instance()->space();
        if (mType == Dynamic) {
            mBody = cpSpaceAddBody(space, cpBodyNew(mMass, mMoment));
        } else if (mType == Static) {
            mBody = cpSpaceGetStaticBody(space);
        }
    }

    setForce(mForce);
    setVelocity(mVelocity);
    setPosition(mPosition);
    setAngle(mAngle);
    setUserData(mUserData);
}

void RCPBody::destroy()
{
    // remove all shapes before removing the body
    mShapes.clear();

    if (mType != Static && RCPWorld::instance()) {
        cpSpace * space = RCPWorld::instance()->space();
        if (mBody && space) {
            cpSpaceRemoveBody(space, mBody);
            cpBodyFree(mBody);
        }
    }

    mBody = 0;
}

void RCPBody::setVelocity(RVector const & v)
{
    mVelocity = v;

    if (mType != Static && mBody) {
        cpBodySetVelocity(mBody, cpv(mVelocity.x(), mVelocity.y()));
    }
}

RVector RCPBody::velocity() const
{
    if (mBody) {
        cpVect p = cpBodyGetVelocity(mBody);
        mVelocity = RVector(p.x, p.y);
    }

    return mVelocity;
}

void RCPBody::setForce(RVector const & f)
{
    mForce = f;

    if (mType != Static && mBody) {
        cpBodySetForce(mBody, cpv(mForce.x(), mForce.y()));
    }
}

RVector RCPBody::force() const
{
    if (mBody) {
        cpVect p = cpBodyGetForce(mBody);
        mForce = RVector(p.x, p.y);
    }

    return mForce;
}

void RCPBody::setAngularVelocity(float v)
{
    if (mBody) {
        cpBodySetAngularVelocity(mBody, v);
    }
}

void RCPBody::setTorque(float t)
{
    if (mBody) {
        cpBodySetTorque(mBody, t);
    }
}

RVector RCPBody::position() const
{
    if (mBody) {
        cpVect p = cpBodyGetPosition(mBody);

        mPosition = RVector(p.x, p.y);
    }
    return mPosition;
}

void RCPBody::setPosition(RVector const & pos)
{
    mPosition = pos;
    if (mType != Static && mBody) {
        cpBodySetPosition(mBody, cpv(mPosition.x(), mPosition.y()));
    }
}

float RCPBody::angle() const
{
    if (mType != Static && mBody) {
        mAngle = radToDeg(cpBodyGetAngle(mBody));
    }

    return mAngle;
}

void RCPBody::setAngle(float a)
{
    mAngle = a;
    if (mBody) {
        cpBodySetAngle(mBody, degToRad(mAngle));
    }
}

void RCPBody::setMoment(float m)
{
    mMoment = m;
    if (mType != Static && mBody) {
        cpBodySetMoment(mBody, m);
    }
}

RTransformation RCPBody::transformation() const
{
    RTransformation trans;

    if (mBody) {
        cpVect pos = cpBodyGetPosition(mBody);
        cpVect rot = cpBodyGetRotation(mBody);

        float matrix[16] = {
           rot.x, rot.y, 0.0f, 0.0f,
          -rot.y, rot.x, 0.0f, 0.0f,
           0.0f,   0.0f, 1.0f, 0.0f,
           pos.x, pos.y, 0.0f, 1.0f};

        trans = RMatrix(matrix);
    }

    return trans;
}

void RCPBody::setUserData(cpDataPointer data)
{
    mUserData = data;
    if (mBody) {
        cpBodySetUserData(mBody, mUserData);
    }
}

void RCPBody::applyImpulse(RVector const & impulse)
{
    if (mBody) {
        cpBodyApplyImpulseAtWorldPoint(mBody, cpv(impulse.x(), impulse.y()), cpBodyLocalToWorld(mBody, cpBodyGetCenterOfGravity(mBody)));
    }

}

}
