
#ifndef RITEMCALLBACK_H
#define RITEMCALLBACK_H

#include "rsmartpointer.h"
#include "ritem.h"

#include <string>
#include <map>

namespace chikkooos
{

class RItemCallback
{
public:
    virtual ~RItemCallback()
    {}
    virtual void called(RItem * item) = 0;
};

class RItemCallbackRegister
{
public:
    static RItemCallbackRegister & instance();

    void add(std::string const & name, RItemCallback * callback);
    void remove(std::string const & name);

    RItemCallback * get(std::string const & name);

private:
    RItemCallbackRegister();
    RItemCallbackRegister(RItemCallbackRegister const &);
    RItemCallbackRegister & operator=(RItemCallbackRegister const &);

private:
    typedef std::map<std::string, RSmartPointer<RItemCallback> > Callbacks;
    typedef Callbacks::iterator CallbacksIter;
    typedef Callbacks::const_iterator CallbacksConstIter;

private:
    Callbacks mCallbacks;
};

}

#endif

