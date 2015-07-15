
#include "rcpbodyitem.h"
#include "rtransutils.h"
#include "rrectangle.h"
#include "rsolidsphere.h"
#include "rsegment.h"
#include "rcpshape.h"

namespace chikkooos
{

RCPBodyItem::RCPBodyItem()
{
    mBody = new RCPBody();
}

RItem * RCPBodyItem::clone()
{
    return new RCPBodyItem();
}

void RCPBodyItem::update(float dt)
{
    if (!mBody->body()) {
        create();
        mBody->setUserData(this);
    }

    RItem::update(dt);
}

void RCPBodyItem::draw(RGc & gc) const
{
    if (mBody->body()) {
        gc.pushTransform();
        gc.setTransformation(mBody->transformation());

        RItem::draw(gc);

        gc.popTransform();
    }
}

void RCPBodyItem::setProperties(RPropertyMap const & map, std::string const & element)
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
        mBody->setType(RCPBody::Static);
    } else {
        mBody->setType(RCPBody::Dynamic);
    }

    mBody->setVelocity(map.getVector("velocity"));
    mBody->setForce(map.getVector("force"));
    mBody->setMass(map.getFloat("mass", mBody->mass()));
}

}
