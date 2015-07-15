
#include "rb2dworld.h"

namespace chikkooos
{

RB2DWorld * RB2DWorld::mInstance;

RB2DWorld::RB2DWorld()
 : mGravity(0, -9.8),
   mWorld(0),
   mStep(-1.0f),
   mVelIterations(8.0f),
   mPosIterations(6.0f)
{}

RB2DWorld::RB2DWorld(RB2DWorld const &)
 : mStep(-1.0f),
   mVelIterations(8.0f),
   mPosIterations(6.0f)
{}

RB2DWorld& RB2DWorld::operator=(RB2DWorld const &)
{
    return *this;
}

RB2DWorld::~RB2DWorld()
{
    destroy();
}

RB2DWorld * RB2DWorld::instance()
{
    return mInstance;
}

bool RB2DWorld::create()
{
    mWorld = new b2World(b2Vec2(mGravity.x(), mGravity.y()));

    return true;
}

void RB2DWorld::destroy()
{
    mWorld = 0;
}

void RB2DWorld::update(float dt)
{
    if (mStep < 0.0f) {
        advance(dt, mVelIterations, mPosIterations);
    } else {
        advance(mStep, mVelIterations, mPosIterations);
    }
    RItem::update(dt);
}

RItem * RB2DWorld::clone()
{
    return new RB2DWorld();
}

void RB2DWorld::setProperties(RPropertyMap const & map, std::string const & name)
{
    destroy();

    if (name.compare("b2dworld") == 0) {
        setGravity(map.getVector("gravity", gravity()));
        mStep = map.getFloat("timestep", mStep);
        mVelIterations = map.getFloat("velocityiterations", mVelIterations);
        mPosIterations = map.getFloat("positioniterations", mPosIterations);
        RB2DWorld::mInstance = this;
        create();
    }
}

void RB2DWorld::advance(float timeStep, float velocityIterations, float positionIterations)
{
    if (!mWorld.isNull()) {
        mWorld->Step(timeStep, velocityIterations, positionIterations);
    }
}

}

