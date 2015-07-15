
#include "rcpworld.h"

namespace chikkooos
{

RCPWorld  * RCPWorld::mInstance = 0;

RCPWorld::RCPWorld()
 : mGravity(0, -400),
   mSpace(0),
   mStep(-1.0f),
   mVelIterations(8.0f),
   mPosIterations(6.0f)
{}

RCPWorld::RCPWorld(RCPWorld const &)
 : mGravity(0, -400),
   mSpace(0),
   mStep(-1.0f),
   mVelIterations(8.0f),
   mPosIterations(6.0f)
{}

RCPWorld& RCPWorld::operator=(RCPWorld const &)
{
    return *this;
}

RCPWorld::~RCPWorld()
{
    destroy();
    if (RCPWorld::mInstance == this) {
        RCPWorld::mInstance = 0;
    }
}

RCPWorld * RCPWorld::instance()
{
    return mInstance;
}

bool RCPWorld::create()
{
    destroy();

    mSpace = cpSpaceNew();

    cpSpaceSetGravity(mSpace, cpv(mGravity.x(), mGravity.y()));

    return true;
}

void RCPWorld::destroy()
{
    if (mSpace) {
        cpSpaceFree(mSpace);
    }

    mSpace = 0;
}

void RCPWorld::update(float dt)
{
    if (mStep < 0.0f) {
        advance(dt);
    } else {
        advance(mStep);
    }

    RItem::update(dt);
}

RItem * RCPWorld::clone()
{
    return new RCPWorld();
}

void RCPWorld::setProperties(RPropertyMap const & map, std::string const & name)
{
    destroy();

    if (name.compare("cpworld") == 0) {
        setGravity(map.getVector("gravity", gravity()));

        mStep = map.getFloat("timestep", mStep);
        mVelIterations = map.getFloat("velocityiterations", mVelIterations);
        mPosIterations = map.getFloat("positioniterations", mPosIterations);

        RCPWorld::mInstance = this;

        create();
    }
}

void RCPWorld::advance(float timeStep)
{
    if (mSpace) {
        cpSpaceStep(mSpace, timeStep);
    }
}

}
