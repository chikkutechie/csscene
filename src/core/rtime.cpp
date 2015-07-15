 
#include "rtime.h"

#if defined(WIN32)
#include <windows.h>
#include <locale.h>
#else
#if defined(__SYMBIAN32__) || defined(SYMBIAN)
#include <e32std.h>
#else
#include <time.h>
#include <sys/time.h>
#endif
#endif

namespace chikkooos
{

static const int MSecPerSec     = 1000;
static const int MSecPerMinute  = 60 * MSecPerSec;
static const int MSecPerHour    = 60 * MSecPerMinute;

RTime::RTime()
 : mMS(0)
{}

void RTime::start()
{
    *this = currentTime();
}

unsigned int RTime::elapsed() const
{
    RTime ct = RTime::currentTime();

    long diff = ct.mMS - mMS;
    
    if (diff < 0) {
        return diff + 86400 * 1000;
    } else {
        return diff;
    }
}

#if defined(WIN32)
RTime RTime::currentTime()
{
    SYSTEMTIME st;
    memset(&st, 0, sizeof(SYSTEMTIME));
    GetLocalTime(&st);
    RTime ct;
    ct.mMS = fromTimeComponentToMS(st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    return ct;
}
#else
#if defined(__SYMBIAN32__) || defined(SYMBIAN)
RTime RTime::currentTime()
{
    RTime ct;
    TTime localTime;
    localTime.HomeTime();
    TDateTime localDateTime = localTime.DateTime();
    ct.mMS = fromTimeComponentToMS((unsigned long)localDateTime.Hour(),
                  (unsigned long)localDateTime.Minute(),
                  (unsigned long)localDateTime.Second(),
                  (unsigned long)(localDateTime.MicroSecond() / 1000));
    return ct;
}
#else
RTime RTime::currentTime()
{
    RTime ct;
    
    struct timeval tv;
    gettimeofday(&tv, 0);
    time_t ltime = tv.tv_sec;
    struct tm *t = 0;
    
    tzset();
    struct tm res;
    t = localtime_r(&ltime, &res);
    
    if (t) {
        ct.mMS = fromTimeComponentToMS(t->tm_hour, t->tm_min, t->tm_sec, tv.tv_usec / 1000);
    }
    
    return ct;
}
#endif
#endif

unsigned long RTime::fromTimeComponentToMS(unsigned long hour, 
                         unsigned long minute,
                         unsigned long sec,
                         unsigned long msec)
{
    return MSecPerHour * hour +
           MSecPerMinute * minute +
           MSecPerSec * sec + msec;
}

}

