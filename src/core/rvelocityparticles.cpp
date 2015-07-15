

#include "rvelocityparticles.h"
#include "rlog.h"

#include <cstdlib>
#include <cmath>

namespace chikkooos
{

void RVelocityParticles::reset(RVelocityParticles::RParticle & p)
{
    p.mPositionX = getRandom(mXStartFrom, mXStartTo);
    p.mPositionY = getRandom(mYStartFrom, mYStartTo);
    p.mPositionZ = getRandom(mZStartFrom, mZStartTo);

    p.mStartX = p.mPositionX;
    p.mStartY = p.mPositionY;
    p.mStartZ = p.mPositionZ;

    float xv = getRandom(mXVelocityFrom, mXVelocityTo);
    float yv = getRandom(mYVelocityFrom, mYVelocityTo);
    float zv = getRandom(mZVelocityFrom, mZVelocityTo);

    RVector v(xv, yv, zv);
    v = v * getRandom(mSpeedFrom, mSpeedTo);
    p.mVelocityX = v.x();
    p.mVelocityY = v.y();
    p.mVelocityZ = v.z();

    p.mStartTime.start();

    if (mWithAlphaTransition) {
        p.mAlpha = 1.0f;
    }

    p.mDuration = getRandom(0.0f, mDuration);
}

void RVelocityParticles::add()
{
    if (count() < mCount) {
        mVertices.insert(mVertices.end(), 3 ,0.0f);
        mVelocities.insert(mVelocities.end(), 3 ,0.0f);
        mStartVertices.insert(mStartVertices.end(), 3 ,0.0f);

        mStartTimes.insert(mStartTimes.end(), RTime());

        mLifeTimes.insert(mLifeTimes.end(), 0.0f);

        if (mWithAlphaTransition) {
            mAlphas.insert(mAlphas.end(), 1.0f);
        }

        RParticle p = particle(count()-1);
        reset(p);
    }
}

void RVelocityParticles::remove(int index)
{
    int ai = index * 3;
    mVertices.erase(mVertices.begin() + ai);
    mVertices.erase(mVertices.begin() + ai);
    mVertices.erase(mVertices.begin() + ai);
    mStartVertices.erase(mStartVertices.begin() + ai);
    mStartVertices.erase(mStartVertices.begin() + ai);
    mStartVertices.erase(mStartVertices.begin() + ai);
    mVelocities.erase(mVelocities.begin() + ai);
    mVelocities.erase(mVelocities.begin() + ai);
    mVelocities.erase(mVelocities.begin() + ai);
    mLifeTimes.erase(mLifeTimes.begin() + index);
    if (mWithAlphaTransition) {
        mAlphas.erase(mAlphas.begin() + index);
    }
    mStartTimes.erase(mStartTimes.begin() + index);
}

void RVelocityParticles::update(float)
{
    if (!mExpired && count() < mCount) {
        create();
    }

    for (unsigned int i=0; i<count(); ++i) {
        RParticle p = particle(i);

        float timeDiff = (float)p.mStartTime.elapsed() / 1000.0f;

        if (timeDiff > p.mDuration ||
            abs(p.mPositionX) > maxX()  ||
            abs(p.mPositionY) > maxY()  ||
            abs(p.mPositionZ) > maxZ()) {
            if (mExpired) {
                remove(i);
                --i;
            } else {
                reset(p);
                continue;
            }
        }

        if (mWithAlphaTransition) {
            p.mAlpha = 1.0f - (timeDiff / p.mDuration);
        }

        float t2 = timeDiff * timeDiff * 0.5f;

        p.mPositionX = p.mStartX + p.mVelocityX * timeDiff + t2 * gravity().x();
        p.mPositionY = p.mStartY + p.mVelocityY * timeDiff + t2 * gravity().y();
        p.mPositionZ = p.mStartZ + p.mVelocityZ * timeDiff + t2 * gravity().z();
    }
}

void RVelocityParticles::reset()
{
    mVertices.clear();
    mStartVertices.clear();
    mVelocities.clear();
    mLifeTimes.clear();
    if (mWithAlphaTransition) {
        mAlphas.clear();
    }
    mStartTimes.clear();
}

}

