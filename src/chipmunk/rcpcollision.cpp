
#include "rcpcollision.h"
#include "rcpshapeitem.h"
#include "rcpworld.h"
#include "rscene.h"

namespace chikkooos
{

RCPCollision::RCPCollision()
 : mCreated(false),
   mTypeA(0),
   mTypeB(0),
   mBeginFunc(0),
   mPreSolveFunc(0),
   mPostSolveFunc(0),
   mSeparateFunc(0)
{}

cpBool RCPCollision::beginFunc(cpArbiter *arb, cpSpace *space, cpDataPointer userData)
{
    RCPCollision * collision = (RCPCollision *)userData;
    if (collision && collision->mBeginFunc) {
        CP_ARBITER_GET_SHAPES(arb, cpsA, cpsB);
        RItem * itemA = (RItem *)cpShapeGetUserData(cpsA);
        RItem * itemB = (RItem *)cpShapeGetUserData(cpsB);

        RCPShapeItem * shapeA = dynamic_cast<RCPShapeItem *>(itemA);
        RCPShapeItem * shapeB = dynamic_cast<RCPShapeItem *>(itemB);

        collision->mBeginFunc->handle(RCollisionEvent(shapeA, shapeB));
    }
    return 1;
}

cpBool RCPCollision::preSolveFunc(cpArbiter *arb, cpSpace *space, cpDataPointer userData)
{
    RCPCollision * collision = (RCPCollision *)userData;
    if (collision && collision->mPreSolveFunc) {
        CP_ARBITER_GET_SHAPES(arb, cpsA, cpsB);
        RItem * itemA = (RItem *)cpShapeGetUserData(cpsA);
        RItem * itemB = (RItem *)cpShapeGetUserData(cpsB);

        RCPShapeItem * shapeA = dynamic_cast<RCPShapeItem *>(itemA);
        RCPShapeItem * shapeB = dynamic_cast<RCPShapeItem *>(itemB);

        collision->mPreSolveFunc->handle(RCollisionEvent(shapeA, shapeB));
    }
    return 1;
}

void RCPCollision::postSolveFunc(cpArbiter *arb, cpSpace *space, cpDataPointer userData)
{
    RCPCollision * collision = (RCPCollision *)userData;
    if (collision && collision->mPostSolveFunc) {
        CP_ARBITER_GET_SHAPES(arb, cpsA, cpsB);
        RItem * itemA = (RItem *)cpShapeGetUserData(cpsA);
        RItem * itemB = (RItem *)cpShapeGetUserData(cpsB);

        RCPShapeItem * shapeA = dynamic_cast<RCPShapeItem *>(itemA);
        RCPShapeItem * shapeB = dynamic_cast<RCPShapeItem *>(itemB);

        collision->mPostSolveFunc->handle(RCollisionEvent(shapeA, shapeB));
    }
}

void RCPCollision::separateFunc(cpArbiter *arb, cpSpace *space, cpDataPointer userData)
{
    RCPCollision * collision = (RCPCollision *)userData;
    if (collision && collision->mSeparateFunc) {
        CP_ARBITER_GET_SHAPES(arb, cpsA, cpsB);
        RItem * itemA = (RItem *)cpShapeGetUserData(cpsA);
        RItem * itemB = (RItem *)cpShapeGetUserData(cpsB);

        RCPShapeItem * shapeA = dynamic_cast<RCPShapeItem *>(itemA);
        RCPShapeItem * shapeB = dynamic_cast<RCPShapeItem *>(itemB);

        collision->mSeparateFunc->handle(RCollisionEvent(shapeA, shapeB));
    }
}

RItem * RCPCollision::clone()
{
    return new RCPCollision();
}

void RCPCollision::update(float dt)
{
    if (!mCreated) {
        create();
    }
}

void RCPCollision::create()
{
    if (RCPWorld::instance()) {

        cpSpace * space = RCPWorld::instance()->space();

        cpCollisionHandler *handler = cpSpaceAddCollisionHandler(space, mTypeA, mTypeB);

        RScene * s = scene();

        if (!mBeginFunctionName.empty() && s) {
            mBeginFunc = s->getEventCollisionCallback(mBeginFunctionName);
        }
        if (mBeginFunc) {
            handler->beginFunc = beginFunc;
        }

        if (!mPreSolveFunctionName.empty() && s) {
            mPreSolveFunc = s->getEventCollisionCallback(mPreSolveFunctionName);
        }
        if (mPreSolveFunc) {
            handler->preSolveFunc = preSolveFunc;
        }

        if (!mPostSolveFunctionName.empty() && s) {
            mPostSolveFunc = s->getEventCollisionCallback(mPostSolveFunctionName);
        }
        if (mPostSolveFunc) {
            handler->postSolveFunc = postSolveFunc;
        }

        if (!mSeparateFunctionName.empty() && s) {
            mSeparateFunc = s->getEventCollisionCallback(mSeparateFunctionName);
        }
        if (mSeparateFunc) {
            handler->separateFunc = separateFunc;
        }

        handler->userData = this;
    }

    mCreated = true;
}

void RCPCollision::setProperties(RPropertyMap const & map, std::string const & element)
{
    mTypeA = map.getInt("typeA");
    mTypeB = map.getInt("typeB");

    mBeginFunctionName = map.getString("begin");
    mPreSolveFunctionName = map.getString("presolve");
    mPostSolveFunctionName = map.getString("postsolve");
    mSeparateFunctionName = map.getString("separate");
}

}
