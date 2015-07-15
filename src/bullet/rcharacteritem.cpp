
#include "rcharacteritem.h"

namespace chikkooos
{

btVector3 RCharacterController::computeReflectionDirection(const btVector3 & direction, const btVector3 & normal)
{
    return direction - (btScalar(2) * direction.dot(normal)) * normal;
}

btVector3 RCharacterController::parallelComponent(const btVector3 & direction, const btVector3 & normal)
{
    btScalar magnitude = direction.dot(normal);
    return normal * magnitude;
}

btVector3 RCharacterController::perpindicularComponent(const btVector3 & direction, const btVector3 & normal)
{
    return direction - parallelComponent(direction, normal);
}

btPairCachingGhostObject * RCharacterController::getGhostObject()
{
    return mGhostObject;
}

RCharacterController::RCharacterController(RItem * item, RGhostObject *ghostObject, btConvexShape * convexShape, btScalar stepHeight,
                                                         btCollisionWorld * collisionWorld, int upAxis)
{
    mItem = item;
    mUpAxis = upAxis;
    mAddedMargin = 0.02;
    mWalkDirection.setValue(0, 0, 0);
    mUseGhostObjectSweepTest = true;
    mGhostObject = ghostObject;
    mStepHeight = stepHeight;
    mTurnAngle = 0;
    mConvexShape = mStandingConvexShape = convexShape;
    mUseWalkDirection = false;
    mVelocityTimeInterval = 0;
    mVerticalOffset = 0;
    mVerticalVelocity = 0;
    mGravity = 9.8 * 3;
    mFallSpeed = 55;
    mJumpSpeed = 10;
    mWasOnGround = false;
    mWasJumping = false;
    setMaxSlope(btRadians(45));
    mCollisionWorld = collisionWorld;
    mCanStand = true;
    mCurrentPosition.setValue(0, 0, 0);
    mMass = 20;
    mListner = 0;
    mJumpFactor = 1.0f;
}

void RCharacterController::setDuckingConvexShape(btConvexShape * shape)
{
    mDuckingConvexShape = shape;
}

void RCharacterController::reset()
{
}

bool RCharacterController::recoverFromPenetration(btCollisionWorld * collisionWorld)
{
    bool penetration = false;

    collisionWorld->getDispatcher()->dispatchAllCollisionPairs(mGhostObject->getOverlappingPairCache(), collisionWorld->getDispatchInfo(), collisionWorld->getDispatcher());

    mCurrentPosition = mGhostObject->getWorldTransform().getOrigin();
    
    //btScalar maxPen = 0;

    for (int i = 0; i < mGhostObject->getOverlappingPairCache()->getNumOverlappingPairs(); i++) {
        mManifoldArray.resize(0);

        btBroadphasePair * collisionPair = &mGhostObject->getOverlappingPairCache()->getOverlappingPairArray()[i];

        if (collisionPair->m_algorithm) {
            collisionPair->m_algorithm->getAllContactManifolds(mManifoldArray);
        }

        for (int j = 0; j < mManifoldArray.size(); j++) {

            btPersistentManifold * manifold = mManifoldArray[j];
            btScalar directionSign = manifold->getBody0() == mGhostObject ? btScalar(-1) : btScalar(1);
        
            for (int p = 0; p < manifold->getNumContacts(); p++) {
                const btManifoldPoint & pt = manifold->getContactPoint(p);
                btScalar dist = pt.getDistance();
                if (dist < 0)
                {
                    //maxPen = dist;
                    mTouchingNormal = pt.m_normalWorldOnB * directionSign;
                    penetration = true;
                }

                mCurrentPosition += pt.m_normalWorldOnB * directionSign * dist * btScalar(0.2);
            }
        }

    }
   
    btTransform newTrans = mGhostObject->getWorldTransform();
    newTrans.setOrigin(mCurrentPosition);
    mGhostObject->setWorldTransform(newTrans);

    return penetration;
}

void RCharacterController::setRBForceImpulseBasedOnCollision()
{
    if (!mWalkDirection.isZero())
    {

        for (int i = 0; i < mGhostObject->getOverlappingPairCache()->getNumOverlappingPairs(); i++)
        {
            btBroadphasePair * collisionPair = &mGhostObject->getOverlappingPairCache()->getOverlappingPairArray()[i];

            btRigidBody * rb = (btRigidBody*)collisionPair->m_pProxy1->m_clientObject;

            if (rb && (mMass > rb->getInvMass()))
            {
                btScalar resultMass = mMass - rb->getInvMass();
                btVector3 reflection = computeReflectionDirection(mWalkDirection * resultMass, getNormalizedVector(mWalkDirection));
                rb->applyCentralImpulse(reflection * -1);
            }
        }

    }
}

void RCharacterController::stepUp(btCollisionWorld * collisionWorld)
{
    btTransform start, end;
    mTargetPosition = mCurrentPosition + getUpAxisDirections()[mUpAxis] * (mStepHeight + (mVerticalOffset > 0 ? mVerticalOffset : 0));

    start.setIdentity();
    end.setIdentity();

    start.setOrigin(mCurrentPosition);
    end.setOrigin(mTargetPosition);

    ClosestNotMeConvexResultCallback callback(mGhostObject, getUpAxisDirections()[mUpAxis], btScalar(0.7071), mListner);
    callback.m_collisionFilterGroup = getGhostObject()->getBroadphaseHandle()->m_collisionFilterGroup;
    callback.m_collisionFilterMask = getGhostObject()->getBroadphaseHandle()->m_collisionFilterMask;

    if (mUseGhostObjectSweepTest) {
        mGhostObject->convexSweepTest(mConvexShape, start, end, callback, collisionWorld->getDispatchInfo().m_allowedCcdPenetration);
    } else {
        collisionWorld->convexSweepTest(mConvexShape, start, end, callback);
    }

    if (callback.hasHit())
    {
        if (callback.m_hitNormalWorld.dot(getUpAxisDirections()[mUpAxis]) > 0)
        {
            mCurrentStepOffset = mStepHeight * callback.m_closestHitFraction;
            mCurrentPosition.setInterpolate3(mCurrentPosition, mTargetPosition, callback.m_closestHitFraction);
        }

        mVerticalOffset = mVerticalVelocity = 0;
    }
    else
    {
        mCurrentStepOffset = mStepHeight;
        mCurrentPosition = mTargetPosition;
    }
}

void RCharacterController::updateTargetPositionBasedOnCollision(const btVector3 & hitNormal, btScalar tangentMag, btScalar normalMag)
{
    btVector3 movementDirection = mTargetPosition - mCurrentPosition;
    btScalar movementLenght = movementDirection.length();

    if (movementLenght > SIMD_EPSILON)
    {
        movementDirection.normalize();

        btVector3 reflectDir = computeReflectionDirection(movementDirection, hitNormal);

        btVector3 parallelDir, perpindicularDir;

        parallelDir = parallelComponent(reflectDir, hitNormal);
        perpindicularDir = perpindicularComponent(reflectDir, hitNormal);

        mTargetPosition = mCurrentPosition;

        if (normalMag != 0)
        {
            btVector3 perpComponent = perpindicularDir * btScalar(normalMag * movementLenght);
            mTargetPosition += perpComponent;
        }
    }
}


void RCharacterController::stepForwardAndStrafe(btCollisionWorld * collisionWorld, const btVector3 & walkMove)
{
    btTransform start, end;
    mTargetPosition = mCurrentPosition + walkMove;

    start.setIdentity();
    end.setIdentity();

    btScalar fraction = 1.0;
    btScalar distance2 = (mCurrentPosition - mTargetPosition).length2();

    if (mTouchingContact)
    {
        if (mNormalizedDirection.dot(mTouchingNormal) > 0)
            updateTargetPositionBasedOnCollision(mTouchingNormal);
    }

    int maxIter = 10;

    while (fraction > 0.01 && maxIter-- > 0)
    {
        start.setOrigin(mCurrentPosition);
        end.setOrigin(mTargetPosition);

        btVector3 sweepDirNegative(mCurrentPosition - mTargetPosition);

        ClosestNotMeConvexResultCallback callback(mGhostObject, sweepDirNegative, 0, mListner);
        callback.m_collisionFilterGroup = getGhostObject()->getBroadphaseHandle()->m_collisionFilterGroup;
        callback.m_collisionFilterMask = getGhostObject()->getBroadphaseHandle()->m_collisionFilterMask;

        btScalar margin = mConvexShape->getMargin();
        mConvexShape->setMargin(margin + mAddedMargin);

        if (mUseGhostObjectSweepTest)
            mGhostObject->convexSweepTest(mConvexShape, start, end, callback, collisionWorld->getDispatchInfo().m_allowedCcdPenetration);
        else
            collisionWorld->convexSweepTest(mConvexShape, start, end, callback, collisionWorld->getDispatchInfo().m_allowedCcdPenetration);

        mConvexShape->setMargin(margin);

        fraction -= callback.m_closestHitFraction;

        if (callback.hasHit())
        {
            //btScalar hitDistance = (callback.m_hitPointWorld - mCurrentPosition).length();

            updateTargetPositionBasedOnCollision(callback.m_hitNormalWorld);
            btVector3 currentDir = mTargetPosition - mCurrentPosition;
            distance2 = currentDir.length2();

            if (distance2 > SIMD_EPSILON)
            {
                currentDir.normalize();

                if (currentDir.dot(mNormalizedDirection) <= 0)
                    break;
            }
            else
                break;
        }
        else
            mCurrentPosition = mTargetPosition;
    }
}

void RCharacterController::stepDown(btCollisionWorld * collisionWorld, btScalar dt)
{
    btTransform start, end;

    btScalar downVelocity = (mVerticalVelocity < 0 ? -mVerticalVelocity : 0) * dt;

    if (downVelocity > 0 && downVelocity < mStepHeight && (mWasOnGround || !mWasJumping))
        downVelocity = mStepHeight;

    btVector3 stepDrop = getUpAxisDirections()[mUpAxis] * (mCurrentStepOffset + downVelocity);
    mTargetPosition -= stepDrop;

    start.setIdentity();
    end.setIdentity();

    start.setOrigin(mCurrentPosition);
    end.setOrigin(mTargetPosition);

    ClosestNotMeConvexResultCallback callback(mGhostObject, getUpAxisDirections()[mUpAxis], mMaxSlopeCosine, mListner);
    callback.m_collisionFilterGroup = getGhostObject()->getBroadphaseHandle()->m_collisionFilterGroup;
    callback.m_collisionFilterMask = getGhostObject()->getBroadphaseHandle()->m_collisionFilterMask;

    if (mUseGhostObjectSweepTest)
        mGhostObject->convexSweepTest(mConvexShape, start, end, callback, collisionWorld->getDispatchInfo().m_allowedCcdPenetration);
    else
        collisionWorld->convexSweepTest(mConvexShape, start, end, callback, collisionWorld->getDispatchInfo().m_allowedCcdPenetration);

    if (callback.hasHit())
    {
        mCurrentPosition.setInterpolate3(mCurrentPosition, mTargetPosition, callback.m_closestHitFraction);
        mVerticalOffset = mVerticalVelocity = 0;
        mWasJumping = false;
    }
    else
        mCurrentPosition = mTargetPosition;
}

void RCharacterController::setVelocityForTimeInterval(const btVector3 & velocity, btScalar timeInterval)
{
    mUseWalkDirection = false;
    mWalkDirection = velocity;
    mNormalizedDirection = getNormalizedVector(mWalkDirection);
    mVelocityTimeInterval = timeInterval;
}

void RCharacterController::warp(const btVector3 & origin)
{
    btTransform xform;
    xform.setIdentity();
    xform.setOrigin(origin);
    mGhostObject->setWorldTransform(xform);
}

void RCharacterController::preStep(btCollisionWorld * collisionWorld)
{
    int numPenetrationLoops = 0;
    mTouchingContact = false;

    while (recoverFromPenetration(collisionWorld))
    {
        numPenetrationLoops++;
        mTouchingContact = true;

        if (numPenetrationLoops > 4)
            break;
    }

    mCurrentPosition = mGhostObject->getWorldTransform().getOrigin();
    mTargetPosition = mCurrentPosition;

}

void RCharacterController::playerStep(btCollisionWorld * collisionWorld, btScalar dt)
{
    if ((!mUseWalkDirection && mVelocityTimeInterval <= 0) &&
		!mWasJumping) {
        return;
	}

    mWasOnGround = onGround();

    //setRBForceImpulseBasedOnCollision();

    mVerticalVelocity -= mGravity * dt;

    if (mVerticalVelocity > 0 && mVerticalVelocity > mJumpSpeed)
        mVerticalVelocity = mJumpSpeed;

    if (mVerticalVelocity < 0 && btFabs(mVerticalVelocity) > btFabs(mFallSpeed))
        mVerticalVelocity = -btFabs(mFallSpeed);

    mVerticalOffset = mVerticalVelocity * dt;

    btTransform xform;
    xform = mGhostObject->getWorldTransform();

    stepUp(collisionWorld);

    if (mUseWalkDirection) {
        if (mWasOnGround) {
            stepForwardAndStrafe(collisionWorld, mWalkDirection);
        } else {
            stepForwardAndStrafe(collisionWorld, mWalkDirection * mJumpFactor);
        }
    } else {
		btVector3 move(0.0f, 0.0f, 0.0f);

	    // still have some time left for moving!
		btScalar dtMoving = (dt < mVelocityTimeInterval) ? dt : mVelocityTimeInterval;
		mVelocityTimeInterval -= dt;

		if (mVelocityTimeInterval > 0.0f) {
			// how far will we move while we are moving?
            if (mWasOnGround) {
			    move = mWalkDirection * dtMoving;
            } else {
			    move = (mWalkDirection * mJumpFactor) * dtMoving;
            }
		}
        // okay, step
        stepForwardAndStrafe(collisionWorld, move);
    }

    stepDown(collisionWorld, dt);

    xform.setOrigin(mCurrentPosition);
    mGhostObject->setWorldTransform(xform);

    if (!mCanStand) {
        stand(); // check if we can stand
    }
}

void RCharacterController::setFallSpeed(btScalar fallSpeed)
{
    mFallSpeed = fallSpeed;
}

void RCharacterController::setJumpSpeed(btScalar jumpSpeed)
{
    mJumpSpeed = jumpSpeed;
}

void RCharacterController::setMaxJumpHeight(btScalar maxJumpHeight)
{
    mMaxJumpHeight = maxJumpHeight;
}

bool RCharacterController::canJump() const
{
    return onGround();
}

void RCharacterController::jump()
{
    if (!canJump())
        return;

    mVerticalVelocity = mJumpSpeed;
    mWasJumping = true;
}

void RCharacterController::duck()
{
    mConvexShape = mDuckingConvexShape;
    mGhostObject->setCollisionShape(mDuckingConvexShape);

    btTransform xform;
    xform.setIdentity();
    xform.setOrigin(mCurrentPosition + btVector3(0, 0.1, 0));
    mGhostObject->setWorldTransform(xform);
}

void RCharacterController::stand()
{
    if (!canStand())
        return;

    mConvexShape = mStandingConvexShape;
    mGhostObject->setCollisionShape(mStandingConvexShape);
}

bool RCharacterController::canStand()
{
    btTransform start, end;

    start.setIdentity();
    end.setIdentity();

    start.setOrigin(mCurrentPosition);
    end.setOrigin(mCurrentPosition + btVector3(0,
                                                static_cast<btCapsuleShape*>(mStandingConvexShape)->getHalfHeight() * 2 - static_cast<btCapsuleShape*>(mDuckingConvexShape)->getHalfHeight() * 2,
                                                0));

    ClosestNotMeConvexResultCallback callback(mGhostObject, -getUpAxisDirections()[mUpAxis], 0, mListner);
    callback.m_collisionFilterGroup = getGhostObject()->getBroadphaseHandle()->m_collisionFilterGroup;
    callback.m_collisionFilterMask = getGhostObject()->getBroadphaseHandle()->m_collisionFilterMask;

    if (mUseGhostObjectSweepTest)
        mGhostObject->convexSweepTest(mConvexShape, start, end, callback, mCollisionWorld->getDispatchInfo().m_allowedCcdPenetration);
    else
        mCollisionWorld->convexSweepTest(mConvexShape, start, end, callback);

    if (callback.hasHit())
    {
        mCanStand = false;
        return false;
    }
    else
    {
        mCanStand = true;
        return true;
    }
}

void RCharacterController::move(bool forward, bool backward, bool left, bool right)
{
    btVector3 walkDirection(0, 0, 0);
    btVector3 frontSpeed(0, 0, .15);
    btVector3 sideSpeed(.13, 0, 0);

    if (forward)
        walkDirection += frontSpeed;

    if (backward)
        walkDirection -= frontSpeed;

    if (left)
        walkDirection -= sideSpeed;

    if (right)
        walkDirection += sideSpeed;



    mLinearVelocity = walkDirection;
}

void RCharacterController::setGravity(const btScalar gravity)
{
    mGravity = gravity;
}

btScalar RCharacterController::getGravity() const
{
    return mGravity;
}

void RCharacterController::setMaxSlope(btScalar slopeRadians)
{
    mMaxSlopeRadians = slopeRadians;
    mMaxSlopeCosine = btCos(slopeRadians);
}

btScalar RCharacterController::getMaxSlope() const
{
    return mMaxSlopeRadians;
}

bool RCharacterController::onGround() const
{
    return mVerticalVelocity == 0 && mVerticalOffset == 0;
}

void RCharacterController::stopWalking()
{
    mUseWalkDirection = false;
    mVelocityTimeInterval = 0;
}

void RCharacterController::setWalkDirection(const btVector3 & walkDirection)
{
    mUseWalkDirection = true;
    mWalkDirection = walkDirection;
    mNormalizedDirection = getNormalizedVector(mWalkDirection);
}

void RCharacterController::setWalkDirection(const btScalar x, const btScalar y, const btScalar z)
{
    mUseWalkDirection = true;
    mWalkDirection.setValue(x, y, z);
    mNormalizedDirection = getNormalizedVector(mWalkDirection);
}

btVector3 RCharacterController::getWalkDirection() const
{
    return mWalkDirection;
}

btVector3 RCharacterController::getPosition() const
{
    return mCurrentPosition;
}

void RCharacterController::setOrientation(const btQuaternion & orientation)
{
    btTransform xform;
    xform = mGhostObject->getWorldTransform();
    xform.setRotation(orientation);
    mGhostObject->setWorldTransform(xform);
}

void RCharacterController::updateAction(btCollisionWorld * collisionWorld, btScalar dt)
{
    preStep(collisionWorld);
    playerStep(collisionWorld, dt);
}

RCharacterItem::RCharacterItem()
 :  mFallSpeed(55.0f),
    mJumpSpeed(10.0f),
    mMaxJumpHeight(1.0f),
    mListner(0),
    mJumpFactor(1.0f)
{}

RCharacterItem::~RCharacterItem()
{
    destroy();
}

bool RCharacterItem::create()
{
    if (isNull()) {

        btTransform startTransform;
        startTransform.setIdentity();
        startTransform.setOrigin(tobtVector3(position()));

        mGhostObject = new RGhostObject(this);

        mGhostObject->setWorldTransform(startTransform);

        mGhostObject->setCollisionShape(mGeometry.impl());
        mGhostObject->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);

        btScalar stepHeight = btScalar(0.35);
        mCharacter = new RCharacterController(this, mGhostObject.data(), (btConvexShape *)mGeometry.impl(), stepHeight, RBulletWorld::instance()->world());

        mCharacter->setListner(listner());

        RBulletWorld::instance()->world()->addCollisionObject(mGhostObject.data(), btBroadphaseProxy::CharacterFilter,
                                                            btBroadphaseProxy::KinematicFilter|btBroadphaseProxy::StaticFilter|btBroadphaseProxy::DefaultFilter);
        RBulletWorld::instance()->addAction(mCharacter.data());

        mCharacter->setMaxJumpHeight(mMaxJumpHeight);
        mCharacter->setFallSpeed(mFallSpeed);
        mCharacter->setJumpSpeed(mJumpSpeed);
        setJumpFactor(jumpFactor());

        reset();
    }
    return true;
}

