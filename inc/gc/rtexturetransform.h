
#ifndef RTEXTURETRANSFORM_H
#define RTEXTURETRANSFORM_H

namespace chikkooos
{

class RTextureTransform
{
public:
    virtual ~RTextureTransform()
    {}

    virtual const float * matrix3x3() const = 0;
    virtual const float * matrix4x4() const = 0;

    virtual bool isIdentity() const = 0;
};

}

#endif
