
#ifndef RGLES1GC_H
#define RGLES1GC_H

#include "rgc.h"

#include <set>
#include <sstream>
#include <string>

namespace chikkooos
{

class RGles1Gc: public RGc
{
public:
    typedef RGc::Lights Lights;
    typedef RGc::LightsIter LightsIter;
    typedef RGc::LightsConstIter LightsConstIter;

public:
    RGles1Gc();
    ~RGles1Gc();

    virtual void draw(RShape const & s);
    virtual void draw(RParticles const & ps);
    virtual void drawShadow(RShape const & s);

protected:
    void drawSimple(RShape const & s);
    void drawTexture(RShape const & s);
    void drawLight(RShape const & s);
    void drawShadow(const RShapePlane & s, RVector const & lposition);

    virtual bool doInitialize();
};

}

#endif

