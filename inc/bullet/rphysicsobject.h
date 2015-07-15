
#ifndef RPHYSICSOBJECT_H
#define RPHYSICSOBJECT_H

#include "rcommon.h"
#include "rgeometry.h"
#include "rbulletworld.h"
#include "rbulletutil.h"

namespace chikkooos
{

class RRigidBody: public btRigidBody, public RPhysicsBody
{
public:
    RRigidBody(RItem * item, btRigidBody::btRigidBodyConstructionInfo const & info)
     : btRigidBody(info),
       RPhysicsBody(item)
    {}
};

class RPhysicsObject
{
public:
	RPhysicsObject();
	~RPhysicsObject();
	
    bool create();
    void destroy();

    RVector position() const;
    void setPosition(RVector const & pos);

    RTransformation transformation() const;

    btRigidBody * rigidBody()
    {
        return mRigidBody.data();
    }

    bool isNull() const
    {
        return mRigidBody.isNull();
    }

    RGeometry const & geometry() const
    {
        return mGeometry;
    }

    RGeometry & geometry()
    {
        return mGeometry;
    }

    float friction() const
    {
        return mFriction;
    }
	
    void setFriction(float v)
    {
        mFriction = v;
    }

    float restitution() const
    {
        return mRestitution;
    }
    void setRestitution(float v)
    {
        mRestitution = v;
    }

    void applyImpulse(RVector const & impulse);

    void setAngularDamping(float ad);

    float angularDamping() const
    {
        return mAngularDamping;
    }

    void setMass(float mass);

    float mass() const
    {
        return mMass;
    }

    void setInertiaTensor(RVector const & v);

    void contactTest(btCollisionWorld::ContactResultCallback& resultCallback)
    {
        if (!mRigidBody.isNull()) {
            RBulletWorld::instance()->contactTest(mRigidBody.data(), resultCallback);
        }
    }

    void setGravity(RVector const & g)
    {
        if (!isNull()) {
            mRigidBody->setGravity(tobtVector3(g));
        }
    }

    RVector gravity() const
    {
        return mGravity;
    }

    void setItem(RItem * item)
    {
        mItem = item;
        if (!isNull()) {
            mRigidBody->setItem(mItem);
        }
    }

    RItem * item()
    {
        return mItem;
    }
	
protected:
    float mFriction;
    float mRestitution;
    float mAngularDamping;
    float mMass;
    RVector mPosition;
    RSmartPointer<RRigidBody> mRigidBody;
    RSmartPointer<btMotionState> mMotionState;
    RGeometry mGeometry;
    RVector mInertiaTensor;
    RVector mGravity;
    RItem * mItem;
};

}

#endif
