
#ifndef RVELOCITYPARTICLES_H
#define RVELOCITYPARTICLES_H

#include "rparticles.h"

#include <limits>

namespace chikkooos
{

class RVelocityParticles: public RParticles
{
public:
    class RParticle
   {
    public:
        RParticle(float & px, float & py, float & pz, 
                  float & sx, float & sy, float & sz, 
                  float & vx, float & vy, float & vz,
                  float & duration, float & alpha, RTime & starttime)
         : mPositionX(px),
           mPositionY(py),
           mPositionZ(pz),
           mStartX(sx),
           mStartY(sy),
           mStartZ(sz),
           mVelocityX(vx),
           mVelocityY(vy),
           mVelocityZ(vz),
           mDuration(duration),
           mAlpha(alpha),
           mStartTime(starttime)
        {}

        float & mPositionX;
        float & mPositionY;
        float & mPositionZ;
        float & mStartX;
        float & mStartY;
        float & mStartZ;
        float & mVelocityX;
        float & mVelocityY;
        float & mVelocityZ;
        float & mDuration;
        float & mAlpha;
        RTime & mStartTime;
    };

public:
    RVelocityParticles(unsigned int count=50)
     : RParticles(count),
       mXVelocityFrom(0.0f),
       mYVelocityFrom(0.0f),
       mZVelocityFrom(0.0f),
       mXVelocityTo(1.0f),
       mYVelocityTo(1.0f),
       mZVelocityTo(1.0f),
       mSpeedFrom(0.0f),
       mSpeedTo(1.0f),
       mMaxX(std::numeric_limits<float>::max()),
       mMaxY(std::numeric_limits<float>::max()),
       mMaxZ(std::numeric_limits<float>::max()),
       mGravity(0.0, -10.0, 0.0),
       mWithAlphaTransition(true)
    {}

    RParticle particle(int index)
    {
        static float tmp = 1.0f;
        int ai = index * 3;
        if (mWithAlphaTransition) {
            return RParticle(mVertices[ai+0], mVertices[ai+1], mVertices[ai+2],
                         mStartVertices[ai+0], mStartVertices[ai+1], mStartVertices[ai+2],
                         mVelocities[ai+0], mVelocities[ai+1], mVelocities[ai+2],
                         mLifeTimes[index], mAlphas[index], mStartTimes[index]);
        } else {
            return RParticle(mVertices[ai+0], mVertices[ai+1], mVertices[ai+2],
                         mStartVertices[ai+0], mStartVertices[ai+1], mStartVertices[ai+2],
                         mVelocities[ai+0], mVelocities[ai+1], mVelocities[ai+2],
                         mLifeTimes[index], tmp, mStartTimes[index]);
        }
    }

    void reset();

    void update(float ms);

    unsigned int count() const
    {
        return mLifeTimes.size();
    }

    float xVelocityFrom() const
    {
        return mXVelocityFrom;
    }

    float xVelocityTo() const
    {
        return mXVelocityTo;
    }

    float yVelocityFrom() const
    {
        return mYVelocityFrom;
    }

    float yVelocityTo() const
    {
        return mYVelocityTo;
    }

    float zVelocityFrom() const
    {
        return mZVelocityFrom;
    }

    float zVelocityTo() const
    {
        return mZVelocityTo;
    }

    void setXVelocity(float from, float to)
    {
        mXVelocityFrom = from;
        mXVelocityTo = to;
    }

    void setYVelocity(float from, float to)
    {
        mYVelocityFrom = from;
        mYVelocityTo = to;
    }

    void setZVelocity(float from, float to)
    {
        mZVelocityFrom = from;
        mZVelocityTo = to;
    }

    void setSpeed(float from, float to)
    {
        mSpeedFrom = from;
        mSpeedTo = to;
    }

    float speedFrom() const
    {
        return mSpeedFrom;
    }

    float speedTo() const
    {
        return mSpeedTo;
    }

    const float * vertices() const
    {
        return &mVertices[0];
    }
    
    const float * alphas() const
    {
        if (mWithAlphaTransition) {
            return &mAlphas[0];
        }
        return 0;
    }

    float maxX() const
    {
        return mMaxX;
    }

    void setMaxX(float v)
    {
        mMaxX = v;
    }

    float maxY() const
    {
        return mMaxY;
    }

    void setMaxY(float v)
    {
        mMaxY = v;
    }

    float maxZ() const
    {
        return mMaxZ;
    }

    void setMaxZ(float v)
    {
        mMaxZ = v;
    }

    RVector gravity() const
    {
        return mGravity;
    }

    void setGravity(RVector const & g)
    {
        mGravity = g;
    }

    bool alphaTransition() const
    {
        return mWithAlphaTransition;
    }

    void setAlphaTransition(bool at)
    {
        mWithAlphaTransition = at;
    }

private:
    void remove(int index);
    void add();
    void reset(RParticle & p);

private:
    std::vector<float> mVertices;
    std::vector<float> mStartVertices;
    std::vector<float> mVelocities;
    std::vector<float> mLifeTimes;
    std::vector<float> mAlphas;
    std::vector<RTime> mStartTimes;
    float mXVelocityFrom;
    float mYVelocityFrom;
    float mZVelocityFrom;
    float mXVelocityTo;
    float mYVelocityTo;
    float mZVelocityTo;
    float mSpeedFrom;
    float mSpeedTo;
    float mMaxX;
    float mMaxY;
    float mMaxZ;
    RVector mGravity;
    bool mWithAlphaTransition;
};

}

#endif

