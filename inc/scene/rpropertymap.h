
#ifndef RPROPERTYMAP_H
#define RPROPERTYMAP_H

#include "rcommon.h"
#include "rvector.h"

#include <string>
#include <map>

namespace chikkooos
{

class RPropertyMap
{
private:
    typedef std::map<std::string, std::string> AttribMap;
    typedef AttribMap::iterator AttribMapIter;
    typedef AttribMap::const_iterator AttribMapConstIter;

public:
    void insert(std::pair<std::string, std::string> const & p)
    {
        mProperties.insert(p);
    }

    void insert(std::string const & n, std::string const & v)
    {
        mProperties.insert(std::pair<std::string, std::string>(n, v));
    }

    std::string getString(std::string const & name, std::string const & defaultValue="") const;
    int getInt(std::string const & name, int defaultValue=0) const;
    float getFloat(std::string const & name, float defaultValue=0.0f) const;
    RVector getVector(std::string const & name, RVector const & defaultValue=RVector()) const;
    int getPosition(std::string const & name) const;

    bool has(std::string const & name) const;
    bool isPosition(std::string const & name) const;

    static bool hasPositionMarker(std::string const &value);
    static int getPositionFromString(std::string const & value);
private:
    AttribMap mProperties;
};

}

#endif
