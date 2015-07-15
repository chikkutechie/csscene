
#include "rphysicsanimationitem.h"

namespace chikkooos
{

RPhysicsAnimationItem::RPhysicsAnimationItem()
{
    mAnimation.object().setItem(this);
}

RItem * RPhysicsAnimationItem::clone()
{
	return new RPhysicsAnimationItem();
}

void RPhysicsAnimationItem::draw(RGc & gc) const
{
    if (mAnimation.state() == RAnimation::None) {
        const_cast<RPhysicsAnimationItem *>(this)->mAnimation.start();
    } else if (mAnimation.state() == RAnimation::Running) {
        const_cast<RPhysicsAnimationItem *>(this)->mAnimation.step();
    }

    gc.pushTransform();
    gc.multiplyTransformation(mAnimation.transformation());

    RItem::draw(gc);

    gc.popTransform();
}

void RPhysicsAnimationItem::setProperties(RPropertyMap const & map, std::string const & element)
{
    RAnimationItem::setProperties(map, element);

    mAnimation.setPosition(map.getVector("position"));
    RGeometry & g = mAnimation.geometry();

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

    mAnimation.setRestitution(map.getFloat("restitution",
	                          mAnimation.restitution()));
    mAnimation.setFriction(map.getFloat("friction", mAnimation.friction()));

	mAnimation.setMass(map.getFloat("mass", mAnimation.mass()));
	mAnimation.setAngularDamping(map.getFloat("angularDamping",
	                             mAnimation.angularDamping()));

	if (map.has("inertiatensor")) {
		RVector v = map.getVector("inertiatensor");
		mAnimation.setInertiaTensor(v);
	} else {
		mAnimation.setInertiaTensor(mAnimation.geometry().defaultInertiaTensor(mAnimation.mass()));
	}

	mAnimation.setGravity(map.getVector("gravity", mAnimation.gravity()));

    if (map.has("intervals")) {
        float t;
        RPhysicsAnimation::IntervalVec intervals;
        std::stringstream is(map.getString("intervals"));
        while (is >> t) {
            intervals.push_back(t);
        }
        mAnimation.setIntervals(intervals);
    }

    if (map.has("impulses")) {
        float t = 0.0f;
        RVector v;
        RPhysicsAnimation::VectorArray veca;
        std::stringstream is(map.getString("impulses"));

        while (is >> t) {
            v.setX(t);

            t = 0.0f;
            is >> t;
            v.setY(t);

            t = 0.0f;
            is >> t;
            v.setZ(t);

            veca.push_back(v);

            t = 0.0f;
        }
        mAnimation.setImpulses(veca);
    }

    if (map.has("positions")) {
        float t = 0.0f;
        RVector v;
        std::stringstream is(map.getString("positions"));
        RPhysicsAnimation::VectorArray veca;

        while (is >> t) {
            v.setX(t);

            t = 0.0f;
            is >> t;
            v.setY(t);

            t = 0.0f;
            is >> t;
            v.setZ(t);

            veca.push_back(v);

            t = 0.0f;
        }
        mAnimation.setPositions(veca);
    }

}

}
