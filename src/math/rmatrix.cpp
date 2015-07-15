
#include "rcommon.h"
#include "rutils.h"
#include "rmatrix.h"
#include "rquaternion.h"

#include <math.h>
#include <string.h>

namespace chikkooos
{

#define MATRIX_SIZE ( sizeof(float) * 16)

namespace
{
static const float MATRIX_IDENTITY[16] =
{
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};
}

RMatrix::RMatrix()
{
    *this = RMatrix::identity();
}

RMatrix::RMatrix(float m11, float m12, float m13, float m14,
        float m21, float m22, float m23, float m24,
        float m31, float m32, float m33, float m34,
        float m41, float m42, float m43, float m44)
{
	load(m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44);
}

RMatrix::RMatrix(const float m[4*4])
{
	load(m);
}

RMatrix RMatrix::createLookAt(const RVector & eyePosition, const RVector & targetPosition, const RVector & up)
{
	return createLookAt(eyePosition.x(), eyePosition.y(), eyePosition.z(),
            			targetPosition.x(), targetPosition.y(), targetPosition.z(),
            			up.x(), up.y(), up.z());
}

RMatrix RMatrix::createLookAt(float eyePositionX, float eyePositionY, float eyePositionZ,
        float targetPositionX, float targetPositionY, float targetPositionZ,
        float upX, float upY, float upZ)
{
	RVector eye(eyePositionX, eyePositionY, eyePositionZ);
	RVector target(targetPositionX, targetPositionY, targetPositionZ);
	RVector up(upX, upY, upZ);
	up = up.normalize();

    RVector zaxis = eye - target;
    zaxis = zaxis.normalize();

    RVector xaxis = up.cross(zaxis);
    xaxis = xaxis.normalize();

    RVector yaxis = zaxis.cross(xaxis);
	yaxis = yaxis.normalize();

	RMatrix dst;

    dst[0] = xaxis.x();
    dst[1] = yaxis.x();
    dst[2] = zaxis.x();
    dst[3] = 0.0f;

    dst[4] = xaxis.y();
    dst[5] = yaxis.y();
    dst[6] = zaxis.y();
    dst[7] = 0.0f;

    dst[8] = xaxis.z();
    dst[9] = yaxis.z();
    dst[10] = zaxis.z();
    dst[11] = 0.0f;

    dst[12] = -xaxis.dot3(eye);
    dst[13] = -yaxis.dot3(eye);
    dst[14] = -zaxis.dot3(eye);
    dst[15] = 1.0f;

    return dst;
}

RMatrix RMatrix::createPerspective(float left, float right, float bottom, float top, float nearZ, float farZ)
{
	RMatrix dst;

	float deltaX = right - left;
	float deltaY = top - bottom;
	float deltaZ = farZ - nearZ;

	if ( ( nearZ <= 0.0f ) || ( farZ <= 0.0f ) ||
			( deltaX <= 0.0f ) || ( deltaY <= 0.0f ) || ( deltaZ <= 0.0f ) ) {
		return dst;
	}

    dst = RMatrix::zero();

    dst[0] = 2.0f * nearZ / deltaX;
    dst[1] = 0.0f;
    dst[2] = 0.0f;
    dst[3] = 0.0f;
    dst[4] = 0.0f;
    dst[5] = 2.0f * nearZ / deltaY;
    dst[6] = 0.0f;
    dst[7] = 0.0f;
    dst[8] = ( right + left ) / deltaX;
    dst[9] = ( top + bottom ) / deltaY;
    dst[10] = - ( nearZ + farZ ) / deltaZ;
    dst[11] = -1.0f;
    dst[12] = 0.0f;
    dst[13] = 0.0f;
    dst[14] = -2.0f * nearZ * farZ / deltaZ;
    dst[15] = 0.0f;

	return dst;
}

RMatrix RMatrix::createPerspective(float fieldOfView, float aspectRatio,
        						   float zNearPlane, float zFarPlane)
{
    float f_n = 1.0f / (zFarPlane - zNearPlane);
    float theta = MATH_DEG_TO_RAD(fieldOfView) * 0.5f;
    if (fabs(fmod(theta, MATH_PIOVER2)) < MATH_EPSILON)
    {
        return RMatrix();
    }
    float divisor = tan(theta);
    float factor = 1.0f / divisor;

    RMatrix dst = RMatrix::zero();

    dst[0] = (1.0f / aspectRatio) * factor;
    dst[5] = factor;
    dst[10] = (-(zFarPlane + zNearPlane)) * f_n;
    dst[11] = -1.0f;
    dst[14] = -2.0f * zFarPlane * zNearPlane * f_n;

    return dst;
}

RMatrix RMatrix::createOrthographic(float width, float height, float zNearPlane, float zFarPlane)
{
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
    return createOrthographic(-halfWidth, halfWidth, -halfHeight, halfHeight, zNearPlane, zFarPlane);
}

RMatrix RMatrix::createOrthographic(float left, float right, float bottom, float top,
                                    float zNearPlane, float zFarPlane)
{
	RMatrix dst = RMatrix::zero();

    dst[0] = 2 / (right - left);
    dst[5] = 2 / (top - bottom);
    dst[12] = (left + right) / (left - right);
    dst[10] = 1 / (zNearPlane - zFarPlane);
    dst[13] = (top + bottom) / (bottom - top);
    dst[14] = zNearPlane / (zNearPlane - zFarPlane);
    dst[15] = 1;

    return dst;
}

RMatrix RMatrix::createScale(const RVector & scale)
{
	RMatrix dst;

    dst[0] = scale.x();
    dst[5] = scale.y();
    dst[10] = scale.z();

	return dst;
}

RMatrix RMatrix::createRotation(RQuaternion const &q)
{
	RMatrix dst;

    float x2 = q.x() + q.x();
    float y2 = q.y() + q.y();
    float z2 = q.z() + q.z();

    float xx2 = q.x() * x2;
    float yy2 = q.y() * y2;
    float zz2 = q.z() * z2;
    float xy2 = q.x() * y2;
    float xz2 = q.x() * z2;
    float yz2 = q.y() * z2;
    float wx2 = q.s() * x2;
    float wy2 = q.s() * y2;
    float wz2 = q.s() * z2;

    dst[0] = 1.0f - yy2 - zz2;
    dst[1] = xy2 + wz2;
    dst[2] = xz2 - wy2;

    dst[4] = xy2 - wz2;
    dst[5] = 1.0f - xx2 - zz2;
    dst[6] = yz2 + wx2;

    dst[8] = xz2 + wy2;
    dst[9] = yz2 - wx2;
    dst[10] = 1.0f - xx2 - yy2;

    return dst;
}

RMatrix RMatrix::createRotation(const RVector & axis, float angle)
{
    float x = axis.x();
    float y = axis.y();
    float z = axis.z();

    // Make sure the input axis is normalized.
    float n = x*x + y*y + z*z;
    if (n != 1.0f)
    {
        // Not normalized.
        n = sqrt(n);
        // Prevent divide too close to zero.
        if (n > 0.000001f)
        {
            n = 1.0f / n;
            x *= n;
            y *= n;
            z *= n;
        }
    }

    float c = cos(MATH_DEG_TO_RAD(angle));
    float s = sin(MATH_DEG_TO_RAD(angle));

    float t = 1.0f - c;
    float tx = t * x;
    float ty = t * y;
    float tz = t * z;
    float txy = tx * y;
    float txz = tx * z;
    float tyz = ty * z;
    float sx = s * x;
    float sy = s * y;
    float sz = s * z;

    RMatrix dst;

    dst[0] = c + tx*x;
    dst[1] = txy + sz;
    dst[2] = txz - sy;
    dst[3] = 0.0f;

    dst[4] = txy - sz;
    dst[5] = c + ty*y;
    dst[6] = tyz + sx;
    dst[7] = 0.0f;

    dst[8] = txz + sy;
    dst[9] = tyz - sx;
    dst[10] = c + tz*z;
    dst[11] = 0.0f;

    dst[12] = 0.0f;
    dst[13] = 0.0f;
    dst[14] = 0.0f;
    dst[15] = 1.0f;

    return dst;
}

RMatrix RMatrix::createTranslation(const RVector & translation)
{
	RMatrix dst;

    dst[12] = translation.x();
    dst[13] = translation.y();
    dst[14] = translation.z();

    return dst;
}


const RMatrix & RMatrix::identity()
{
    static RMatrix m(
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 );
    return m;
}

const RMatrix & RMatrix::zero()
{
	static RMatrix m(
	        0, 0, 0, 0,
	        0, 0, 0, 0,
	        0, 0, 0, 0,
	        0, 0, 0, 0 );
	return m;
}

void RMatrix::reset()
{
	*this = RMatrix::identity();
}

void RMatrix::load(const float m[4*4])
{
	for (int i=0; i<16; ++i) {
		(*this)[i] = m[i];
	}
}

void RMatrix::load(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24,
             float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
{
	RMatrix &m = *this;

    m[0]  = m11;
    m[1]  = m21;
    m[2]  = m31;
    m[3]  = m41;
    m[4]  = m12;
    m[5]  = m22;
    m[6]  = m32;
    m[7]  = m42;
    m[8]  = m13;
    m[9]  = m23;
    m[10] = m33;
    m[11] = m43;
    m[12] = m14;
    m[13] = m24;
    m[14] = m34;
    m[15] = m44;
}


float RMatrix::determinant() const
{
	const RMatrix & m = *this;

    float a0 = m[0] * m[5] - m[1] * m[4];
    float a1 = m[0] * m[6] - m[2] * m[4];
    float a2 = m[0] * m[7] - m[3] * m[4];
    float a3 = m[1] * m[6] - m[2] * m[5];
    float a4 = m[1] * m[7] - m[3] * m[5];
    float a5 = m[2] * m[7] - m[3] * m[6];
    float b0 = m[8] * m[13] - m[9] * m[12];
    float b1 = m[8] * m[14] - m[10] * m[12];
    float b2 = m[8] * m[15] - m[11] * m[12];
    float b3 = m[9] * m[14] - m[10] * m[13];
    float b4 = m[9] * m[15] - m[11] * m[13];
    float b5 = m[10] * m[15] - m[11] * m[14];

    // Calculate the determinant.
    return (a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0);
}

RMatrix RMatrix::invertTranspose() const
{
	return inverse().transpose();
}

RMatrix RMatrix::inverse() const
{
	const RMatrix &m = *this;

    float a0 = m[0] * m[5] - m[1] * m[4];
    float a1 = m[0] * m[6] - m[2] * m[4];
    float a2 = m[0] * m[7] - m[3] * m[4];
    float a3 = m[1] * m[6] - m[2] * m[5];
    float a4 = m[1] * m[7] - m[3] * m[5];
    float a5 = m[2] * m[7] - m[3] * m[6];
    float b0 = m[8] * m[13] - m[9] * m[12];
    float b1 = m[8] * m[14] - m[10] * m[12];
    float b2 = m[8] * m[15] - m[11] * m[12];
    float b3 = m[9] * m[14] - m[10] * m[13];
    float b4 = m[9] * m[15] - m[11] * m[13];
    float b5 = m[10] * m[15] - m[11] * m[14];

    // Calculate the determinant.
    float det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;

    // Close to zero, can't invert.
    if (fabs(det) <= MATH_TOLERANCE) {
        return RMatrix();
    }

    RMatrix inverse;
    inverse[0]  = m[5] * b5 - m[6] * b4 + m[7] * b3;
    inverse[1]  = -m[1] * b5 + m[2] * b4 - m[3] * b3;
    inverse[2]  = m[13] * a5 - m[14] * a4 + m[15] * a3;
    inverse[3]  = -m[9] * a5 + m[10] * a4 - m[11] * a3;

    inverse[4]  = -m[4] * b5 + m[6] * b2 - m[7] * b1;
    inverse[5]  = m[0] * b5 - m[2] * b2 + m[3] * b1;
    inverse[6]  = -m[12] * a5 + m[14] * a2 - m[15] * a1;
    inverse[7]  = m[8] * a5 - m[10] * a2 + m[11] * a1;

    inverse[8]  = m[4] * b4 - m[5] * b2 + m[7] * b0;
    inverse[9]  = -m[0] * b4 + m[1] * b2 - m[3] * b0;
    inverse[10] = m[12] * a4 - m[13] * a2 + m[15] * a0;
    inverse[11] = -m[8] * a4 + m[9] * a2 - m[11] * a0;

    inverse[12] = -m[4] * b3 + m[5] * b1 - m[6] * b0;
    inverse[13] = m[0] * b3 - m[1] * b1 + m[2] * b0;
    inverse[14] = -m[12] * a3 + m[13] * a1 - m[14] * a0;
    inverse[15] = m[8] * a3 - m[9] * a1 + m[10] * a0;

    return inverse.multiply(1.0f / det);
}

RMatrix RMatrix::transpose() const
{
	const RMatrix & m =*this;

    float t[16] = {
        m[0], m[4], m[8], m[12],
        m[1], m[5], m[9], m[13],
        m[2], m[6], m[10], m[14],
        m[3], m[7], m[11], m[15]
    };

    return RMatrix(t);
}


RVector RMatrix::multiply(RVector const & v) const
{
	RVector dst;
	const RMatrix &m = *this;

    float x = v[0] * m[0] + v[1] * m[4] + v[2] * m[8] + v[3] * m[12];
    float y = v[0] * m[1] + v[1] * m[5] + v[2] * m[9] + v[3] * m[13];
    float z = v[0] * m[2] + v[1] * m[6] + v[2] * m[10] + v[3] * m[14];
    float w = v[0] * m[3] + v[1] * m[7] + v[2] * m[11] + v[3] * m[15];

    dst[0] = x;
    dst[1] = y;
    dst[2] = z;
    dst[3] = w;

    return dst;
}

RMatrix RMatrix::multiply(float scalar) const
{
	const RMatrix &m = *this;
	float dst[16];

    dst[0]  = m[0]  * scalar;
    dst[1]  = m[1]  * scalar;
    dst[2]  = m[2]  * scalar;
    dst[3]  = m[3]  * scalar;
    dst[4]  = m[4]  * scalar;
    dst[5]  = m[5]  * scalar;
    dst[6]  = m[6]  * scalar;
    dst[7]  = m[7]  * scalar;
    dst[8]  = m[8]  * scalar;
    dst[9]  = m[9]  * scalar;
    dst[10] = m[10] * scalar;
    dst[11] = m[11] * scalar;
    dst[12] = m[12] * scalar;
    dst[13] = m[13] * scalar;
    dst[14] = m[14] * scalar;
    dst[15] = m[15] * scalar;

    return RMatrix(dst);
}

RMatrix RMatrix::multiply(const RMatrix & m2) const
{
    const RMatrix &m1 = *this;
    float product[16];

    product[0]  = m1[0] * m2[0]  + m1[4] * m2[1] + m1[8]   * m2[2]  + m1[12] * m2[3];
    product[1]  = m1[1] * m2[0]  + m1[5] * m2[1] + m1[9]   * m2[2]  + m1[13] * m2[3];
    product[2]  = m1[2] * m2[0]  + m1[6] * m2[1] + m1[10]  * m2[2]  + m1[14] * m2[3];
    product[3]  = m1[3] * m2[0]  + m1[7] * m2[1] + m1[11]  * m2[2]  + m1[15] * m2[3];

    product[4]  = m1[0] * m2[4]  + m1[4] * m2[5] + m1[8]   * m2[6]  + m1[12] * m2[7];
    product[5]  = m1[1] * m2[4]  + m1[5] * m2[5] + m1[9]   * m2[6]  + m1[13] * m2[7];
    product[6]  = m1[2] * m2[4]  + m1[6] * m2[5] + m1[10]  * m2[6]  + m1[14] * m2[7];
    product[7]  = m1[3] * m2[4]  + m1[7] * m2[5] + m1[11]  * m2[6]  + m1[15] * m2[7];

    product[8]  = m1[0] * m2[8]  + m1[4] * m2[9] + m1[8]   * m2[10] + m1[12] * m2[11];
    product[9]  = m1[1] * m2[8]  + m1[5] * m2[9] + m1[9]   * m2[10] + m1[13] * m2[11];
    product[10] = m1[2] * m2[8]  + m1[6] * m2[9] + m1[10]  * m2[10] + m1[14] * m2[11];
    product[11] = m1[3] * m2[8]  + m1[7] * m2[9] + m1[11]  * m2[10] + m1[15] * m2[11];

    product[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8]  * m2[14] + m1[12] * m2[15];
    product[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9]  * m2[14] + m1[13] * m2[15];
    product[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
    product[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];

    return RMatrix(product);
}

void RMatrix::add(const RMatrix & m)
{
	for (int i=0; i<16; ++i) {
		(*this)[i] += m[i];
	}
}

void RMatrix::add(float scalar)
{
	for (int i=0; i<16; ++i) {
		(*this)[i] += scalar;
	}
}

void RMatrix::subtract(const RMatrix m)
{
	for (int i=0; i<16; ++i) {
		(*this)[i] -= m[i];
	}
}

void RMatrix::rotate(const RVector & axis, float angle)
{
    RMatrix r = createRotation(axis, angle);
    *this = multiply(r);
}

void RMatrix::scale(float xScale, float yScale, float zScale)
{
	RMatrix r = createScale(RVector(xScale, yScale, zScale));
	*this = multiply(r);
}

void RMatrix::translate(float x, float y, float z)
{
	RMatrix r = createTranslation(RVector(x, y, z));
	*this = multiply(r);
}

}

