
#ifndef VECTOR_H
#define VECTOR_H

#include "rcommon.h"

namespace chikkooos
{

class RVector
{
public:
    RVector(float v1=0.0f, float v2=0.0f, float v3=0.0f, float v4=1.0f)
    {
        set(v1, v2, v3, v4);
    }

    RVector(const float *v)
    {
        set(v);
    }

    void set(const float *v)
    {
        set(v[0], v[1], v[2], v[3]);
    }

    void set(float v1=0.0f, float v2=0.0f, float v3=0.0f, float v4=1.0f)
    {
        setX(v1);
        setY(v2);
        setZ(v3);
        setW(v4);
    }

    bool operator==(RVector const &o) const
    {
        return x() == o.x() &&
               y() == o.y() &&
               z() == o.z() &&
               w() == o.z();
    }

    bool operator!=(RVector const &o) const
    {
        return !(*this == o);
    }

    RVector operator+(RVector const &o) const
    {
        return RVector ((x() + o.x()),
        		(y() + o.y()),
        		(z() + o.z()),
        		(w() + o.w()));
    }

    RVector operator-(RVector const &o) const
    {
        RVector v;
        v.setX(x() - o.x());
        v.setY(y() - o.y());
        v.setZ(z() - o.z());
        v.setW(w() - o.w());
        return v;
    }

    RVector operator*(RVector const &o) const
    {
        RVector v;
        v.setX(x() * o.x());
        v.setY(y() * o.y());
        v.setZ(z() * o.z());
        v.setW(w() * o.w());
        return v;
    }

    RVector operator*(float s) const
    {
        RVector v;
        v.setX(x() * s);
        v.setY(y() * s);
        v.setZ(z() * s);
        v.setW(w() * s);
        return v;
    }

    RVector operator/(float s) const
    {
        RVector v;
        v.setX(x() / s);
        v.setY(y() / s);
        v.setZ(z() / s);
        v.setW(w() / s);
        return v;
    }

    void setX(float v)
    {
        mData[0] = v;
    }

    void setY(float v)
    {
        mData[1] = v;
    }

    void setZ(float v)
    {
        mData[2] = v;
    }

    void setW(float v)
    {
        mData[3] = v;
    }

    void setR(float v)
    {
        setX(v);
    }

    void setG(float v)
    {
        setY(v);
    }

    void setB(float v)
    {
        setZ(v);
    }

    void setA(float v)
    {
        setW(v);
    }

    float x() const
    {
        return mData[0];
    }

    float y() const
    {
        return mData[1];
    }

    float z() const
    {
        return mData[2];
    }

    float w() const
    {
        return mData[3];
    }

    float r() const
    {
        return x();
    }

    float g() const
    {
        return y();
    }

    float b() const
    {
        return z();
    }

    float a() const
    {
        return w();
    }

    const float * data() const
    {
        return mData;
    }

    float length() const
    {
        return sqrt(x()*x() + y()*y() + z()*z());
    }

    RVector normalize() const
    {
    	return toUnit();
    }

    RVector toUnit() const
    {
        float l = length();
        if (l == 0.0f) {
            l = 1.0f;
        }

        return RVector(x()/l, y()/l, z()/l);
    }

    static RVector normal(RVector const &v1, RVector const &v2, RVector const &v3)
    {
        RVector vect1 = v1 - v2;
        RVector vect2 = v3 - v2;
        RVector n;

        n.setX(vect1.y()*vect2.z() - vect1.z()*vect2.y());
        n.setY(vect1.z()*vect2.x() - vect1.x()*vect2.z());
        n.setZ(vect1.x()*vect2.y() - vect1.y()*vect2.x());

        return n.toUnit();
    }

    RVector cross(RVector const & oth) const
    {
        return RVector (((y() * oth.z()) - (z() * oth.y())),
        		 ((z() * oth.x()) - (x() * oth.z())),
        		 ((x() * oth.y()) - (y() * oth.x())));
    }

    float dot3(RVector const & oth) const
    {
    	return x() * oth.x() +
    		   y() * oth.y() +
    		   z() * oth.z();
    }

    float dot(RVector const & oth) const
    {
    	return x() * oth.x() +
    		   y() * oth.y() +
    		   z() * oth.z() +
    		   w() * oth.z();
    }

    float & operator[](int index)
    {
    	return mData[index];
    }

    const float & operator[](int index) const
    {
    	return mData[index];
    }

private:
    float mData[4];
};

}

#endif

