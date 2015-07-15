
#include "rbulletworld.h"

namespace chikkooos
{

RBulletWorld * RBulletWorld::mInstance;

RBulletWorld::RBulletWorld()
 : mGravity(0.0, -9.8, 0.0),
   mWorldType(DiscreteDynamicsWorld),
   mBroadphaseType(Dbvt)
{}

RBulletWorld::~RBulletWorld()
{
    clear();
    destroy();
}

RBulletWorld * RBulletWorld::instance()
{
    return mInstance;
}

void RBulletWorld::update(float dt)
{
    advance(dt);
}

RItem * RBulletWorld::clone()
{
    return new RBulletWorld();
}

bool RBulletWorld::create()
{
    if (mWorld.isNull()) {
        btAxisSweep3* sweepBP = 0;
        switch (mBroadphaseType)
        {
            case AxisSweep3:
            {
            btVector3 worldMin(-1000,-1000,-1000);
            btVector3 worldMax(1000,1000,1000);
            sweepBP = new btAxisSweep3(worldMin, worldMax);
            sweepBP->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
            mBroadphase = sweepBP;
            rLogI() << "Broadphase : " << "AxisSweep3" << std::endl;
            }
            break;

            case Simple:
            mBroadphase = new btSimpleBroadphase();
            rLogI() << "Broadphase : " << "Simple" << std::endl;
            break;

            case MultiSap:

            case Dbvt:
            default:
            mBroadphase = new btDbvtBroadphase();
            rLogI() << "Broadphase : " << "Dbvt" << std::endl;
            break;
        }

        mCollisionConfiguration = new btDefaultCollisionConfiguration();
        mDispatcher = new btCollisionDispatcher(mCollisionConfiguration.data());
        mConstraintSolver = new btSequentialImpulseConstraintSolver();

        switch (mWorldType) {
            case DiscreteDynamicsWorld:
            mWorld = new btDiscreteDynamicsWorld(mDispatcher,
                                                 mBroadphase, mConstraintSolver,
                                                 mCollisionConfiguration);
            ((btDiscreteDynamicsWorld *)mWorld.data())->setGravity(tobtVector3(mGravity));
            ((btDiscreteDynamicsWorld *)mWorld.data())->getDispatchInfo().m_allowedCcdPenetration = 0.00001f;
            break;

            default:
            break;
        }

        if (sweepBP) {
            sweepBP->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
        }

    }

    return true;
}

void RBulletWorld::destroy()
{
    if (!mWorld.isNull()) {
        mWorld = 0;
        mConstraintSolver = 0;
        mCollisionConfiguration = 0;
        mDispatcher = 0;
        mBroadphase = 0;

        rLogI() << "bulletworld distroyed" << std::endl;
    }
}

void RBulletWorld::add(btCollisionObject *body, ObjectType type)
{
    if (!mWorld.isNull() && body) {
        switch (mWorldType) {
            case DiscreteDynamicsWorld:
            add((btDiscreteDynamicsWorld *)mWorld.data(), body, type);
            break;

            default:
            break;
        }
    }
}

void RBulletWorld::addAction(btActionInterface* action)
{
    if (!mWorld.isNull() && action) {
        switch (mWorldType) {
            case DynamicsWorld:
            case DiscreteDynamicsWorld:
            case SoftRigidDynamicsWorld:
            ((btDynamicsWorld *)mWorld.data())->addAction(action);
            break;

            default:
            break;
        }
    }
}

void RBulletWorld::removeAction(btActionInterface* action)
{
    if (!mWorld.isNull() && action) {
        switch (mWorldType) {
            case DynamicsWorld:
            case DiscreteDynamicsWorld:
            case SoftRigidDynamicsWorld:

            ((btDynamicsWorld *)mWorld.data())->removeAction(action);
            break;

            default:
            break;
        }
    }
}

void RBulletWorld::add(btCollisionWorld * world, btCollisionObject *body, ObjectType type)
{
    switch (type) {
        case Rigid:
        rLogI() << "rigid object " << std::endl;
        break;

        case Collision:
        rLogI() << "collision object " << std::endl;
        world->addCollisionObject(body);
        break;

        case Soft:
        rLogI() << "soft object " << std::endl;
        break;

        default:
        rLogI() << "unknown object " << std::endl;
        world->addCollisionObject(body);
        break;
    }
}

void RBulletWorld::add(btDynamicsWorld * world, btCollisionObject *body, ObjectType type)
{
    switch (type) {
        case Rigid:
        rLogI() << "rigid object " << std::endl;
        world->addRigidBody((btRigidBody *)body);
        break;

        case Collision:
        rLogI() << "collision object " << std::endl;
        world->addCollisionObject(body);
        break;

        case Soft:
        rLogI() << "soft object " << std::endl;
        break;

        default:
        rLogI() << "unknown object " << std::endl;
        world->addRigidBody((btRigidBody *)body);
        break;
    }
}

void RBulletWorld::add(btDiscreteDynamicsWorld * world, btCollisionObject *body, ObjectType type)
{
    switch (type) {
        case Rigid:
        world->addRigidBody((btRigidBody *)body);
        break;

        case Collision:
        world->addCollisionObject(body);
        break;

        case Soft:
        break;

        default:
        world->addRigidBody((btRigidBody *)body);
        break;
    }
}

void RBulletWorld::add(btSoftRigidDynamicsWorld * world, btCollisionObject *body, ObjectType type)
{
    switch (type) {
        case Rigid:
        rLogI() << "rigid object " << std::endl;
        world->addRigidBody((btRigidBody *)body);
        break;

        case Collision:
        rLogI() << "collision object " << std::endl;
        world->addCollisionObject(body);
        break;

        case Soft:
        rLogI() << "soft object " << std::endl;
        world->addSoftBody((btSoftBody *)body);
        break;

        default:
        rLogI() << "unknown object " << std::endl;
        world->addRigidBody((btRigidBody *)body);
        break;
    }
}

void RBulletWorld::remove(btCollisionObject *body, ObjectType type)
{
    if (!mWorld.isNull() && body) {
        switch (mWorldType) {
            case DiscreteDynamicsWorld:
            remove((btDiscreteDynamicsWorld *)mWorld.data(), body, type);
            break;

            default:
            break;
        }
    }
}

void RBulletWorld::remove(btCollisionWorld * world, btCollisionObject *body, ObjectType type)
{
    switch (type)
    {
        case Rigid:
        break;

        case Collision:
        world->removeCollisionObject(body);
        break;

        case Soft:
        break;

        default:
        world->removeCollisionObject(body);
        break;
    }
}

void RBulletWorld::remove(btDynamicsWorld * world, btCollisionObject *body, ObjectType type)
{
    switch (type)
    {
        case Rigid:
        world->removeRigidBody((btRigidBody *)body);
        break;

        case Collision:
        world->removeCollisionObject(body);
        break;

        case Soft:
        break;

        default:
        world->removeRigidBody((btRigidBody *)body);
        break;
    }
}

void RBulletWorld::remove(btDiscreteDynamicsWorld * world, btCollisionObject *body, ObjectType type)
{
    switch (type)
    {
        case Rigid:
        world->removeRigidBody((btRigidBody *)body);
        break;

        case Collision:
        world->removeCollisionObject(body);
        break;

        case Soft:
        break;

        default:
        world->removeRigidBody((btRigidBody *)body);
        break;
    }
}

void RBulletWorld::remove(btSoftRigidDynamicsWorld * world, btCollisionObject *body, ObjectType type)
{
    switch (type)
    {
        case Rigid:
        world->removeRigidBody((btRigidBody *)body);
        break;

        case Collision:
        world->removeCollisionObject(body);
        break;

        case Soft:
        world->removeSoftBody((btSoftBody *)body);
        break;

        default:
        world->removeRigidBody((btRigidBody *)body);
        break;
    }
}

void RBulletWorld::advance(float t, float step, float fixedTimeStep)
{
    if (!mWorld.isNull()) {
        switch (mWorldType) {
            case DiscreteDynamicsWorld:
            ((btDiscreteDynamicsWorld *)mWorld.data())->stepSimulation(t, step, fixedTimeStep);
            break;

            default:
            break;
        }
    }
}

void RBulletWorld::setProperties(RPropertyMap const & map, std::string const & name)
{
    destroy();

    if (name.compare("bulletworld") == 0) {
        std::string world = map.getString("world", std::string());
        if (world.compare("collision") == 0) {
            mWorldType = CollisionWorld;
        } else if (world.compare("dynamics") == 0) {
            mWorldType = DynamicsWorld;
        } else if (world.compare("discretedynamics") == 0) {
            mWorldType = DiscreteDynamicsWorld;
        } else if (world.compare("softrigiddynamics") == 0) {
            mWorldType = SoftRigidDynamicsWorld;
        }

        std::string bp = map.getString("broadphase", std::string());
        if (bp.compare("dbvt") == 0) {
            mBroadphaseType = Dbvt;
        } else if (bp.compare("axissweep3") == 0) {
            mBroadphaseType = AxisSweep3;
        } else if (bp.compare("simple") == 0) {
            mBroadphaseType = Simple;
        }

        setGravity(map.getVector("gravity", gravity()));

        create();

        RBulletWorld::mInstance = this;
    }
}

}

