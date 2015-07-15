
#include "rphysicsanimation.h"
#include "rlog.h"

namespace chikkooos
{

bool RPhysicsAnimation::create()
{
    if (mObject.isNull()) {
	    return mObject.create();
    }
    return true;
}

void RPhysicsAnimation::destroy()
{
    if (!mObject.isNull()) {
	    mObject.destroy();
    }
}
	
void RPhysicsAnimation::doReverse()
{
}

void RPhysicsAnimation::update(float elapsed)
{
    if (elapsed == 0.0f) {
        create();
    }

    if (mIntervals.empty() ||
        mIntervals.size() != mImpulses.size()) {
        return;
    }

    if (elapsed == 0.0f) {
        mIndex = 0;
        setPosition(position());
    }
    
    if (mIndex < mIntervals.size()) {
        float interval = mIntervals[mIndex];
        if (interval <= elapsed) {
            mObject.applyImpulse(mImpulses[mIndex]);
            ++mIndex;
        }
    }
}

}

