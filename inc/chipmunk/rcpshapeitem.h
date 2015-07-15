
#ifndef RCPSHAPEITEM_H
#define RCPSHAPEITEM_H

#include "ritem.h"
#include "rcpshape.h"

namespace chikkooos
{

class RCPBodyItem;

class RCPShapeItem: public RItem
{
public:
    RCPShapeItem()
     : mCPShape(new RCPShape()),
       mCustomShape(false),
       mBodyId(0),
       mBody(0)
    {}

    void create();
    void destroy();

    RItem * clone();

    void update(float dt);

    void setProperties(RPropertyMap const & map, std::string const & element);

    void setShapeType(RCPShape::Shape s, bool withGraphicsShape = false)
    {
        mCPShape->setShapeType(s);

        if (withGraphicsShape) {
            createGraphicsShape();
        }
    }

    RCPShape::Shape shapeType() const
    {
        return mCPShape->shapeType();
    }

    void setSize(float w, float h)
    {
        mCPShape->setSize(w, h);
    }

    void setRadius(float r)
    {
        mCPShape->setRadius(r);
    }

    void setSegmentPos(float x1, float y1, float x2, float y2)
    {
        mCPShape->setSegmentPos(x1, y1, x2, y2);
    }

    void setFriction(float f)
    {
        mCPShape->setFriction(f);
    }

    float friction() const
    {
        return mCPShape->friction();
    }

    void setElasticity(float e)
    {
        mCPShape->setElasticity(e);
    }

    float elasticity() const
    {
        return mCPShape->elasticity();
    }

    RCPShape * cpShape()
    {
        return mCPShape.data();
    }

    void setBodyItem(RCPBodyItem * b)
    {
        mBody = b;
    }

    void setCollisionType(int t)
    {
        mCPShape->setCollisionType(t);
    }

    int collisionType() const
    {
        return collisionType();
    }


protected:
    void createGraphicsShape();

protected:
    RSmartPointer<RCPShape> mCPShape;
    bool mCustomShape;
    int mBodyId;
    RCPBodyItem * mBody;
};

}

#endif

