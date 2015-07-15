
#ifndef RPHYSICSITEM_H
#define RPHYSICSITEM_H

#include "ritem.h"
#include "rphysicsobject.h"
namespace chikkooos
{

class RPhysicsItem: public RItem
{
public:
    enum Type
    {
        Static,
        Dynamic
    };

public:
    RPhysicsItem(Type t);

    virtual ~RPhysicsItem();

    virtual bool create();
    virtual void destroy();

    RVector position() const
	{
		return mObject.position();
	}
	
    virtual void setPosition(RVector const & pos)
	{
		mObject.setPosition(pos);
	}

    virtual void updateBoundingInfo()
	{}

    virtual RTransformation transformation() const
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

    virtual void contactTest(btCollisionWorld::ContactResultCallback& resultCallback)
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
	
    Type type() const
    {
        return mType;
    }
	
    RItem * clone();
    void draw(RGc & gc) const;
    void setProperties(RPropertyMap const & map, std::string const & element);
	
protected:
    Type mType;
    RPhysicsObject mObject;
};

}

#endif

