
#ifndef RCPCOLLISION_H
#define RCPCOLLISION_H

#include "ritem.h"
#include "revent.h"
#include "reventmanager.h"

#include <chipmunk/chipmunk.h>

namespace chikkooos
{

class RCPCollision: public RItem
{
public:
    RCPCollision();

    RItem * clone();

    void update(float dt);

    void setProperties(RPropertyMap const & map, std::string const & element);

    void setBeginFunc(std::string const & functionName)
    {
        mBeginFunctionName = functionName;
    }

    void setPreSolveFunc(std::string const & functionName)
    {
        mPreSolveFunctionName = functionName;
    }

    void setPostSolveFunc(std::string const & functionName)
    {
        mPostSolveFunctionName = functionName;
    }

    void setSeparateFunc(std::string const & functionName)
    {
        mSeparateFunctionName = functionName;
    }

    void setBeginFunc(RCollisionEventListner * function)
    {
        mBeginFunc = function;
    }

    void setPreSolveFunc(RCollisionEventListner * function)
    {
        mPreSolveFunc = function;
    }

    void setPostSolveFunc(RCollisionEventListner * function)
    {
        mPostSolveFunc = function;
    }

    void setSeparateFunc(RCollisionEventListner * function)
    {
        mSeparateFunc = function;
    }

    void setType(int a, int b)
    {
        mTypeA = a;
        mTypeB = b;
    }

    void create();

private:

    static cpBool beginFunc(cpArbiter *arb, cpSpace *space, cpDataPointer userData);
    static cpBool preSolveFunc(cpArbiter *arb, cpSpace *space, cpDataPointer userData);
    static void postSolveFunc(cpArbiter *arb, cpSpace *space, cpDataPointer userData);
    static void separateFunc(cpArbiter *arb, cpSpace *space, cpDataPointer userData);

private:
    bool mCreated;

    int mTypeA;
    int mTypeB;

    RCollisionEventListner * mBeginFunc;
    RCollisionEventListner * mPreSolveFunc;
    RCollisionEventListner * mPostSolveFunc;
    RCollisionEventListner * mSeparateFunc;

    std::string mBeginFunctionName;
    std::string mPreSolveFunctionName;
    std::string mPostSolveFunctionName;
    std::string mSeparateFunctionName;
};

}

#endif

