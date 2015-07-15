
#ifndef RBULLETUTILS_H
#define RBULLETUTILS_H

#include "rvector.h"

#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"
#include "BulletSoftBody/btSoftRigidDynamicsWorld.h"
#include "BulletCollision/BroadphaseCollision/btBroadphaseProxy.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "BulletDynamics/Character/btKinematicCharacterController.h"

namespace chikkooos
{

class RItem;

inline RVector toRVector(btVector3 const & btv)
{
    return RVector(btv.x(),
                   btv.y(),
                   btv.z(),
                   btv.w());

}

inline btVector3 tobtVector3(RVector const & v)
{
    return btVector3(v.x(),
                     v.y(),
                     v.z());
}

class RPhysicsBody
{
public:
    RPhysicsBody(RItem * item)
     : mItem(item)
    {}
    virtual ~RPhysicsBody()
    {}

    RItem * item()
    {
        return mItem;
    }

    const RItem * item() const
    {
        return mItem;
    }

    void setItem(RItem * item)
    {
        mItem = item;
    }
private:
    RItem * mItem;
};

}

#endif

