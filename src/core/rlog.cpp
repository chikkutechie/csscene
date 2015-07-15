
#include "rlog.h"

#include "rbasicoutdevice.h"

namespace chikkooos
{

RLog::RLog()
 : mOut(new RBasicOutDevice()),
   mTagWidth(50)
{
    mOut->setLogger(this);
}

RLog::RLog(ROutDevice * device)
 : mOut(device),
   mTagWidth(50)
{
    mOut->setLogger(this);
}

namespace
{
RSmartPointer<RLog> log = new RLog;
}

RLog & RLog::instance(Type t, const char * filename, unsigned int lineno)
{
    log->setType(t);
    if (filename) {
        log->start(filename, lineno);
    }
    return *log;
}

void RLog::start(const char * filename, unsigned int lineno)
{
    if (mBuffer.str().length() > 0) {
        mOut->write(mBuffer.str());
        mBuffer.str("");
    }

    std::stringstream ss;

    ss << tag() << "/" << typeString() << " (" << filename << ":" << lineno << ") ";

    std::string msg = ss.str();

    (*this) << msg;
    for (unsigned int i=msg.length(); i < mTagWidth; ++i) {
        (*this) << " ";
    }
}

}

