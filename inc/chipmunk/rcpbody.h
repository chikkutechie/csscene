
#ifndef RCPBODY_H
#define RCPBODY_H

#include "rtransformation.h"
#include "rcpshape.h"

#include <chipmunk/chipmunk.h>
#include <vector>

namespace chikkooos
{

class RCPBody
{
public:
    enum Type
    {
        Static,
        Dynamic
    };

public:
    RCPBody();
    ~RCPBody();

    void setMoment(float m);

    float moment() const
    {
        return mMoment;
    }

    RVector position() const;
    void setPosition(RVector const & pos);
    float angle() const;
    void setAngle(float a);

    RTransformation transformation() const;

    cpBody * body()
    {
        return mBody;
    }

    const cpBody * body() const
    {
        return mBody;
    }

    void setType(Type t)
    {
        mType = t;
    }

    Type type() const
    {
        return mType;
    }

    void create();
    void destroy();

    void setMass(float d)
    {
        mMass = d;
    }

    float mass() const
    {
        return mMass;
    }

    void setVelocity(RVector const & v);
    RVector velocity() const;

    void setForce(RVector const & f);
    RVector force() const;

    void setAngularVelocity(float v);
    void setTorque(float t);

    void applyImpulse(RVector const & impulse);

    void addShape(RSmartPointer<RCPShape> const & s)
    {
        mShapes.push_back(s);
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

protected:
    typedef std::vector<RSmartPointer<RCPShape> > CPShapes;
    typedef CPShapes::iterator CPShapesIter;
    typedef CPShapes::const_iterator CPShapesConstIter;

    CPShapes mShapes;

    cpBody  * mBody;
    cpDataPointer mUserData;

    Type mType;
    mutable RVector mPosition;

    mutable float mAngle;

    float mMass;
    float mMoment;

    mutable RVector mVelocity;
    mutable RVector mForce;
};

}

#endif
