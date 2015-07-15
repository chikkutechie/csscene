
#ifndef RB2WORLD_H
#define RB2WORLD_H

#include "rcommon.h"
#include "ritem.h"
#include "rvector.h"
#include "rpropertymap.h"
#include "rlog.h"
#include "rsmartpointer.h"

#include "Box2D/Dynamics/b2World.h"

namespace chikkooos
{

class RB2DWorld: public RItem
{
public:
    enum ObjectType
    {
        Dynamic,
        Static
    };

public:
    static RB2DWorld * instance();

    RB2DWorld();
    ~RB2DWorld();

    bool create();

    void destroy();

    RVector gravity() const
    {
        return mGravity;
    }

    void setGravity(RVector const & g)
    {
        mGravity = g;

        if (!mWorld.isNull()) {
            mWorld->SetGravity(b2Vec2(mGravity.x(), mGravity.y()));
        }
    }

    void update(float dt);
    RItem * clone();
    void setProperties(RPropertyMap const & attributes, std::string const & name);

    void advance(float timeStep, float velocityIterations, float positionIterations);

    b2World * world()
    {
        return mWorld.data();
    }

protected:
    RB2DWorld(RB2DWorld const &);
    RB2DWorld& operator=(RB2DWorld const &);

protected:
    RVector mGravity;
    RSmartPointer<b2World> mWorld;
    float mStep;
    float mVelIterations;
    float mPosIterations;


private:
    static RB2DWorld * mInstance;
};

}

#endif

