
#ifndef RSIMULATOR_H
#define RSIMULATOR_H

#include "rcommon.h"
#include "ritem.h"
#include "rvector.h"
#include "rpropertymap.h"
#include "rlog.h"
#include "rsmartpointer.h"
#include "rbulletutil.h"

namespace chikkooos
{

class RBulletWorld: public RItem
{
public:
    enum ObjectType
    {
        Rigid,
        Collision,
        Soft
    };

    enum WorldType
    {
        CollisionWorld,
        DynamicsWorld,
        DiscreteDynamicsWorld,
        SoftRigidDynamicsWorld
    };

    enum Broadphase
    {
        Dbvt,
        AxisSweep3,
        Simple,
        MultiSap
    };

public:
    RBulletWorld();
    ~RBulletWorld();

    static RBulletWorld * instance();

    bool create();

    void destroy();

    RVector gravity() const
    {
        return mGravity;
    }

    void setGravity(RVector const & g)
    {
        mGravity = g;
    }

    virtual void update(float dt);
    virtual RItem * clone();

    void setProperties(RPropertyMap const & attributes, std::string const & name);

    void advance(float t, float step=1, float fixedTimeStep=1.0f/60.0f);

    // bullet specific
    void add(btCollisionObject *body, ObjectType type = Rigid);
    void remove(btCollisionObject *body, ObjectType type = Rigid);

    void addAction(btActionInterface* action);
    void removeAction(btActionInterface* action);

    void contactTest(btCollisionObject* colObj, btCollisionWorld::ContactResultCallback& resultCallback)
    {
        mWorld->contactTest(colObj, resultCallback);
    }

    WorldType worldType() const
    {
        return mWorldType;
    }

    btCollisionWorld * world()
    {
        return mWorld.data();
    }

    const btCollisionWorld * world() const
    {
        return mWorld.data();
    }

protected:
    void add(btCollisionWorld * world, btCollisionObject *body, ObjectType type = Rigid);
    void add(btDynamicsWorld * world, btCollisionObject *body, ObjectType type = Rigid);
    void add(btDiscreteDynamicsWorld * world, btCollisionObject *body, ObjectType type = Rigid);
    void add(btSoftRigidDynamicsWorld * world, btCollisionObject *body, ObjectType type = Rigid);

    void remove(btCollisionWorld * world, btCollisionObject *body, ObjectType type = Rigid);
    void remove(btDynamicsWorld * world, btCollisionObject *body, ObjectType type = Rigid);
    void remove(btDiscreteDynamicsWorld * world, btCollisionObject *body, ObjectType type = Rigid);
    void remove(btSoftRigidDynamicsWorld * world, btCollisionObject *body, ObjectType type = Rigid);

protected:
    RBulletWorld(RBulletWorld const &);
    RBulletWorld& operator=(RBulletWorld const &);

protected:
    RSmartPointer<btCollisionWorld> mWorld;
    RSmartPointer<btBroadphaseInterface> mBroadphase;
    RSmartPointer<btCollisionConfiguration> mCollisionConfiguration;
    RSmartPointer<btDispatcher> mDispatcher;
    RSmartPointer<btConstraintSolver> mConstraintSolver;

    RVector mGravity;
    WorldType mWorldType;
    Broadphase mBroadphaseType;

private:
    static RBulletWorld *mInstance;
};

}

#endif

