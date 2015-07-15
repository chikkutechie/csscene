
#ifndef RGCSETTINGS_H
#define RGCSETTINGS_H

#include "ritem.h"

namespace chikkooos
{

class RGCSettings: public RItem
{
private:
    int mDepthTest;
    int mBlending;
    int mCulling;

public:
    RGCSettings();

    void draw(RGc & gc) const;

    RItem * clone();
    void setProperties(RPropertyMap const & map, std::string const & element);

};

}

#endif

