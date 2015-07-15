
#include "rb2dbody.h"
#include "rb2dworld.h"

#include "Box2D/Collision/Shapes/b2CircleShape.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"

namespace chikkooos
{

RB2DBody::RB2DBody()
 : mBody(0),
   mType(Dynamic),
   mShape(Box),
   mPosition(0.0f, 0.0f, 0.0f),
   mAngle(0.0f),
   mDensity(0.0f)
{}

RB2DBody::~RB2DBody()
{
    destroy();
}

float RB2DBody::angle() const
{
    if (mBody) {
        mAngle = radToDeg(mBody->GetAngle());
    }

    return mAngle;
}

void RB2DBody::setAngle(float a)
{
    mAngle = a;

    if (mBody) {
        mBody->SetTransform(mBody->GetPosition(), a);
    }
}

RVector RB2DBody::position() const
{
    if (mBody) {
        mPosition = RVector(mBody->GetPosition().x * PTM_RATIO, mBody->GetPosition().y * PTM_RATIO, 0, 1);
    }

    return mPosition;
}

void RB2DBody::setPosition(RVector const & pos)
{
    mPosition.set(pos.x()/PTM_RATIO, pos.y()/PTM_RATIO, 0);
    if (mBody) {
        mBody->SetTransform(b2Vec2(mPosition.x()/PTM_RATIO, mPosition.y()/PTM_RATIO), mBody->GetAngle());
    }
}

RTransformation RB2DBody::transformation() const
{
    return RTransformation();
}

void RB2DBody::create()
{
    destroy();

    mBodyDef.position.Set(mPosition.x(), mPosition.y());
    mBodyDef.angle = degToRad(mAngle);
    mBodyDef.type = b2_dynamicBody;

    if (mType == Static) {
        mBodyDef.type = b2_staticBody;
    } else if (mType == Kinematic) {
        mBodyDef.type = b2_kinematicBody;
    }

    mBody = RB2DWorld::instance()->world()->CreateBody(&mBodyDef);

    if (mShape == Circle) {
        b2CircleShape * shape = new b2CircleShape();
        shape->m_p.Set(0, 0);
        shape->m_radius = mRadius;
        mBodyShape = shape;
    } else {
        b2PolygonShape * shape = new b2PolygonShape();
        shape->SetAsBox(mWidth, mHeight);
        mBodyShape = shape;
    }

    mFixtureDef.shape = mBodyShape.data();
    mFixtureDef.density = mDensity;

    mBody->CreateFixture(&mFixtureDef);
}

void RB2DBody::destroy()
{
    if (mBody) {
        RB2DWorld::instance()->world()->DestroyBody(mBody);
        mBodyShape = 0;
        mBody = 0;
    }
}

}
