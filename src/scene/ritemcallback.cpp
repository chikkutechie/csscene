
#include "ritemcallback.h"

namespace chikkooos
{

RItemCallbackRegister::RItemCallbackRegister()
{}

RItemCallbackRegister & RItemCallbackRegister::instance()
{
    static RItemCallbackRegister obj;
    return obj;
}

void RItemCallbackRegister::add(std::string const & name, RItemCallback * callback)
{
    mCallbacks.insert(std::make_pair(name, callback));
}

void RItemCallbackRegister::remove(std::string const & name)
{
    CallbacksIter iter = mCallbacks.find(name);
    if (iter != mCallbacks.end()) {
        mCallbacks.erase(name);
    }
}

RItemCallback * RItemCallbackRegister::get(std::string const & name)
{
    CallbacksIter iter = mCallbacks.find(name);
    if (iter != mCallbacks.end()) {
        return iter->second;
    }
    return 0;
}

}

