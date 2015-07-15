
#ifndef RCPWORLD_H
#define RCPWORLD_H

#include "rcommon.h"
#include "ritem.h"
#include "rvector.h"
#include "rpropertymap.h"
#include "rlog.h"
#include "rsmartpointer.h"

#include <chipmunk/chipmunk.h>

namespace chikkooos
{

class RCPWorld: public RItem
{
public:
    static RCPWorld * instance();

public:
    RCPWorld();
    ~RCPWorld();

    bool create();

    void destroy();

    RVector gravity() const
    {
        return mGravity;
    }

    void setGravity(RVector const & g)
    {
        mGravity = g;
        if (mSpace) {
            cpSpaceSetGravity(mSpace, cpv(mGravity.x(), mGravity.y()));
        }
    }

    void update(float dt);
    RItem * clone();
    void setProperties(RPropertyMap const & attributes, std::string const & name);

    void advance(float timeStep);

    cpSpace * space()
    {
        return mSpace;
    }

protected:
    RCPWorld(RCPWorld const &);
    RCPWorld& operator=(RCPWorld const &);

protected:
    RVector mGravity;
    cpSpace * mSpace;

    float mStep;
    float mVelIterations;
    float mPosIterations;

private:
    static RCPWorld * mInstance;
};

}

#endif
