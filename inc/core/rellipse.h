
#ifndef RELLIPSE_H
#define RELLIPSE_H

#include "rshape.h"

namespace chikkooos
{

class REllipse: public RShape
{
public:
    enum Mode
    {
        FILL,
        STROKE
    };

    REllipse(float cx, float cy, float r, Mode mode = FILL)
     : mCx(cx),
       mCy(cy),
       mMajorRadii(r),
       mMinorRadii(r),
       mMode(mode)
    {
        create();
    }

    REllipse(float cx, float cy, float majorRadii, float minorRadii, Mode mode = FILL)
     : mCx(cx),
       mCy(cy),
       mMajorRadii(majorRadii),
       mMinorRadii(minorRadii),
       mMode(mode)
    {
        create();
    }

    void set(float cx, float cy, float majorRadii, float minorRadii, Mode mode = FILL)
    {
        mCx = cx;
        mCy = cy;
        mMajorRadii = majorRadii;
        mMinorRadii = minorRadii;
        mMode = mode;
        create();
    }

    GLenum primitive() const
    {
        if (mMode == FILL) {
            return GL_TRIANGLE_FAN;
        } else {
            return GL_LINE_STRIP;
        }
    }


private:
    void create();

private:
    float mCx;
    float mCy;
    float mMajorRadii;
    float mMinorRadii;
    Mode mMode;
};

}

#endif
