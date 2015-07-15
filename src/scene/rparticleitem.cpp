
#include "rparticleitem.h"
#include "rvelocityparticles.h"
#include "rlinearparticles.h"
#include "rbezierparticles.h"

namespace chikkooos
{

void RParticleItem::draw(RGc & gc) const
{
    if (!mParticles.isNull()) {
        if (mParticles->state() == RAnimation::None) {
            const_cast<RParticleItem *>(this)->mParticles->start();
        } else if (mParticles->state() == RAnimation::Running) {
            const_cast<RParticleItem *>(this)->mParticles->step();
        }
        gc.draw(*(mParticles.data()));
    }
}

RItem * RParticleItem::clone()
{
    return new RParticleItem(*this);
}

void RParticleItem::setProperties(RPropertyMap const & map, std::string const & element)
{
    if (element.compare("velocityparticles") == 0) {
        RVelocityParticles * ps = new RVelocityParticles();

        RVector sp = map.getVector("speed", RVector(ps->speedFrom(), ps->speedTo()));
        ps->setSpeed(sp.x(), sp.y());

        RVector xv = map.getVector("xvelocity", RVector(ps->xVelocityFrom(), ps->xVelocityTo()));
        ps->setXVelocity(xv.x(), xv.y());
        RVector yv = map.getVector("yvelocity", RVector(ps->yVelocityFrom(), ps->yVelocityTo()));
        ps->setYVelocity(yv.x(), yv.y());
        RVector zv = map.getVector("zvelocity", RVector(ps->zVelocityFrom(), ps->zVelocityTo()));
        ps->setZVelocity(zv.x(), zv.y());

        ps->setMaxX(map.getFloat("maxx", ps->maxX()));
        ps->setMaxY(map.getFloat("maxy", ps->maxY()));
        ps->setMaxZ(map.getFloat("maxz", ps->maxZ()));

        ps->setAlphaTransition(map.getInt("alphatransition", ps->alphaTransition()));

        ps->setGravity(map.getVector("gravity", ps->gravity()));

        mParticles = ps;
    } else if (element.compare("linearparticles") == 0) {
        RLinearParticles * ps = new RLinearParticles();

        RVector xv = map.getVector("xend", RVector(ps->xEndFrom(), ps->xEndTo()));
        ps->setXEnd(xv.x(), xv.y());
        RVector yv = map.getVector("yend", RVector(ps->yEndFrom(), ps->yEndTo()));
        ps->setYEnd(yv.x(), yv.y());
        RVector zv = map.getVector("zend", RVector(ps->zEndFrom(), ps->zEndTo()));
        ps->setZEnd(zv.x(), zv.y());

        mParticles = ps;
    } else if (element.compare("bezierparticles") == 0) {
        RBezierParticles * ps = new RBezierParticles();

        RVector xv = map.getVector("xend", RVector(ps->xEndFrom(), ps->xEndTo()));
        ps->setXEnd(xv.x(), xv.y());
        RVector yv = map.getVector("yend", RVector(ps->yEndFrom(), ps->yEndTo()));
        ps->setYEnd(yv.x(), yv.y());
        RVector zv = map.getVector("zend", RVector(ps->zEndFrom(), ps->zEndTo()));
        ps->setZEnd(zv.x(), zv.y());

        xv = map.getVector("xcontrol", RVector(ps->xControlFrom(), ps->xControlTo()));
        ps->setXControl(xv.x(), xv.y());
        yv = map.getVector("ycontrol", RVector(ps->yControlFrom(), ps->yControlTo()));
        ps->setYControl(yv.x(), yv.y());
        zv = map.getVector("zcontrol", RVector(ps->zControlFrom(), ps->zControlTo()));
        ps->setZControl(zv.x(), zv.y());

        mParticles = ps;
    }

    if (!mParticles.isNull()) {
        RVector xv = map.getVector("xstart", RVector(mParticles->xStartFrom(), mParticles->xStartTo()));
        mParticles->setXStart(xv.x(), xv.y());
        RVector yv = map.getVector("ystart", RVector(mParticles->yStartFrom(), mParticles->yStartTo()));
        mParticles->setYStart(yv.x(), yv.y());
        RVector zv = map.getVector("zstart", RVector(mParticles->zStartFrom(), mParticles->zStartTo()));
        mParticles->setZStart(zv.x(), zv.y());

        mParticles->setMaximumParticleCount(map.getInt("count", mParticles->count())); 

        mParticles->setSize(map.getInt("size", mParticles->size())); 
        mParticles->setSmoothStop(map.getInt("smoothstop", mParticles->smoothStop())); 

        RAnimationItem::setProperties(map, element);
    }
}

}

