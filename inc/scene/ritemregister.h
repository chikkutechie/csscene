
#ifndef RITEMREGISTER_H
#define RITEMREGISTER_H

#include "rcommon.h"
#include "rsmartpointer.h"
#include "ritem.h"

#include <map>

namespace chikkooos
{

class RItem;

class RItemRegister
{
private:
    static RItemRegister * instance();

public:
    static bool addItem(std::string const & name, RItem * item);
    static void removeItem(std::string const & name);
    static RItem * getItem(std::string const & name);
    static bool hasItem(std::string const & name);

private:
    bool add(std::string const & name, RItem * item);
    void remove(std::string const & name);
    RItem * get(std::string const & name);
    bool has(std::string const & name) const;

private:
    RItemRegister();

    RItemRegister(RItemRegister const &);
    RItemRegister & operator=(RItemRegister const &);

private:
    typedef std::map<std::string, RSmartPointer<RItem> > ItemMap;
    typedef ItemMap::iterator ItemMapIter;
    typedef ItemMap::const_iterator ItemMapConstIter;

private:
    ItemMap mItems;
};

}

#endif

