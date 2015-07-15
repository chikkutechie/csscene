
#include "rquaternion.h"

namespace chikkooos
{


void RQuaternion::set(float angle, const RVector & axis)
{
    float halfAngle = angle * 0.5f;

    float radians = halfAngle * M_PI / 180.0f;

    float sinHalfAngle = sinf(radians);

    RVector normal = axis.toUnit();
    mX = normal.x() * sinHalfAngle;
    mY = normal.y() * sinHalfAngle;
    mZ = normal.z() * sinHalfAngle;
    mS = cosf(radians);
}

bool RQuaternion::hasInverse()
{
    float n = mX * mX + mY * mY + mZ * mZ + mS * mS;
    if (n < 0.000001f) {
    	return false;
    } else {
    	return true;
    }
}

RQuaternion RQuaternion::inverse()
{
	float n = mX * mX + mY * mY + mZ * mZ + mS * mS;

    // Too close to zero.
    if (n < 0.000001f) {
    	return RQuaternion(0.0f, 0.0f, 0.0f, 0.0f);
    }

    n = 1.0f / n;

    RQuaternion dst;
	dst.mX = -mX * n;
	dst.mY = -mY * n;
	dst.mZ = -mZ * n;
	dst.mS = mS * n;

	return dst;
}

RQuaternion RQuaternion::normalize() const
{
	float n = mX * mX + mY * mY + mZ * mZ + mS * mS;

    // Too close to zero.
    if (n < 0.000001f) {
    	return RQuaternion(0.0f, 0.0f, 0.0f, 0.0f);
    }

    n = 1.0f / n;

	RQuaternion dst;
	dst.mX = mX * n;
	dst.mY = mY * n;
	dst.mZ = mZ * n;
	dst.mS = mS * n;

	return dst;
}

RQuaternion RQuaternion::operator*(const RQuaternion & q)
{
    float x = mS * q.mX + mX * q.mS + mY * q.mZ - mZ * q.mY;
    float y = mS * q.mY - mX * q.mZ + mY * q.mS + mZ * q.mX;
    float z = mS * q.mZ + mX * q.mY - mY * q.mX + mZ * q.mS;
    float s = mS * q.mS - mX * q.mX - mY * q.mY - mZ * q.mZ;

    return RQuaternion(s, x, y, z);
}

RMatrix RQuaternion::matrix() const
{
	return RMatrix::createRotation(*this);
}

}
