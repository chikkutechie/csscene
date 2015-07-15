
#ifndef RPARTICLEITEM_H
#define RPARTICLEITEM_H

#include "ranimationitem.h"
#include "rparticles.h"
#include "rsmartpointer.h"

namespace chikkooos
{

class RParticleItem: public RAnimationItem
{
public:
    RParticleItem(RItem * parent = 0)
     : RAnimationItem(parent)
    {}

    RSmartPointer<RParticles> particles() const
    {
        return mParticles;
    }

    void setParticles(RSmartPointer<RParticles> const & ps)
    {
        mParticles = ps;
    }

    void draw(RGc & gc) const;

    RItem * clone();
    void setProperties(RPropertyMap const & map, std::string const & element);

    RAnimation & animation()
    {
        return *mParticles.data();
    }
    virtual const RAnimation & animation() const
    {
        return *mParticles.data();
    }
protected:
    RSmartPointer<RParticles> mParticles;
};

}

#endif

