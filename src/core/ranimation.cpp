
#include "ranimation.h"

namespace chikkooos
{

RAnimation::RAnimation()
 : mDuration(2.0f),
   mInterval(0.02),
   mState(None),
   mListner(0),
   mRepeat(false),
   mReverse(false)
{}

void RAnimation::step()
{
    if (mState == Running) {
        float mselap =  (float)mPreviousTime.elapsed() / 1000.0f;

        if (mselap >= interval()) {

            mPreviousTime.start();

            mselap = (float)mStartTime.elapsed()  / 1000.0f;

            update(mselap);

            if (mListner) {
                mListner->updated();
            }

            if (mselap > mDuration) {
                stop();
            }
        }
    }
}

void RAnimation::start() {
    if (mState != Running) {
        mState = Running;
        mStartTime.start();
        mPreviousTime.start();
        if (mListner) {
            mListner->started();
        }
        update(0.0f);
    }
}

void RAnimation::stop() {
    if (mState != Stopped) {
        mState = Stopped;
        if (mListner) {
            mListner->stopped();
        }
        if (mRepeat) {
            if (mReverse) {
                doReverse();
            }
            start();
        }
    }
}

float RAnimation::interpolate(float s, float e, float t) const
{
    if (t < 0.0) {
        t = 0.0;
    }
    if (t > 1.0) {
        t = 1.0;
    }
    float et = mEC.eval(t);
    return e * et - s * et + s;
}

RVector RAnimation::interpolate(RVector const & s, RVector const & e, float t) const
{
    if (t < 0.0) {
        t = 0.0;
    }
    if (t > 1.0) {
        t = 1.0;
    }
    float et = mEC.eval(t);
    return e * et - s * et + s;
}

}

