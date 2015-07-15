
#ifndef RBASICOUTDEVICE_H
#define RBASICOUTDEVICE_H

#include "routdevice.h"

#include <iostream>

namespace chikkooos
{

class RBasicOutDevice: public ROutDevice
{
public:
    RBasicOutDevice()
     : mOut(&std::cout)
    {}

    virtual void write(std::string const &v) const
    {
        (*mOut) << v;
    }

    virtual void write(const char *v) const
    {
        (*mOut) << v;
    }

    virtual void write(char v) const
    {
        (*mOut) << v;
    }

    virtual void write(int v) const
    {
        (*mOut) << v;
    }

    virtual void write(unsigned int v) const
    {
        (*mOut) << v;
    }

    virtual void write(float v) const
    {
        (*mOut) << v;
    }

    virtual void write(double v) const
    {
        (*mOut) << v;
    }

    virtual void write(long v) const
    {
        (*mOut) << v;
    }

    virtual void write(unsigned long v) const
    {
        (*mOut) << v;
    }

    void write(std::ostream& (*pf)(std::ostream&)) const
    {
        pf(*mOut);
    }

protected:
    std::ostream * mOut;
};

}

#endif

