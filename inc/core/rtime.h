 
#ifndef RTIME_H
#define RTIME_H

namespace chikkooos
{

class RTime
{
public:
    RTime();
    
    void start();
    unsigned int elapsed() const;
    
public:
    static RTime currentTime();

private:
    static unsigned long fromTimeComponentToMS(unsigned long hour, 
                              unsigned long minute,
                              unsigned long sec,
                              unsigned long msec = 0);
private:
    unsigned long mMS;
};

}

#endif
