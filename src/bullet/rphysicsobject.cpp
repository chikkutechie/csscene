
#include "rphysicsitem.h"
#include "rgeometry.h"
#include "rlog.h"

namespace chikkooos
{

RPhysicsObject::RPhysicsObject()
 : mFriction(1.0f),
   mRestitution(0.0),
   mAngularDamping(0.001f),
   mMass(0.0f),
   mGravity(0.0f, -9.8f, 0.0f),
   mItem(0)
{}

RPhysicsObject::~RPhysicsObject()
{
    destroy();
}

void RPhysicsObject::setAngularDamping(float ad)
{
    mAngularDamping = ad;
}

void RPhysicsObject::setInertiaTensor(RVector const & v)
{
    mInertiaTensor = v;
}

void RPhysicsObject::applyImpulse(RVector const & impulse)
{
    if (!mRigidBody.isNull()) {
        mRigidBody->applyCentralImpulse(tobtVector3(impulse));
    }
}

RVector RPhysicsObject::position() const
{
    return mPosition;
}

void RPhysicsObject::setPosition(RVector const & pos)
{
    mPosition = pos;
/*
    if (!isNull()) {
        btTransform trans;
        mRigidBody->getMotionState()->getWorldTransform(trans);
        trans.setOrigin(tobtVector3(pos));
        mRigidBody->getMotionState()->setWorldTransform(trans);
    }
*/
}

void RPhysicsObject::setMass(float mass)
{
    mMass = mass;
}

RTransformation RPhysicsObject::transformation() const
{
    RMatrix m;

    if (!isNull()) {
        btTransform trans;
        mRigidBody->getMotionState()->getWorldTransform(trans);
        float matrixData[4 * 4];
        trans.getOpenGLMatrix(matrixData);
        m.load(matrixData);
    }

    return RTransformation(m);
}

bool RPhysicsObject::create()
{
    if (mRigidBody.isNull()) {
        btTransform trns;
        trns.setIdentity();
        trns.setOrigin(tobtVector3(mPosition));
        mMotionState = new btDefaultMotionState(trns);
        btRigidBody::btRigidBodyConstructionInfo info(mass(), mMotionState.data(), mGeometry.impl(), tobtVector3(mInertiaTensor));
        info.m_restitution = restitution();
        info.m_friction = friction();
        info.m_additionalAngularDampingFactor = angularDamping();
        mRigidBody = new RRigidBody(mItem, info);
        mRigidBody->setGravity(tobtVector3(gravity()));
        mRigidBody->setSleepingThresholds(0.0f, 0.0f);
        mRigidBody->setAngularFactor(0.0f);
        RBulletWorld::instance()->add(mRigidBody.data());
    }

    return true;
}

void RPhysicsObject::destroy()
{
    if (!mRigidBody.isNull()) {
        RBulletWorld::instance()->remove(mRigidBody.data());
        mRigidBody = 0;
        mMotionState = 0;
    }
}

}

