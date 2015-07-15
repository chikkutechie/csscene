
#ifndef RPARTICLES_H
#define RPARTICLES_H

#include "rcommon.h"
#include "rvector.h"
#include "ranimation.h"

#include <vector>

namespace chikkooos
{

class RParticles: public RAnimation, public RAnimationListner
{
public:
    RParticles(unsigned int count=50)
     : mCount(count),
       mXStartFrom(1.0f),
       mYStartFrom(1.0f),
       mZStartFrom(1.0f),
       mXStartTo(1.0f),
       mYStartTo(1.0f),
       mZStartTo(1.0f),
       mSize(1.0f),
       mExpired(false),
       mSmoothStop(true)
    {
        mListner = this;
    }

    virtual ~RParticles()
    {}

    virtual void reset() = 0;

    virtual unsigned int count() const = 0;

    virtual const float * vertices() const = 0;
    
    virtual const float * alphas() const
    {
        return 0;
    }
    
    void setMaximumParticleCount(unsigned int count)
    {
        mCount = count;
    }

    float xStartFrom() const
    {
        return mXStartFrom;
    }

    float xStartTo() const
    {
        return mXStartTo;
    }

    float yStartFrom() const
    {
        return mYStartFrom;
    }

    float yStartTo() const
    {
        return mYStartTo;
    }

    float zStartFrom() const
    {
        return mZStartFrom;
    }

    float zStartTo() const
    {
        return mZStartTo;
    }

    void setXStart(float from, float to)
    {
        mXStartFrom = from;
        mXStartTo = to;
    }

    void setYStart(float from, float to)
    {
        mYStartFrom = from;
        mYStartTo = to;
    }

    void setZStart(float from, float to)
    {
        mZStartFrom = from;
        mZStartTo = to;
    }

    float size() const
    {
        return mSize;
    }

    void setSize(float s)
    {
        mSize = s;
    }

    bool smoothStop() const
    {
        return mSmoothStop;
    }

    void setSmoothStop(bool ss)
    {
        mSmoothStop = ss;
    }

protected:
    void doReverse()
    {}
    void create();

    void setListner(RAnimationListner *)
    {}
    
    void started()
    {
        mExpired = false;
    }

    void stopped()
    {
        mExpired = true;
        if (!mSmoothStop) {
            reset();
        } else {
            if (count() > 0) {
                mState = Running;
            }
        }
    }

    virtual void add() = 0;

    float getRandom(float min, float max) const;
    int getRandom(int min, int max) const;

protected:
    unsigned int mCount;
    float mXStartFrom;
    float mYStartFrom;
    float mZStartFrom;
    float mXStartTo;
    float mYStartTo;
    float mZStartTo;
    float mSize;
    bool mExpired;
    bool mSmoothStop;
};

}

#endif

