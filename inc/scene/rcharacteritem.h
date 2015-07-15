
#ifndef RCHARACTERITEM_H
#define RCHARACTERITEM_H

#include "ritem.h"
#include "rcommon.h"
#include "rgeometry.h"
#include "rbulletworld.h"
#include "rbulletutil.h"

namespace chikkooos
{

class RCharacterListner
{
public:
    virtual ~RCharacterListner()
    {}

    virtual void onCollision(RItem * item)
    {}
};

class RGhostObject: public btPairCachingGhostObject, public RPhysicsBody
{
public:
    RGhostObject(RItem * item)
     : RPhysicsBody(item)
    {}
};

class RCharacterController: public btCharacterControllerInterface
{
private:
/*
    class ClosestNotMeRayResultCallback : public btCollisionWorld::ClosestRayResultCallback
    {
    private:
        btCollisionObject * mMe;
        RCharacterListner * mListner;

    public:
        ClosestNotMeRayResultCallback(btCollisionObject * me, RCharacterListner * listner)
         : btCollisionWorld::ClosestRayResultCallback(btVector3(0, 0, 0), btVector3(0, 0, 0)),
           mMe(me),
           mListner(listner)
        {}

        btScalar addSingleResult(btCollisionWorld::LocalRayResult & rayResult, bool normalInWorldSpace)
        {
            if (rayResult.m_collisionObject == mMe) {
                return 1.0;
            }

            return btCollisionWorld::ClosestRayResultCallback::addSingleResult(rayResult, normalInWorldSpace);
        }
    };
*/

    class ClosestNotMeConvexResultCallback : public btCollisionWorld::ClosestConvexResultCallback
    {
    private:
        btCollisionObject * mMe;
        const btVector3 mUp;
        btScalar mMinSlopeDot;
        RCharacterListner * mListner;

    public:
        ClosestNotMeConvexResultCallback(btCollisionObject * me, const btVector3 & up, btScalar minSlopeDot, RCharacterListner * listner)
         : btCollisionWorld::ClosestConvexResultCallback(btVector3(0, 0, 0), btVector3(0, 0, 0)),
           mMe(me),
           mUp(up),
           mMinSlopeDot(minSlopeDot),
           mListner(listner)
        {}

        btScalar addSingleResult(btCollisionWorld::LocalConvexResult & convexResult, bool normalInWorldSpace)
        {
            if (convexResult.m_hitCollisionObject == mMe) {
                return 1.0;
            }

            if (mListner) {
                const RPhysicsBody * pb = dynamic_cast<const RPhysicsBody *>(convexResult.m_hitCollisionObject);
                if (pb) {
                    mListner->onCollision(const_cast<RPhysicsBody *>(pb)->item());
                }
            }

            btVector3 hitNormalWorld;

            if (normalInWorldSpace)
                hitNormalWorld = convexResult.m_hitNormalLocal;
            else
                hitNormalWorld = convexResult.m_hitCollisionObject->getWorldTransform().getBasis() * convexResult.m_hitNormalLocal;

            btScalar dotUp = mUp.dot(hitNormalWorld);

            if (dotUp < mMinSlopeDot)
                return 1.0;

            return btCollisionWorld::ClosestConvexResultCallback::addSingleResult(convexResult, normalInWorldSpace);
        }
    };


public:
    RCharacterController(RItem * item, RGhostObject * go, btConvexShape * cs, btScalar step, btCollisionWorld * collisionWorld, int upAxis = 1);

    btPairCachingGhostObject * getGhostObject();

    void setDuckingConvexShape(btConvexShape * shape);
    bool recoverFromPenetration(btCollisionWorld * collisionWorld);
    void stepUp(btCollisionWorld * collisionWorld);
    void setRBForceImpulseBasedOnCollision();
    void updateTargetPositionBasedOnCollision(const btVector3 & hitNormal, btScalar tangentMag = 0, btScalar normalMag = 1);
    void stepForwardAndStrafe(btCollisionWorld * collisionWorld, const btVector3 & walkMove);
    void stepDown(btCollisionWorld * collisionWorld, btScalar dt);
    void setVelocityForTimeInterval(const btVector3 & velocity, btScalar timeInterval);
    void reset();
    void warp(const btVector3 & origin);
    void preStep(btCollisionWorld * collisionWorld);
    void playerStep(btCollisionWorld * collisionWorld, btScalar dt);
    void setFallSpeed(btScalar fallSpeed);
    void setJumpSpeed(btScalar jumpSpeed);
    void setMaxJumpHeight(btScalar maxJumpHeight);
    bool canJump() const;
    void jump();
    void duck();
    void stand();
    bool canStand();
    void move(bool forward, bool backward, bool left, bool right); /*, bool up, bool down*/
    void setGravity(const btScalar gravity);
    btScalar getGravity() const;
    void setMaxSlope(btScalar slopeRadians);
    btScalar getMaxSlope() const;
    bool onGround() const;
    void stopWalking();
    void setWalkDirection(const btVector3 & walkDirection);
    void setWalkDirection(const btScalar x, const btScalar y, const btScalar z);
    void setOrientation(const btQuaternion & orientation);
    btVector3 getWalkDirection() const;
    btVector3 getPosition() const;
    void updateAction(btCollisionWorld * collisionWorld, btScalar dt);
    RCharacterListner * listner()
    {
        return mListner;
    }

    void setListner(RCharacterListner * listner)
    {
        mListner = listner;
    }

    float jumpFactor() const
    {
        return mJumpFactor;
    }

