
#include "rbezierparticles.h"
#include "rlog.h"

#include <cstdlib>
#include <cmath>

namespace chikkooos
{

void RBezierParticles::reset(RBezierParticles::RParticle & p)
{
    p.mPositionX = getRandom(mXStartFrom, mXStartTo);
    p.mPositionY = getRandom(mYStartFrom, mYStartTo);
    p.mPositionZ = getRandom(mZStartFrom, mZStartTo);

    p.mStartX = p.mPositionX;
    p.mStartY = p.mPositionY;
    p.mStartZ = p.mPositionZ;

    p.mEndX = getRandom(mXEndFrom, mXEndTo);
    p.mEndY = getRandom(mYEndFrom, mYEndTo);
    p.mEndZ = getRandom(mZEndFrom, mZEndTo);

    p.mControlX = getRandom(mXControlFrom, mXControlTo);
    p.mControlY = getRandom(mYControlFrom, mYControlTo);
    p.mControlZ = getRandom(mZControlFrom, mZControlTo);

    p.mStartTime.start();

    p.mDuration = getRandom(0.0f, mDuration);
}

void RBezierParticles::add()
{
    if (count() < mCount) {
        mVertices.insert(mVertices.end(), 3, 0.0f);
        mStartVertices.insert(mStartVertices.end(), 3, 0.0f);
        mEndVertices.insert(mEndVertices.end(), 3, 0.0f);
        mControlVertices.insert(mControlVertices.end(), 3, 0.0f);

        mStartTimes.push_back(RTime());

        mLifeTimes.push_back(0.0f);

        RParticle p = particle(count()-1);
        reset(p);
    }
}

void RBezierParticles::remove(int index)
{
    int ai = index * 3;
    mVertices.erase(mVertices.begin() + ai);
    mVertices.erase(mVertices.begin() + ai);
    mVertices.erase(mVertices.begin() + ai);

    mStartVertices.erase(mStartVertices.begin() + ai);
    mStartVertices.erase(mStartVertices.begin() + ai);
    mStartVertices.erase(mStartVertices.begin() + ai);

    mEndVertices.erase(mEndVertices.begin() + ai);
    mEndVertices.erase(mEndVertices.begin() + ai);
    mEndVertices.erase(mEndVertices.begin() + ai);

    mControlVertices.erase(mControlVertices.begin() + ai);
    mControlVertices.erase(mControlVertices.begin() + ai);
    mControlVertices.erase(mControlVertices.begin() + ai);

    mLifeTimes.erase(mLifeTimes.begin() + index);
    mStartTimes.erase(mStartTimes.begin() + index);
}

void RBezierParticles::update(float)
{
    if (!mExpired && count() < mCount) {
        create();
    }

    for (unsigned int i=0; i<count(); ++i) {
        RParticle p = particle(i);

        float timeDiff = (float)p.mStartTime.elapsed() / 1000.0f;

        if (timeDiff > p.mDuration) {
            if (mExpired) {
                remove(i);
                --i;
            } else {
                reset(p);
            }
            continue;
        }
        
        float t;
        if (mLifeTimeOption == RandomLifeTime) {
            t = timeDiff / mDuration;
        } else {
            t = timeDiff / p.mDuration;
        }

        float t2 = t * t;
        float omt2 = (1-t) * (1-t);
        float ttomt = 2 * t * (1-t);

        p.mPositionX = p.mStartX * omt2 + p.mControlX * ttomt + p.mEndX * t2; 
        p.mPositionY = p.mStartY * omt2 + p.mControlY * ttomt + p.mEndY * t2; 
        p.mPositionZ = p.mStartZ * omt2 + p.mControlZ * ttomt + p.mEndZ * t2; 
    }
}

void RBezierParticles::reset()
{
    mVertices.clear();
    mStartVertices.clear();
    mEndVertices.clear();
    mControlVertices.clear();
    mLifeTimes.clear();
    mStartTimes.clear();
}

}

