
#ifndef CUBE_H
#define CUBE_H

#include "rshape.h"

#include <vector>

namespace chikkooos
{

class RSolidCube: public RShape
{
public:
    RSolidCube(float w=1.0f, float h=1.0f, float l=1.0f)
    {
        create(w, h, l);
    }

    void set(float w, float h, float l)
    {
        create(w, h, l);
    }

    float width() const
    {
        return mWidth;
    }
    float height() const
    {
        return mHeight;
    }
    float length() const
    {
        return mLength;
    }

private:
    void create(float w, float h, float l);

private:
    float mWidth;
    float mHeight;
    float mLength;
};

}

#endif

