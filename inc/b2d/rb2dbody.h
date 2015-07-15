
#ifndef RB2DBODY_H
#define RB2DBODY_H

#include "rtransformation.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Dynamics/b2Fixture.h"

#define PTM_RATIO 32.0f

namespace chikkooos
{

class RB2DBody
{
public:
    enum Type
    {
        Static,
        Dynamic,
        Kinematic
    };

    enum Shape
    {
        Box,
        Circle
    };

public:
    RB2DBody();
    ~RB2DBody();

    RVector position() const;
    void setPosition(RVector const & pos);
    float angle() const;
    void setAngle(float a);

    RTransformation transformation() const;

    b2Body * body()
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

    void setShape(Shape s)
    {
        mShape = s;
    }

    Shape shape() const
    {
        return mShape;
    }

    void create();
    void destroy();

    void setSize(float w, float h)
    {
        mWidth = w/PTM_RATIO;
        mHeight = h/PTM_RATIO;
    }

    void setRadius(float r)
    {
        mRadius = r/PTM_RATIO;
    }

    void setUserData(void * userData)
    {
        mFixtureDef.userData = userData;
    }

    const void * userData() const
    {
        return mFixtureDef.userData;
    }

    void * userData()
    {
        return mFixtureDef.userData;
    }

    void setFriction(float f)
    {
        mFixtureDef.friction = f;
    }

    float friction() const
    {
        return mFixtureDef.friction;
    }

    void setRestitution(float r)
    {
        mFixtureDef.restitution = r;
    }

    float restitution() const
    {
        return mFixtureDef.restitution;
    }

    void setDensity(float d)
    {
        mDensity = d;
    }

    float density() const
    {
        return mDensity;
    }

private:
    b2Body  * mBody;
    RSmartPointer<b2Shape> mBodyShape;
    b2BodyDef mBodyDef;
    b2FixtureDef mFixtureDef;

    Type mType;
    Shape mShape;

    mutable RVector mPosition;
    mutable float mAngle;
    float mWidth;
    float mHeight;
    float mRadius;
    float mDensity;
};

}

#endif
