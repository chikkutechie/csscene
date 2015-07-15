

#include "rlinearparticles.h"
#include "rlog.h"

#include <cstdlib>
#include <cmath>

namespace chikkooos
{

void RLinearParticles::reset(RLinearParticles::RParticle & p)
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

    p.mStartTime.start();

    p.mDuration = getRandom(0.0f, mDuration);
}

void RLinearParticles::add()
{
    if (count() < mCount) {
        mVertices.insert(mVertices.end(), 3, 0.0f);
        mStartVertices.insert(mStartVertices.end(), 3, 0.0f);
        mEndVertices.insert(mEndVertices.end(), 3, 0.0f);

        mStartTimes.push_back(RTime());
        mLifeTimes.push_back(0.0f);

        RParticle p = particle(count()-1);
        reset(p);
    }
}

void RLinearParticles::remove(int index)
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

    mLifeTimes.erase(mLifeTimes.begin() + index);
    mStartTimes.erase(mStartTimes.begin() + index);
}

void RLinearParticles::update(float)
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

        p.mPositionX = p.mEndX * t + p.mStartX * (1.0f - t);
        p.mPositionY = p.mEndY * t + p.mStartY * (1.0f - t);
        p.mPositionZ = p.mEndZ * t + p.mStartZ * (1.0f - t);
    }
}

void RLinearParticles::reset()
{
    mVertices.clear();
    mStartVertices.clear();
    mEndVertices.clear();
    mLifeTimes.clear();
    mStartTimes.clear();
}

}

