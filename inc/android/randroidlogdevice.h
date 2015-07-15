
#ifndef RANDROIDLOGDEVICE_H
#define RANDROIDLOGDEVICE_H

#include "routdevice.h"

#include <android/log.h>
#include <iostream>

namespace chikkooos
{

class RAndroidLogDevice: public ROutDevice
{
public:
    RAndroidLogDevice();

    int getPriority() const;

    virtual void write(std::string const &v) const
    {
        write(v.c_str());
    }

    virtual void write(const char *v) const
    {
        __android_log_print(getPriority(), mTag.c_str(), "%s", v);
    }

    virtual void write(char v) const
    {
        __android_log_print(getPriority(), mTag.c_str(), "%c", v);
    }

    virtual void write(int v) const
    {
        __android_log_print(getPriority(), mTag.c_str(), "%d", v);
    }

    virtual void write(unsigned int v) const
    {
        __android_log_print(getPriority(), mTag.c_str(), "%d", v);
    }

    virtual void write(float v) const
    {
        __android_log_print(getPriority(), mTag.c_str(), "%f", v);
    }

    virtual void write(double v) const
    {
        __android_log_print(getPriority(), mTag.c_str(), "%f", v);
    }

    virtual void write(long v) const
    {
        __android_log_print(getPriority(), mTag.c_str(), "%ld", v);
    }

    virtual void write(unsigned long v) const
    {
        __android_log_print(getPriority(), mTag.c_str(), "%ld", v);
    }

    void write(std::ostream& (*pf)(std::ostream&)) const
    {}

private:
    std::string mTag;
};

}

#endif

