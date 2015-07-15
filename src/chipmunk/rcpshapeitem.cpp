
#include "rcpshapeitem.h"
#include "rcpbodyitem.h"
#include "rrectangle.h"
#include "rellipse.h"
#include "rsegment.h"
#include "rshapeitem.h"

namespace chikkooos
{

RItem * RCPShapeItem::clone()
{
    return new RCPShapeItem();
}

void RCPShapeItem::update(float dt)
{
    create();

    RItem::update(dt);
}

void RCPShapeItem::create()
{
    if (!mCPShape->shape()) {
        if (!mBody && mBodyId) {
            mBody = dynamic_cast<RCPBodyItem *>(root()->findItemById(mBodyId));
        }

        if (!mBody) {
            mBody = dynamic_cast<RCPBodyItem *>(parent());
        }

        if (mBody && mBody->body()) {
            mBody->setMoment(mCPShape->moment(mBody->mass()));
            mCPShape->setBody(mBody->body());
            mCPShape->create();
            mBody->body()->addShape(mCPShape);
        }
        mCPShape->setUserData(this);
    }
}

void RCPShapeItem::destroy()
{
    mCPShape = 0;
}

void RCPShapeItem::createGraphicsShape()
{
    clear();

    RShapeItem * shapeItem = new RShapeItem();

    switch (mCPShape->shapeType()) {
        case RCPShape::Box: {
            RSizeF size = mCPShape->size();
            shapeItem->setShape(new RRectangle(-size.width()/2.0f, -size.height()/2.0f, size.width()/2.0f, size.height()/2.0f));
        }
        break;

        case RCPShape::Circle:
            shapeItem->setShape(new REllipse(0.0f, 0.0f, mCPShape->radius()));
        break;

        case RCPShape::Segment: {
            RVector a = mCPShape->segmentStart();
            RVector b = mCPShape->segmentEnd();
            shapeItem->setShape(new RSegment(a.x(), a.y(), b.x(), b.y(), mCPShape->radius()));
        }
        break;
    }

    if (shapeItem) {
        add(shapeItem);
    }
}

void RCPShapeItem::setProperties(RPropertyMap const & map, std::string const & element)
{
    RItem::setProperties(map, element);

    mCustomShape = (map.getInt("customshape") != 0);
    mBodyId = map.getInt("body", 0);

    if (map.has("box")) {
        RVector v = map.getVector("box");

        setSize(v.x(), v.y());
        setShapeType(RCPShape::Box);

        setBoundedRect(-v.x()/2, -v.y()/2, v.x(), v.y());

    } else if (map.has("circle")) {
        float r = map.getFloat("circle");

        setRadius(r/2.0f);
        setShapeType(RCPShape::Circle);

        setBoundedRect(-r, -r, r, r);
    } else if (map.has("segment")) {
        RVector pos = map.getVector("segment");
        float r = map.getFloat("radius");

        setRadius(r);
        setSegmentPos(pos.x(), pos.y(), pos.z(), pos.w());
        setShapeType(RCPShape::Segment);

        setBoundedRect(pos.x(), pos.y(), pos.z()-pos.x(), pos.w()-pos.y());
    }

    if (!mCustomShape) {
        createGraphicsShape();
    }

    setElasticity(map.getFloat("elasticity", mCPShape->elasticity()));
    setFriction(map.getFloat("friction", mCPShape->friction()));
}

}
