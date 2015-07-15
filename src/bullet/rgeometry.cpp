
#include "rgeometry.h"
#include "rphysicsitem.h"
#include "rsolidsphere.h"
#include "rsolidcube.h"

#include "rbulletutil.h"

namespace chikkooos
{

void RGeometry::setBox(float w, float h, float l)
{
    mWidth = w;
    mHeight = h;
    mLength = l;
    mImpl = new btBoxShape(btVector3(w/2.0f, h/2.0f, l/2.0f));
    mType = Box;
}

void RGeometry::setSphere(float r)
{
    mRadius = r;
    mImpl = new btSphereShape(r/2.0f);
    mType = Sphere;
}

void RGeometry::setCylinder(float r, float h)
{
    mRadius = r;
    mHeight = h;
    mImpl = new btCylinderShape(btVector3(r/2.0f, h/2.0f, 1));
    mType = Cylinder;
}

RVector RGeometry::defaultInertiaTensor(float mass) const
{
    btVector3 inertia(0, 0, 0);

    if (!mImpl.isNull()) {
        mImpl->calculateLocalInertia(mass, inertia);
    }

    return toRVector(inertia);
}

void RGeometry::setType(Type t)
{
    mType = t;

    if (!mImpl.isNull()) {
        switch (mType) {
            case Box:
            setBox(mWidth, mHeight, mLength);
            break;

            case Sphere:
            setSphere(mRadius);
            break;

            case Cylinder:
            setCylinder(mRadius, mHeight);
            break;
        }
    }
}

}

