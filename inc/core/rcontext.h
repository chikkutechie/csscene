
#ifndef RCONTEXT_H
#define RCONTEXT_H

#include <string>

namespace chikkooos
{

class RGc;
class RFrameBufferImpl;

class RContext
{
public:
    static RContext & instance();

public:
    void setContext(std::string const & name);
    RGc * createGc();
    RFrameBufferImpl * createFrameBufferImpl();

private:
    RContext();
    RContext(RContext const &);
    RContext& operator=(RContext const &);

private:
    std::string mContext;
};

}

#endif

