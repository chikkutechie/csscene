
#include "rb2dbodyitem.h"

#include "rtransutils.h"
#include "rrectangle.h"
#include "rsolidsphere.h"

namespace chikkooos
{

RB2DBodyItem::RB2DBodyItem()
{
    mBody = new RB2DBody();
}

RItem * RB2DBodyItem::clone()
{
    return new RB2DBodyItem();
}

void RB2DBodyItem::draw(RGc & gc) const
{
    if (!mShape.isNull()) {

        mProjection = gc.frustum();
        mCamera = gc.camera();
        mParentTransformation = gc.transformation();

        const_cast<RB2DBodyItem *>(this)->update();

        gc.pushTransform();
        gc.setTransformation(mTransformation);
        gc.draw(*mShape.data());
        gc.popTransform();
    }
}

void RB2DBodyItem::update()
{
    if (mBody) {
        mTransformation.reset();

        RVector pos = mBody->position();
        float angle = mBody->angle();

        float tx = mX+mWidth/2.0f;
        float ty = mY+mHeight/2.0f;

        mTransformation.translate(pos.x(), pos.y(), 0.0f);
        mTransformation.translate(tx, ty, 0.0f);
        mTransformation.rotate(angle, 0, 0, 1);
        mTransformation.translate(-tx, -ty, 0.0f);
    }
}

void RB2DBodyItem::setProperties(RPropertyMap const & map, std::string const & element)
{
    RItem::setProperties(map, element);

    if (map.has("position")) {
        mBody->setPosition(map.getVector("position"));
    } else if (map.has("boundedrect")) {
        mBody->setPosition(RVector(mX, mY));
    }

    mBody->setAngle(map.getFloat("angle"));

    std::string type = map.getString("type");
    if (type.compare("static") == 0) {
        mBody->setType(RB2DBody::Static);
    }

    mBody->setRestitution(map.getFloat("restitution", mBody->restitution()));
    mBody->setFriction(map.getFloat("friction", mBody->friction()));

    mBody->setDensity(map.getFloat("density", mBody->density()));

    if (map.has("box")) {
        RVector v = map.getVector("box");
        mBody->setSize(v.x(), v.y());
        mBody->setShape(RB2DBody::Box);

        mShape = new RRectangle(-v.x(), -v.y(), v.x(), v.y());

        setBoundedRect(-v.x(), -v.y(), 2.0f*v.x(), 2.0f*v.y());
    }

    if (map.has("circle")) {
        float r = map.getFloat("circle");
        mBody->setRadius(r);
        mBody->setShape(RB2DBody::Circle);

        mShape = new RSolidSphere(r*2.0f);

        setBoundedRect(-r, -r, 2.0f * r, 2.0f * r);
    }

    create();
}

}
