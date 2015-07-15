
#include "rphysicsitem.h"
#include "rgeometry.h"
#include "rlog.h"

namespace chikkooos
{

RPhysicsItem::RPhysicsItem(Type t)
 : mType(t)
{
    mObject.setItem(this);
}

RPhysicsItem::~RPhysicsItem()
{}

void RPhysicsItem::draw(RGc & gc) const
{
    if (isNull()) {
        const_cast<RPhysicsItem*>(this)->create();
    }

    gc.pushTransform();
    gc.multiplyTransformation(transformation());

    RItem::draw(gc);

    gc.popTransform();
}

bool RPhysicsItem::create()
{
    if (mObject.isNull()) {
        mObject.create();
    }

    return true;
}

void RPhysicsItem::destroy()
{
	mObject.destroy();
}

RItem * RPhysicsItem::clone()
{
    RPhysicsItem * item = new RPhysicsItem(type());

    item->setPosition(position());
    item->setMass(mass());
    item->setAngularDamping(angularDamping());
    item->setFriction(friction());
    item->setRestitution(restitution());

    return item;
}

void RPhysicsItem::setProperties(RPropertyMap const & map, std::string const & element)
{
    if (map.has("position")) {
        setPosition(map.getVector("position"));
    } else if (map.has("boundedrect")) {
        setPosition(RVector(mX, mY));
    }

    RGeometry & g = geometry();

    if (map.has("box")) {
        RVector v = map.getVector("box");
        g.setBox(v.x(), v.y(), v.z());
    } else if (map.has("cube")) {
        RVector v = map.getVector("cube");
        g.setBox(v.x(), v.y(), v.z());
    } else if (map.has("sphere")) {
        float v = map.getFloat("sphere");
        g.setSphere(v);
    } else if (map.has("cylinder")) {
        RVector v = map.getVector("cylinder");
        g.setCylinder(v.x(), v.y());
    }
    setRestitution(map.getFloat("restitution", restitution()));
    setFriction(map.getFloat("friction", friction()));

    if (mType == Dynamic) {
        setMass(map.getFloat("mass", mass()));
        setAngularDamping(map.getFloat("angularDamping", angularDamping()));
        if (map.has("inertiatensor")) {
            RVector v = map.getVector("inertiatensor");
            setInertiaTensor(v);
        } else {
            setInertiaTensor(geometry().defaultInertiaTensor(mass()));
        }
        setGravity(map.getVector("gravity", gravity()));
    }
}

}

