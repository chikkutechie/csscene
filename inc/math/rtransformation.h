
#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "rcommon.h"
#include "rsharedobject.h"
#include "rvector.h"
#include "rmatrix.h"
#include "rfrustum.h"

#include <cstring>
#include <cmath>
#include <stack>

namespace chikkooos
{

class RTransformationData
{
public:
    typedef std::stack<RMatrix> MatrixStack;

    MatrixStack mMatrixStack;
};

class RTransformation: public RDetachableSharedObject<RTransformationData>
{
private:
    typedef RTransformationData::MatrixStack MatrixStack;

public:
    RTransformation()
    {
        push();
    }

    RTransformation(RMatrix const & m)
    {
        push();
        load(m);
    }

    RTransformation(RFrustum const & f)
    {
        push();
        load(f.matrix());
    }

    const RMatrix & matrix() const
    {
        return data_p().mMatrixStack.top();
    }

    RMatrix & matrix()
    {
        return data_p().mMatrixStack.top();
    }

    void load(RMatrix const & m)
    {
        matrix() = m;
    }

    void push();

    void pop()
    {
        data_p().mMatrixStack.pop();
    }

    void reset()
    {
        data_p().mMatrixStack.top().reset();
    }

    RTransformation multiply(RTransformation const & t) const;

    RTransformation multiply(RMatrix const & m) const;

    RVector multiply(float x, float y, float z, float w=1.0f) const
    {
        return multiply(RVector(x, y, z, w));
    }

    RVector multiply(RVector const & p) const
    {
        return matrix().multiply(p);
    }

    RTransformation inverse() const;

    RTransformation invertTranspose() const;

    RTransformation transpose() const;

    void translate(float tx, float ty, float tz);

    void rotate(float angle, float x, float y, float z);

    void scale(float sx, float sy, float sz);
};

}

#endif

