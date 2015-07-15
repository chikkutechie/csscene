
#ifndef RLOG_H
#define RLOG_H

#include "rcommon.h"
#include "rvector.h"
#include "rmatrix.h"
#include "rsmartpointer.h"
#include "routdevice.h"
#include "rtransformation.h"

#include <iostream>
#include <sstream>

namespace chikkooos
{

class RLogBase
{
public:
    enum Type
    {
        Error,
        Warning,
        Info
    };

public:
    RLogBase()
     : mType(Info)
    {}

    void setType(Type t)
    {
        mType = t;
    }

    Type type() const
    {
        return mType;
    }

    const char * tag() const
    {
        return PACKAGE;
    }

    const char * typeString() const
    {
        switch (type()) {
            case Error:
                return "Error";
            case Warning:
                return "Warning";
            case Info:
                return "Info";
        }
        return "";
    }

protected:
    Type mType;
};

class RLog: public RLogBase
{
public:
    static RLog & instance(Type t = Info, const char * filename = 0, unsigned int lineno = 0);

public:
    RLog();
    RLog(ROutDevice * device);

    // ownership transfered
    void setOutDevice(ROutDevice * device)
    {
        mOut = device;
        mOut->setLogger(this);
    }

    RLog& operator<<(std::string const &v)
    {
        mBuffer << v;
        return *this;
    }

    RLog& operator<<(std::ostream& (*pf)(std::ostream&))
    {
        if (mBuffer.str().length() > 0) {
            mOut->write(mBuffer.str());
            mBuffer.str("");
        }
        mOut->write(pf);
        return *this;
    }

    RLog& operator<<(const char *v)
    {
        mBuffer << v;
        return *this;
    }

    RLog& operator<<(long v)
    {
        mBuffer << v;
        return *this;
    }

    RLog& operator<<(unsigned long v)
    {
        mBuffer << v;
        return *this;
    }

    RLog& operator<<(int v)
    {
        mBuffer << v;
        return *this;
    }

    RLog& operator<<(unsigned int v)
    {
        mBuffer << v;
        return *this;
    }

    RLog& operator<<(char v)
    {
        mBuffer << v;
        return *this;
    }

    RLog& operator<<(unsigned char v)
    {
        mBuffer << v;
        return *this;
    }

    RLog& operator<<(float v)
    {
        mBuffer << v;
        return *this;
    }

    RLog& operator<<(double v)
    {
        mBuffer << v;
        return *this;
    }

    RLog& operator<<(RVector const & v)
    {
        (*this) << "{" << v.x() << ", " << v.y() << ", " << v.z() << ", " << v.w() << "}"; 
        return *this;
    }

    RLog& operator<<(RMatrix const & v);

    RLog& operator<<(RTransformation const & v)
    {
        (*this) << v.matrix();
        return *this;
    }

protected:
    void start(const char * filename, unsigned int lineno);

protected:
    RSmartPointer<ROutDevice> mOut;
    Type mType;
    unsigned int mTagWidth;
    std::stringstream mBuffer;
};

class RNoLog: public RLogBase
{
public:
    static RNoLog & instance(Type t = Info, const char * filename = 0, unsigned int lineno = 0)
    {
        static RNoLog nolog;
        return nolog;
    }

public:
    RNoLog()
    {}

    // ownership transfered
    void setOutDevice(ROutDevice * device)
    {
        mOut = device;
    }

    RNoLog& operator<<(std::string const &)
    {
        return *this;
    }

    RNoLog& operator<<(std::ostream& (*)(std::ostream&))
    {
        return *this;
    }

    RNoLog& operator<<(const char *)
    {
        return *this;
    }

    RNoLog& operator<<(long)
    {
        return *this;
    }

    RNoLog& operator<<(unsigned long)
    {
        return *this;
    }

    RNoLog& operator<<(int)
    {
        return *this;
    }

    RNoLog& operator<<(unsigned int)
    {
        return *this;
    }

    RNoLog& operator<<(char)
    {
        return *this;
    }

    RNoLog& operator<<(unsigned char)
    {
        return *this;
    }

private:
    RSmartPointer<ROutDevice> mOut;
};

}

#define doLog(C, T) C::instance(T, __FILE__, __LINE__)

#if defined(RDEBUG)
#define rLogE() doLog(chikkooos::RLog, chikkooos::RLogBase::Error)
#define rLogW() doLog(chikkooos::RLog, chikkooos::RLogBase::Warning)
#define rLogI() doLog(chikkooos::RLog, chikkooos::RLogBase::Info)
#else
#define rLogE() doLog(chikkooos::RNoLog, chikkooos::RLogBase::Error)
#define rLogW() doLog(chikkooos::RNoLog, chikkooos::RLogBase::Warning)
#define rLogI() doLog(chikkooos::RNoLog, chikkooos::RLogBase::Info)
#endif

#define rLog() rLogI()

#endif