void RCharacterItem::destroy()
{
    if (!isNull()) {
        RBulletWorld::instance()->world()->removeCollisionObject(mGhostObject.data());
        RBulletWorld::instance()->removeAction(mCharacter.data());
        mCharacter = 0;
        mGhostObject = 0;
    }
}

void RCharacterItem::reset()
{
    RBulletWorld::instance()->world()->getBroadphase()->getOverlappingPairCache()->cleanProxyFromPairs(mGhostObject->getBroadphaseHandle(),
                                    RBulletWorld::instance()->world()->getDispatcher());
    mCharacter->reset();
    mCharacter->warp(tobtVector3(position()));
}

RVector RCharacterItem::position() const
{
    if (!isNull()) {
        btTransform trans = mGhostObject->getWorldTransform();
        return toRVector(trans.getOrigin());
    }
    return mPosition;
}

void RCharacterItem::setPosition(RVector const & pos)
{
    mPosition = pos;
}

RTransformation RCharacterItem::transformation() const
{
    btTransform trans = mGhostObject->getWorldTransform();
    float matrixData[4 * 4];
    trans.getOpenGLMatrix(matrixData);
    RMatrix m;
    m.load(matrixData);

    return RTransformation(m);
}


RItem * RCharacterItem::clone()
{
    RCharacterItem * item = new RCharacterItem();

    return item;
}

