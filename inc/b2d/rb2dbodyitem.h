
#ifndef RB2DBODYITEM_H
#define RB2DBODYITEM_H

#include "ritem.h"
#include "rb2dbody.h"

namespace chikkooos
{

class RB2DBodyItem: public RItem
{
public:
    RB2DBodyItem();

    RItem * clone();

    void draw(RGc & gc) const;

    void setProperties(RPropertyMap const & map, std::string const & element);

    RB2DBody * body()
    {
        return mBody.data();
    }

    void setBody(RB2DBody *b)
    {
        mBody = b;
    }

    void setShape(RSmartPointer<RShape> s)
    {
        mShape = s;
    }

    void setPosition(RVector const & pos)
    {
        mBody->setPosition(pos);
    }

    RVector position() const
    {
        return mBody->position();
    }

    void setAngle(float a)
    {
        mBody->setAngle(a);
    }

    float angle() const
    {
        return mBody->angle();
    }

    void create()
    {
        mBody->create();
    }

    void update();

protected:
    RSmartPointer<RB2DBody> mBody;
    RSmartPointer<RShape> mShape;
    RTransformation mTransformation;

    mutable RFrustum mProjection;
    mutable RCamera mCamera;
    mutable RTransformation mParentTransformation;
};

}

#endif
