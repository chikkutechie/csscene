
#ifndef RMESHSHAPE_H
#define RMESHSHAPE_H

#include "rshape.h"

namespace chikkooos
{

class RMeshShape: public RShape
{
public:
    RMeshShape()
     : mPrimitives(GL_TRIANGLES)
    {}

    GLenum primitive() const
    {
        return mPrimitives;
    }

    void setPrimitive(GLenum primitives)
    {
        mPrimitives = primitives;
    }

    void clear()
    {
        RShape::clear();
    }

    void addNormal(float x, float y, float z)
    {
        RShape::addNormal(x, y, z);
    }

    void addNormals(float * data, int count=3)
    {
        for (int i=0; i<count; i+=3) {
            addNormal(data[i], data[i+1], data[i+2]);
        }
    }

    void addVertex(float x, float y, float z)
    {
        RShape::addVertex(x, y, z);
    }

    void addVertices(float * data, int count=3)
    {
        for (int i=0; i<count; i+=3) {
            addVertex(data[i], data[i+1], data[i+2]);
        }
    }

    void addTexCoord(float x, float y)
    {
        RShape::addTexCoord(x, y);
    }

    void addTexCoords(float * data, int count=2)
    {
        for (int i=0; i<count; i+=2) {
            addTexCoord(data[i], data[i+1]);
        }
    }

    void addIndex(unsigned short i)
    {
        RShape::addIndex(i);
    }

    void addIndices(unsigned short * data, int count)
    {
        for (int i=0; i<count; ++i) {
            addIndex(data[i]);
        }
    }

private:
    GLenum mPrimitives;
};

}

#endif

