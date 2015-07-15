
#include "rcommon.h"
#include "randroidlogdevice.h"
#include "rlog.h"

namespace chikkooos
{

RAndroidLogDevice::RAndroidLogDevice()
 : mTag(PACKAGE)
{}

int RAndroidLogDevice::getPriority() const
{
    if (mLogger) {
        switch (mLogger->type()) {
            case RLogBase::Error:
            return ANDROID_LOG_ERROR;

            case RLogBase::Warning:
            return ANDROID_LOG_WARN;

            case RLogBase::Info:
            return ANDROID_LOG_INFO;
        }
    }
    return ANDROID_LOG_INFO;
}

}

