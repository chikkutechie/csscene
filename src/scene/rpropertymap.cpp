
#include "rpropertymap.h"
#include <sstream>

namespace chikkooos
{

std::string RPropertyMap::getString(std::string const & name, std::string const & defaultValue) const
{
    AttribMapConstIter iter = mProperties.find(name);
    if (iter != mProperties.end()) {
        return iter->second;
    } else {
        return defaultValue;
    }
}

int RPropertyMap::getInt(std::string const & name, int defaultValue) const
{
    int v = 0;

    AttribMapConstIter iter = mProperties.find(name);
    if (iter != mProperties.end()) {
        std::stringstream ss(iter->second);
        ss >> v;
    } else {
        v = defaultValue;
    }

    return v;
}

float RPropertyMap::getFloat(std::string const & name, float defaultValue) const
{
    float v = 0.0f;

    AttribMapConstIter iter = mProperties.find(name);
    if (iter != mProperties.end()) {
        std::stringstream ss(iter->second);
        ss >> v;
    } else {
        v = defaultValue;
    }

    return v;
}

RVector RPropertyMap::getVector(std::string const & name, RVector const & defaultValue) const
{
    AttribMapConstIter iter = mProperties.find(name);
    if (iter != mProperties.end()) {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        float w = 1.0f;
        std::stringstream ss(iter->second);
        ss >> x;
        ss >> y;
        ss >> z;
        ss >> w;
        return RVector(x, y, z, w);
    } else {
        return defaultValue;
    }
}

int RPropertyMap::getPosition(std::string const & name) const
{
    return RPropertyMap::getPositionFromString(getString(name));
}

bool RPropertyMap::has(std::string const & name) const
{
    return (mProperties.find(name) != mProperties.end());
}

int RPropertyMap::getPositionFromString(std::string const & value)
{
    int pos = -1;

    if (!value.empty() && value[0] == '@') {
        std::stringstream ss(value.substr(1, value.length()-1));
        ss >> pos;
    }

    return pos;
}

bool RPropertyMap::hasPositionMarker(std::string const &value)
{
    if (!value.empty()) {
        return value[0] == '@';
    }
    return false;
}

bool RPropertyMap::isPosition(std::string const & name) const
{
    return hasPositionMarker(getString(name));
}

}