void RCharacterItem::draw(RGc & gc) const
{
    if (isNull()) {
        const_cast<RCharacterItem*>(this)->create();
        rLogI() << "creating a character item" << std::endl;
    }

    gc.pushTransform();
    gc.multiplyTransformation(transformation());

    RItem::draw(gc);

    gc.popTransform();
}

void RCharacterItem::setProperties(RPropertyMap const & map, std::string const & element)
{
    setPosition(map.getVector("position"));
    RGeometry & g = geometry();

    if (map.has("box")) {
        RVector v = map.getVector("box");
        g.setBox(v.x(), v.y(), v.z());
    } else if (map.has("cube")) {
        RVector v = map.getVector("cube");
        g.setBox(v.x(), v.y(), v.z());
    } else if (map.has("sphere")) {
        float v = map.getFloat("sphere");
        g.setSphere(v);
    } else if (map.has("cylinder")) {
        RVector v = map.getVector("cylinder");
        g.setCylinder(v.x(), v.y());
    }

    setMaxJumpHeight(map.getFloat("maxjumpheight", mMaxJumpHeight));
    setJumpSpeed(map.getFloat("jumpspeed", mJumpSpeed));
    setFallSpeed(map.getFloat("fallspeed", mFallSpeed));
    setJumpFactor(map.getFloat("jumpfactor", jumpFactor()));
}

}


