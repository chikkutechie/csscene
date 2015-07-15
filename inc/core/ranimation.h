
#ifndef ANIMATION_H
#define ANIMATION_H

#include "rtime.h"
#include "rvector.h"
#include "reasingcurve.h"

namespace chikkooos
{

class RAnimationListner
{
public:
    virtual ~RAnimationListner()
    {}

    virtual void started()
    {}

    virtual void stopped()
    {}

    virtual void updated()
    {}
};

class RAnimation
{
public:
    enum State {
        None,
        Running,
        Paused,
        Stopped
    };
    
public:
    RAnimation();

    virtual ~RAnimation()
    {}

    float duration() const
    {
        return mDuration;
    }

    void setDuration(float d)
    {
        mDuration = d;
    }

    float interval() const
    {
        return mInterval;
    }

    void setInterval(float i)
    {
        mInterval = i;
    }
    
    void setRepeat(bool v)
    {
    	mRepeat = v;
    }
    
    bool reverse() const
    {
        return mReverse;
    }

    void setReverse(bool r)
    {
        mReverse = r;
    }

	REasingCurve easingCurve() const
    {
        return mEC;
    }

    void setEasingCurve(REasingCurve e)
    {
        mEC = e;
    }
    
    virtual void setListner(RAnimationListner * l)
    {
    	mListner = l;
    }
    
    State state() const
    {
        return mState;
    }

    virtual void step();
    
    virtual void start();
    
    virtual void stop();
    
    virtual void restart()
    {
        stop();
        start();
    }

    virtual void reset()
    {}
    
protected:
    virtual void update(float t) = 0;
    virtual void doReverse() = 0;

    float interpolate(float s, float e, float t) const;
    RVector interpolate(RVector const & s, RVector const & e, float t) const;

protected:
	REasingCurve mEC;
	float mDuration;
	float mInterval;
	State mState;
	RAnimationListner * mListner;
	bool mRepeat;
    bool mReverse;
	RTime mStartTime;
	RTime mPreviousTime;
};

}

#endif

