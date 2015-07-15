
#ifndef RCPBODYITEM_H
#define RCPBODYITEM_H

#include "ritem.h"
#include "rcpbody.h"

namespace chikkooos
{

class RCPBodyItem: public RItem
{
public:
    RCPBodyItem();

    RItem * clone();

    void update(float dt);
    void draw(RGc & gc) const;

    void setProperties(RPropertyMap const & map, std::string const & element);

    RCPBody * body()
    {
        return mBody.data();
    }

    void setBody(RCPBody *b)
    {
        mBody = b;
    }

    void setMass(float m)
    {
        mBody->setMass(m);
    }

    void setMoment(float m)
    {
        mBody->setMoment(m);
    }

    float moment() const
    {
        return mBody->moment();
    }

    float mass()
    {
        return mBody->mass();
    }

    void setPosition(RVector const & pos)
    {
        mBody->setPosition(pos);
    }

    RVector position() const
    {
        return mBody->position();
    }

    void setAngle(float a)
    {
        mBody->setAngle(a);
    }

    float angle() const
    {
        return mBody->angle();
    }

    void setVelocity(RVector const & v)
    {
        mBody->setVelocity(v);
    }

    RVector velocity() const
    {
        return mBody->velocity();
    }

    void setForce(RVector const & f)
    {
        mBody->setForce(f);
    }

    RVector force() const
    {
        return mBody->force();
    }

    void applyImpulse(RVector const & impulse)
    {
        mBody->applyImpulse(impulse);
    }

    void setAngularVelocity(float v)
    {
        mBody->setAngularVelocity(v);
    }

    void setTorque(float t)
    {
        mBody->setTorque(t);
    }

    void create()
    {
        mBody->create();
    }

protected:
    RSmartPointer<RCPBody> mBody;
};

}

#endif
