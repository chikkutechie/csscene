
#include "rparticles.h"
#include "rlog.h"

#include <limits>
#include <cstdlib>

namespace chikkooos
{

void RParticles::create()
{
    if (!mExpired && count() < mCount) {
        unsigned int randCount = getRandom((int)count(), (int)mCount+1);
        for (unsigned int i=count(); i<randCount; ++i) {
            add();
        }
    }
}

float RParticles::getRandom(float min, float max) const
{
    float randNum = (float)rand () / (float)RAND_MAX;
    return min + (max - min) * randNum;
}

int RParticles::getRandom(int min, int max) const
{
    return rand() % (max-min)+min; 
}

}

