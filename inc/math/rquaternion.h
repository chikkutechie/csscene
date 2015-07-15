
#ifndef RQUATERNION_H
#define RQUATERNION_H

#include "rmatrix.h"

namespace chikkooos
{

class RQuaternion
{
public:
	RQuaternion(float s=1.0f, float x=0.0f, float y=0.0f, float z=0.0f)
	 : mS(s),
	   mX(x),
	   mY(y),
	   mZ(z)
	{}

	RQuaternion(const float * data)
	 : mS(data[0]),
	   mX(data[1]),
	   mY(data[2]),
	   mZ(data[3])
	{}

	RQuaternion(float angle, const RVector & axis)
	{
		set(angle, axis);
	}

    void set(float angle, const RVector & axis);

    void setIdentity()
    {
    	mX = 0.0f;
    	mY = 0.0f;
    	mZ = 0.0f;
    	mS = 1.0f;
    }

    bool isIdentity() const
    {
    	return mX == 0.0f && mY == 0.0f && mZ == 0.0f && mS == 1.0f;
    }

    bool isZero() const
    {
    	return mX == 0.0f && mY == 0.0f && mZ == 0.0f && mS == 0.0f;
    }

    RQuaternion conjugate()
    {
    	return RQuaternion(-mS, -mX, -mY, -mZ);
    }

    RQuaternion inverse();

    bool hasInverse();

    RQuaternion normalize() const;

    RQuaternion operator*(const RQuaternion & q);

    RMatrix matrix() const;

    float x() const
    {
    	return mX;
    }

    float y() const
    {
    	return mY;
    }

    float z() const
    {
    	return mZ;
    }

    float s() const
    {
    	return mS;
    }

private:
	float mS;
	float mX;
	float mY;
	float mZ;
};

}

#endif
