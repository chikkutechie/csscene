
#ifndef MATRIX_H
#define MATRIX_H

#include "rsharedobject.h"
#include "rvector.h"

namespace chikkooos
{

class RQuaternion;

class RMatrix
{
private:
    float mData[4*4];

public:
    RMatrix();

    RMatrix(float m11, float m12, float m13, float m14,
            float m21, float m22, float m23, float m24,
            float m31, float m32, float m33, float m34,
            float m41, float m42, float m43, float m44);

    RMatrix(const float m[4*4]);

    RMatrix operator+(RMatrix const & o) const
    {
    	RMatrix res = *this;
    	res.add(o);
    	return res;
    }

    RMatrix operator+(float v) const
    {
    	RMatrix res = *this;
    	res.add(v);
    	return res;
    }

    RMatrix& operator+=(float v)
    {
    	add(v);
    	return *this;
    }

    RMatrix operator-(RMatrix const & o) const
    {
    	RMatrix res = *this;
    	res.subtract(o);
    	return res;
    }

    RMatrix& operator-=(RMatrix const & o)
    {
    	subtract(o);
    	return *this;
    }

    RMatrix operator*(RMatrix const & m) const
    {
    	return multiply(m);
    }

    void reset();

    void load(const float m[4*4]);
    
    void load(float m11, float m12, float m13, float m14,
              float m21, float m22, float m23, float m24,
              float m31, float m32, float m33, float m34,
              float m41, float m42, float m43, float m44);

    float * data()
    {
        return &(mData[0]);
    }

    const float * data() const
    {
        return &(mData[0]);
    }

    float determinant() const;

    RMatrix invertTranspose() const;
    RMatrix inverse() const;

    RMatrix transpose() const;

    RMatrix multiply(const RMatrix & matrix2) const;
    RVector multiply(RVector const & p) const;
    RMatrix multiply(float v) const;

    void rotate(const RVector & axis, float angle);
    void scale(float xScale, float yScale, float zScale);
    void translate(float x, float y, float z);

    static const RMatrix & identity();
    static const RMatrix & zero();

    static RMatrix createLookAt(const RVector & eyePosition, const RVector & targetPosition, const RVector & up);
    static RMatrix createLookAt(float eyePositionX, float eyePositionY, float eyePositionZ,
                                 float targetCenterX, float targetCenterY, float targetCenterZ,
                                 float upX, float upY, float upZ);

    static RMatrix createPerspective(float fieldOfView, float aspectRatio, float zNearPlane, float zFarPlane);
    static RMatrix createPerspective(float left, float right, float bottom, float top,
                                     float zNearPlane, float zFarPlane);
    static RMatrix createOrthographic(float width, float height, float zNearPlane, float zFarPlane);
    static RMatrix createOrthographic(float left, float right, float bottom, float top,
                                            float zNearPlane, float zFarPlane);

    static RMatrix createScale(const RVector & scale);
    static RMatrix createRotation(const RVector & axis, float angle);
    static RMatrix createRotation(RQuaternion const &q);
    static RMatrix createTranslation(const RVector & translation);

private:

    void add(const RMatrix & m);
    void add(float scalar);

    void subtract(const RMatrix m);

    float & operator[](int index)
    {
    	return mData[index];
    }

    const float & operator[](int index) const
    {
    	return mData[index];
    }
};

}

#endif

