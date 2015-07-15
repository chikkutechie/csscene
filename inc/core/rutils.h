
#ifndef UITLS_H
#define UITLS_H

#include <cmath>

namespace chikkooos
{

#define MATH_DEG_TO_RAD(x)          ((x) * 0.0174532925f)
#define MATH_RAD_TO_DEG(x)          ((x)* 57.29577951f)
#define MATH_RANDOM_MINUS1_1()      ((2.0f*((float)rand()/RAND_MAX))-1.0f)      // Returns a random float between -1 and 1.
#define MATH_RANDOM_0_1()           ((float)rand()/RAND_MAX)                    // Returns a random float between 0 and 1.
#define MATH_FLOAT_SMALL            1.0e-37f
#define MATH_TOLERANCE              2e-37f
#define MATH_E                      2.71828182845904523536f
#define MATH_LOG10E                 0.4342944819032518f
#define MATH_LOG2E                  1.442695040888963387f
#define MATH_PI                     3.14159265358979323846f
#define MATH_PIOVER2                1.57079632679489661923f
#define MATH_PIOVER4                0.785398163397448309616f
#define MATH_PIX2                   6.28318530717958647693f
#define MATH_EPSILON                0.000001f
#define MATH_CLAMP(x, lo, hi)       ((x < lo) ? lo : ((x > hi) ? hi : x))
#ifndef M_1_PI
#define M_1_PI                      0.31830988618379067154
#endif


inline bool fcompare(float v1, float v2)
{
	if (fabs(v1-v2) < MATH_EPSILON) {
		return true;
	}

	return false;
}

template <typename T>
class RSize
{
public:
    RSize()
     : mWidth(0),
       mHeight(0)
    {}

    RSize(const T & width, const T & height)
     : mWidth(width),
       mHeight(height)
    {}

    void setWidth(const T & width)
    {
        mWidth = width;
    }

    T width() const
    {
        return mWidth;
    }

    void setHeight(const T & height)
    {
        mHeight = height;
    }

    T height() const
    {
        return mHeight;
    }

    bool isNull()
    {
        return mWidth == 0 || mHeight = 0;
    }

private:
    T mWidth;
    T mHeight;
};

typedef RSize<int> RSizeI;
typedef RSize<unsigned int> RSizeUI;
typedef RSize<float> RSizeF;

template <typename T>
class RRectType
{
public:
    RRectType()
    {}

    RRectType(T x1, T y1, T x2, T y2)
     : mX1(x1),
       mY1(y1),
       mX2(x2),
       mY2(y2)
    {
    }

    bool isEmpty() const {return ((width() == 0) | (height() == 0));}

    T x1() const {return mX1;}
    T y1() const {return mY1;}
    T x2() const {return mX2;}
    T y2() const {return mY2;}

    void setX1(T v) {mX1 = v;}
    void setY1(T v) {mY1 = v;}
    void setX2(T v) {mX2 = v;}
    void setY2(T v) {mY2 = v;}

    T height() const {return mY2-mY1;}
    T width() const {return mX2-mX1;}

private:
    T mX1;
    T mY1;
    T mX2;
    T mY2;
};

typedef RRectType<int> RRectTypeI;
typedef RRectType<unsigned int> RRectTypeUI;
typedef RRectType<float> RRectTypeF;

}

#endif