    void setJumpFactor(float jf)
    {
        mJumpFactor = jf;
    }

private:
    btVector3 computeReflectionDirection(const btVector3 & direction, const btVector3 & normal);
    btVector3 parallelComponent(const btVector3 & direction, const btVector3 & normal);
    btVector3 perpindicularComponent(const btVector3 & direction, const btVector3 & normal);
    void setPlayerMode();

    void debugDraw(btIDebugDraw *)
    {}

    static btVector3 * getUpAxisDirections()
    {
        static btVector3 sUpAxisDirection[3] = {btVector3(1, 0, 0),
                                                btVector3(0, 1, 0),
                                                btVector3(0, 0, 1)};

        return sUpAxisDirection;
    }

    static btVector3 getNormalizedVector(const btVector3 & v)
    {
        btVector3 n = v.normalized();

        if (n.length() < SIMD_EPSILON)
            n.setValue(0, 0, 0);

        return n;
    }

private:
    RItem * mItem;
    btScalar mHalfHeight;
    btPairCachingGhostObject * mGhostObject;
    btConvexShape * mConvexShape;
    btConvexShape * mStandingConvexShape;
    btConvexShape * mDuckingConvexShape;
    btCollisionWorld * mCollisionWorld;
    btScalar mVerticalVelocity;
    btScalar mVerticalOffset;
    btScalar mFallSpeed;
    btScalar mJumpSpeed;
    btScalar mMaxJumpHeight;
    btScalar mMaxSlopeRadians;
    btScalar mMaxSlopeCosine;
    btScalar mGravity;

    btScalar mTurnAngle;
    btScalar mStepHeight;

    btScalar mAddedMargin;

    btVector3 mWalkDirection;
    btVector3 mNormalizedDirection;

    btVector3 mCurrentPosition;
    btScalar mCurrentStepOffset;
    btVector3 mTargetPosition;

    btManifoldArray mManifoldArray;

    bool mTouchingContact;
    btVector3 mTouchingNormal;
    bool mWasOnGround;
    bool mWasJumping;
    bool mUseGhostObjectSweepTest;
    bool mUseWalkDirection;
    btScalar mVelocityTimeInterval;
    int mUpAxis;

    btVector3 mLinearVelocity;
    btScalar mMass;
    bool mCanStand;
    RCharacterListner * mListner;
    float mJumpFactor;
};


class RCharacterItem: public RItem
{
public:
    RCharacterItem();

    virtual ~RCharacterItem();

    virtual bool create();
    virtual void destroy();

    RVector position() const;
    virtual void setPosition(RVector const & pos);

    virtual RTransformation transformation() const;

    bool isNull() const
    {
        return mCharacter.isNull();
    }

    RGeometry const & geometry() const
    {
        return mGeometry;
    }

    RGeometry & geometry()
    {
        return mGeometry;
    }

    RItem * clone();
    void draw(RGc & gc) const;
    void setProperties(RPropertyMap const & map, std::string const & element);

    void reset();

    RCharacterController * charaterController()
    {
        return mCharacter.data();
    }

    const RCharacterController * charaterController() const
    {
        return mCharacter.data();
    }

    void setFallSpeed(float fallSpeed)
    {
        mFallSpeed = fallSpeed;
        if (!isNull()) {
            return mCharacter->setFallSpeed(mFallSpeed);
        }
    }

    void setJumpSpeed(float jumpSpeed)
    {
        mJumpSpeed = jumpSpeed;
        if (!isNull()) {
            return mCharacter->setJumpSpeed(mJumpSpeed);
        }
    }

    void setMaxJumpHeight(float maxJumpHeight)
    {
        mMaxJumpHeight = maxJumpHeight;
        if (!isNull()) {
            return mCharacter->setMaxJumpHeight(mMaxJumpHeight);
        }
    }

    bool canJump() const
    {
        if (!isNull()) {
            return mCharacter->canJump();
        }
        return false;
    }

    void jump()
    {
        if (!isNull()) {
            mCharacter->jump();
        }
    }

    void duck()
    {
        if (!isNull()) {
            mCharacter->duck();
        }
    }

    void stand()
    {
        if (!isNull()) {
            mCharacter->stand();
        }
    }

    bool canStand()
    {
        if (!isNull()) {
            return mCharacter->canStand();
        }
        return false;
    }

    void move(bool forward, bool backward, bool left, bool right)
    {
        if (!isNull()) {
            mCharacter->move(forward, backward, left, right);
        }
    }


    void setWalkDirection(RVector const & t)
    {
        if (!isNull()) {
            mCharacter->setWalkDirection(tobtVector3(t));
        }
    }

    void stopWalking()
    {
        if (!isNull()) {
            mCharacter->stopWalking();
        }
    }

    void setVelocityForTimeInterval(RVector const & velocity, btScalar timeInterval)
    {
        if (!isNull()) {
            mCharacter->setVelocityForTimeInterval(tobtVector3(velocity), timeInterval);
        }
    }

    RCharacterListner * listner()
    {
        return mListner;
    }

    void setListner(RCharacterListner * l)
    {
        mListner = l;
        if (!isNull()) {
            mCharacter->setListner(mListner);
        }
    }

    float jumpFactor() const
    {
        return mJumpFactor;
    }

    void setJumpFactor(float jf)
    {
        mJumpFactor = jf;
        if (!isNull()) {
            mCharacter->setJumpFactor(mJumpFactor);
        }
    }

protected:
    float mFallSpeed;
    float mJumpSpeed;
    float mMaxJumpHeight;
    RVector mPosition;
    RSmartPointer<RGhostObject> mGhostObject;
    RSmartPointer<RCharacterController> mCharacter;
    RGeometry mGeometry;
    RCharacterListner * mListner;
    float mJumpFactor;
};

}

#endif

