
#include "rellipse.h"

#include <cmath>

namespace chikkooos
{

void REllipse::create()
{
    clear();

    const float slices = 20;

    if (mMode == FILL) {
        addVertex(mCx, mCy, 0.0f);
    }

    float twopi = 2.0f * (float)M_PI;
    float interval = twopi/slices;
    float i = 0.0f;
    float angleLimit = twopi+interval;

    for (; i<angleLimit; i += interval) {

        float x = mMajorRadii * cosf(i);
        float y = mMinorRadii * sinf(i);

        if (i > twopi) {
            x = mMajorRadii;
            y = 0.0f;
        } else {
            x = mMajorRadii * cosf(i);
            y = mMinorRadii * sinf(i);
        }

        float tx = ((x / mMajorRadii) + 1.0f ) / 2.0f;
        float ty = ((y / mMinorRadii) + 1.0f ) / 2.0f;

        x += mCx;
        y += mCy;

        addVertex(x, y, 0.0f);

        addTexCoord(tx, ty);

        addNormal(0.0f, 0.0f, 1.0f);
    }
}

}
