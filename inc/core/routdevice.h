
#ifndef ROUTDEVICE_H
#define ROUTDEVICE_H

#include <string>

namespace chikkooos
{

class RLog;

class ROutDevice
{
public:
    ROutDevice()
     : mLogger(0)
    {}

    virtual ~ROutDevice()
    {}

    virtual void write(std::string const &v) const = 0;
    virtual void write(const char *v) const = 0;
    virtual void write(char v) const = 0;
    virtual void write(int v) const = 0;
    virtual void write(unsigned int v) const = 0;
    virtual void write(float v) const = 0;
    virtual void write(double v) const = 0;
    virtual void write(long v) const = 0;
    virtual void write(unsigned long v) const = 0;
    virtual void write(std::ostream& (*pf)(std::ostream&)) const = 0;

    void setLogger(RLog * logger)
    {
        mLogger = logger;
    }

    RLog * logger()
    {
        return mLogger;
    }

    const RLog * logger() const
    {
        return mLogger;
    }

protected:
    RLog * mLogger;
};

}

#endif

