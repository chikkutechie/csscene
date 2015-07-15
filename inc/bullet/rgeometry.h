
#ifndef RGEOMETRY_H
#define RGEOMETRY_H

#include "rcommon.h"
#include "rsmartpointer.h"
#include "rshape.h"
#include "rvector.h"

#include "btBulletDynamicsCommon.h"

namespace chikkooos
{

class RPhysicsItem;

class RGeometry
{
public:
    enum Type
    {
        Box,
        Sphere,
        Cylinder
    };

public:
    RGeometry()
     : mType(Box),
       mWidth(1.0f),
       mHeight(1.0f),
       mLength(1.0f),
       mRadius(1.0f)
    {}

    bool isNull() const
    {
        return mImpl.isNull();
    }

    btCollisionShape * impl()
    {
        return mImpl.data();
    }

    void setType(Type t);

    Type type() const
    {
        return mType;
    }

    void setBox(float w, float h, float l);

    void setSphere(float r);

    void setCylinder(float r, float h);

    RVector defaultInertiaTensor(float mass) const;

private:
    RSmartPointer<btCollisionShape> mImpl;
    Type mType;
    float mWidth;
    float mHeight;
    float mLength;
    float mRadius;
};

}

#endif

