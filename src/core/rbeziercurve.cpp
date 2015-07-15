#include "rbeziercurve.h"

namespace chikkooos
{

RVector RBezierCurve::interpolate(float t)
{
    if (t > 1.0f) {
        t = 1.0f;
    } else if (t < 0.0f) {
        t = 0.0f;
	}

	if (mType == Quad) {
        return interpolateQuad(t);
	} else {
        return interpolateCubic(t);
    }
}

RVector RBezierCurve::interpolateQuad(float t)
{
    float t2 = t * t;
    float omt2 = (1.0f-t) * (1.0f-t);
    float ttomt = 2.0f * t * (1.0f-t);

    float x = mStart.x() * omt2 + mControl1.x() * ttomt + mEnd.x() * t2;
    float y = mStart.y() * omt2 + mControl1.y() * ttomt + mEnd.y() * t2;
    float z = mStart.z() * omt2 + mControl1.z() * ttomt + mEnd.z() * t2;

	return RVector(x, y, z);
}

RVector RBezierCurve::interpolateCubic(float t)
{
    float t2 = t * t;
	float t3 = t2 * t;
	float omt = (1-t);
    float omt2 = omt * omt;
    float omt3 = omt2 * omt;

    float ttomt2 = 3 * t * omt2;

    float tt2omt = 3 * t2 * omt;

    float x = mStart.x() * omt3 + mControl1.x() * ttomt2 + mControl2.x() * tt2omt + mEnd.x() * t3;
    float y = mStart.y() * omt3 + mControl1.y() * ttomt2 + mControl2.y() * tt2omt + mEnd.y() * t3;
    float z = mStart.z() * omt3 + mControl1.z() * ttomt2 + mControl2.z() * tt2omt + mEnd.z() * t3;

	return RVector(x, y, z);
}

}

