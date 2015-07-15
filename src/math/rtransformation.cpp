
#include "rtransformation.h"

namespace chikkooos
{

void RTransformation::push()
{
    if (data_p().mMatrixStack.empty()) {
        data_p().mMatrixStack.push(RMatrix());
    } else {
        data_p().mMatrixStack.push(data_p().mMatrixStack.top());
    }
}

RTransformation RTransformation::multiply(RTransformation const & t) const
{
    return multiply(t.matrix());
}

RTransformation RTransformation::multiply(RMatrix const & m) const
{
    RTransformation result;
    result.matrix() = matrix() * m;
    return result;
}

RTransformation RTransformation::inverse() const
{
    RTransformation r;
    RMatrix m = matrix().inverse();
    r.load(m);
    return r;
}

RTransformation RTransformation::invertTranspose() const
{
    RTransformation r;
    RMatrix m = matrix().invertTranspose();
    r.load(m);
    return r;
}

RTransformation RTransformation::transpose() const
{
    RTransformation r;
    
    RMatrix m = matrix().transpose();
    r.load(m);

    return r;
}

void RTransformation::translate(float tx, float ty, float tz)
{
    matrix().translate(tx, ty, tz);
}

void RTransformation::rotate(float angle, float ax, float ay, float az)
{
	matrix().rotate(RVector(ax, ay, az), angle);
}

void RTransformation::scale(float sx, float sy, float sz)
{
    matrix().scale(sx, sy, sz);
}

}
