#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include "rvector.h"

namespace chikkooos
{

class RBezierCurve
{
public:
    static const int Quad  = 0;
	static const int Cubic = 1;

private:
	int mType;
	RVector mStart;
	RVector mEnd;
	RVector mControl1;
	RVector mControl2;

public:
    RBezierCurve(int type = Quad)
    {
		mType = type;
	}

	void setStart(RVector s)
	{
		mStart = s;
	}

	void setEnd(RVector s)
	{
		mEnd = s;
	}

	void setControl1(RVector s)
	{
		mControl1 = s;
	}

	void setControl2(RVector s)
	{
		mControl2 = s;
	}

	RVector interpolate(float t);

private:
    RVector interpolateQuad(float t);

	RVector interpolateCubic(float t);

};

}

#endif

