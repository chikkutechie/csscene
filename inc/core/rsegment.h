
#ifndef RSEGMENT_H
#define RSEGMENT_H

#include <vector>

#include "rshape.h"

namespace chikkooos
{

class RSegment: public RShape
{
public:
    enum Mode
    {
        FILL,
        STROKE
    };

    RSegment(float x1, float y1, float x2, float y2, float r, Mode mode = FILL)
     : mX1(x1),
       mY1(y1),
       mX2(x2),
       mY2(y2),
       mRadius(r),
       mMode(mode)
    {
        create();
    }

    void set(float x1, float y1, float x2, float y2, float r, Mode mode = FILL)
    {
        mX1 = x1;
        mY1 = y1;
        mX2 = x2;
        mY2 = y2;
        mRadius = r;
        mMode = mode;
        create();
    }


    GLenum primitive() const
    {
        if (mMode == FILL) {
            return GL_TRIANGLE_FAN;
        } else {
            return GL_LINE_LOOP;
        }
    }


private:
    void create()
    {
        clear();

        RVector v1(mX1, mY1);
        RVector v2(mX2, mY2);

        RVector ray = (v2 - v1).normalize();

        float cosValue = ray.dot3(RVector(1, 0));
        float angle = acosf(cosValue);

        RMatrix rotMat1;
        rotMat1.translate(mX1, mY1, 0);
        rotMat1.rotate(RVector(0, 0, 1), radToDeg(angle));
        rotMat1.translate(-mX1, -mY1, 0);

        RMatrix rotMat2;
        rotMat2.translate(mX2, mY2, 0);
        rotMat2.rotate(RVector(0, 0, 1), radToDeg(angle));
        rotMat2.translate(-mX2, -mY2, 0);

        RVector p1 = rotMat1.multiply(RVector(mX1, mY1-mRadius));
        RVector p2 = rotMat2.multiply(RVector(mX2, mY2-mRadius));

        RVector p3 = rotMat2.multiply(RVector(mX2, mY2+mRadius));
        RVector p4 = rotMat1.multiply(RVector(mX1, mY1+mRadius));

        rLogI() << "Segment Angle : " << angle  << "(" << radToDeg(angle) << ")"<< std::endl;
        rLogI() << "Original point p1: " << RVector(mX1, mY1-mRadius) << "p2 : " << RVector(mX2, mY2-mRadius) << "p3 : " << RVector(mX2, mY2+mRadius) << "p4 : " << RVector(mX1, mY1+mRadius) << std::endl;
        rLogI() << "Tranform point p1 : " << p1 << "p2 : " << p2 << "p3 : " << p3 << "p4 : " << p4 << std::endl;

        addVertex(p1.x(), p1.y(), 0.0f);
        addVertex(p2.x(), p2.y(), 0.0f);
        addVertex(p3.x(), p3.y(), 0.0f);
        addVertex(p4.x(), p4.y(), 0.0f);

        addTexCoord(0.0f, 1.0f);
        addTexCoord(1.0f, 1.0f);
        addTexCoord(1.0f, 0.0f);
        addTexCoord(0.0f, 0.0f);

        addNormal(0.0f, 0.0f, 1.0f);
        addNormal(0.0f, 0.0f, 1.0f);
        addNormal(0.0f, 0.0f, 1.0f);
        addNormal(0.0f, 0.0f, 1.0f);
    }

private:
    float mX1;
    float mY1;
    float mX2;
    float mY2;
    float mRadius;

    Mode mMode;
};

}

#endif


