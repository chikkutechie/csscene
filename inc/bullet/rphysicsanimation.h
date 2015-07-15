
#ifndef RPHYSICSANIMATION_H
#define RPHYSICSANIMATION_H

#include "ranimation.h"
#include "rphysicsobject.h"

#include <vector>

namespace chikkooos
{

class RPhysicsAnimation: public RAnimation
{
public:
    typedef std::vector<float> IntervalVec;
    typedef IntervalVec::iterator IntervalVecIter;
    typedef IntervalVec::const_iterator IntervalVecConstIter;

    typedef std::vector<RVector> VectorArray;
    typedef VectorArray::iterator VectorArrayIter;
    typedef VectorArray::const_iterator VectorArrayConstIter;

public:
	RPhysicsAnimation()
     : mIndex(0)
	{}

    void setIntervals(IntervalVec const & intervals)
    {
        mIntervals = intervals;
    }
    
    void setImpulses(VectorArray const & impulses)
    {
        mImpulses = impulses;
    }

    void setPositions(VectorArray const & positions)
    {
        mPositions = positions;
    }

    bool create();
    void destroy();

    RVector position() const
	{
		return mObject.position();
	}
	
    void setPosition(RVector const & pos)
	{
		mObject.setPosition(pos);
	}

    RTransformation transformation() const
	{
		return mObject.transformation();
	}

    btRigidBody * rigidBody()
    {
        return mObject.rigidBody();
    }

    bool isNull() const
    {
        return mObject.isNull();
    }

    RGeometry const & geometry() const
    {
        return mObject.geometry();
    }

    RGeometry & geometry()
    {
        return mObject.geometry();
    }

    float friction() const
    {
        return mObject.friction();
    }
    void setFriction(float v)
    {
        mObject.setFriction(v);
    }

    float restitution() const
    {
        return mObject.restitution();
    }
    void setRestitution(float v)
    {
        mObject.setRestitution(v);
    }
    
    void applyImpulse(RVector const & impulse)
	{
		mObject.applyImpulse(impulse);
	}

    void setAngularDamping(float ad)
	{
		mObject.setAngularDamping(ad);
	}

    float angularDamping() const
    {
        return mObject.angularDamping();
    }

    void setMass(float mass)
	{
		mObject.setMass(mass);
	}

    float mass() const
    {
        return mObject.mass();
    }

    void setInertiaTensor(RVector const & v)
	{
		mObject.setInertiaTensor(v);
	}

    void contactTest(btCollisionWorld::ContactResultCallback& resultCallback)
    {
		mObject.contactTest(resultCallback);
    }

    void setGravity(RVector const & g)
    {
		mObject.setGravity(g);
    }

    RVector gravity() const
    {
        return mObject.gravity();
    }

	RPhysicsObject & object()
	{
		return mObject;
	}
	
	const RPhysicsObject & object() const
	{
		return mObject;
	}
	
protected:
    void doReverse();

	void update( float elapsed);

protected:
    IntervalVec mIntervals;
    VectorArray mImpulses;
    VectorArray mPositions;
    unsigned int mIndex;
	RPhysicsObject mObject;
};

}

#endif

