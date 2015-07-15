
#ifndef SHAPE_H
#define SHAPE_H

#include "rcommon.h"
#include "rsharedobject.h"
#include "rbufferobject.h"
#include "rvector.h"

#include <vector>

namespace chikkooos
{

class RShape;

class RShapeBuffer
{
private:
    enum Index
    {
        Verticies = 0,
        Normals = 1,
        TexCoords = 2,
        Indices = 3
    };

public:
    RShapeBuffer()
     : mEmpty(true),
       mHasVertices(false),
       mHasNormals(false),
       mHasTexCoords(false),
       mHasIndices(false),
       mBuffer(4)
    {}

    RShapeBuffer(RShape & s)
     : mBuffer(4)
    {
        mEmpty = create(s);
    }

    bool create(RShape & s);

    GLuint handle(Index i)
    {
        return mBuffer.handle(i);
    }

    bool isNull() const
    {
        return mEmpty;
    }

    bool hasVertices() const
    {
        return mHasVertices;
    }

    bool hasNormals() const
    {
        return mHasNormals;
    }

    bool hasTexCoords() const
    {
        return mHasTexCoords;
    }

    bool hasIndices() const
    {
        return mHasIndices;
    }

    void bindVertices() const;
    void bindNormals() const;
    void bindTexCoords() const;
    void bindIndices() const;

    void unbind() const;

    RBufferObject buffer() const
    {
        return mBuffer;
    }

private:
    bool mEmpty;
    bool mHasVertices;
    bool mHasNormals;
    bool mHasTexCoords;
    bool mHasIndices;
    RBufferObject mBuffer;
};

class RShapePlane
{
public:
    class Plane
    {
    public:
        Plane();

        unsigned int mPointIndex[3];
        unsigned int mNeighIndex[3];
        mutable bool mVisible;
        float mCoeffA;
        float mCoeffB;
        float mCoeffC;
        float mCoeffD;
    };

public:
    RShapePlane(const RShape * s = 0)
     : mShape(s)
    {
        if (s) {
            create();
        }
    }

    bool isNull() const
    {
        return mPlanes.size() == 0;
    }

    const RShape * shape() const
    {
        return mShape;
    }

    RVector point(int index) const;

    std::vector<Plane> & planes()
    {
        return mPlanes;
    }

    const std::vector<Plane> & planes() const
    {
        return mPlanes;
    }

    Plane & at(int index)
    {
        return mPlanes[index];
    }

    const Plane & at(int index) const
    {
        return mPlanes[index];
    }

private:
    void create();
    void setConnectivity();
    void calcPlane(RShapePlane::Plane & plane);

private:
    const RShape * mShape;
    std::vector<Plane> mPlanes;
};

class RShapeData
{
public:
    void clear()
    {
        mVertices.clear();
        mNormals.clear();
        mTexCoords.clear();
        mIndices.clear();
        mBuffer = RShapeBuffer();
    }

public:
    std::vector<float> mVertices;
    std::vector<float> mNormals;
    std::vector<float> mTexCoords;
    std::vector<unsigned short> mIndices;
    RShapeBuffer mBuffer;
    RShapePlane mPlane;
};

class RShape: public RDetachableSharedObject<RShapeData>
{
public:
    virtual ~RShape()
    {}

    const float * vertices() const
    {
        return &(this->data_p().mVertices[0]);
    }

    const float * normals() const
    {
        return &(data_p().mNormals[0]);
    }

    const float * texcoords() const
    {
        return &(data_p().mTexCoords[0]);
    }

    const unsigned short * indices() const
    {
        return &(data_p().mIndices[0]);
    }

    int verticesCount() const
    {
        return data_p().mVertices.size() / 3;
    }

    int normalsCount() const
    {
        return data_p().mNormals.size() / 3;
    }

    int texcoordsCount() const
    {
        return data_p().mTexCoords.size() / 2;
    }

    int indicesCount() const
    {
        return data_p().mIndices.size();
    }

    int verticesSize() const
    {
        return data_p().mVertices.size() * sizeof(float);
    }

    int normalsSize() const
    {
        return data_p().mNormals.size() * sizeof(float);
    }

    int texcoordsSize() const
    {
        return data_p().mTexCoords.size() * sizeof(float);
    }

    int indicesSize() const
    {
        return data_p().mIndices.size() * sizeof(unsigned short);
    }

    virtual GLenum primitive() const
    {
        return GL_TRIANGLES;
    }

    const RShapeBuffer & getBuffer() const
    {
        return data_p().mBuffer;
    }

    bool hasBuffer() const
    {
        return !(data_p().mBuffer.isNull());
    }

    bool createBuffer()
    {
        return data_p().mBuffer.create(*this);
    }

    const RShapePlane & getPlane() const
    {
        return data_p().mPlane;
    }

    bool hasPlane() const
    {
        return !(data_p().mPlane.isNull());
    }

    void createPlane()
    {
        if (!hasPlane()) {
            data_p().mPlane = RShapePlane(this);
        }
    }

protected:
    void clear()
    {
        data_p().clear();
    }

    void addNormal(float x, float y, float z)
    {
        data_p().mNormals.push_back(x);
        data_p().mNormals.push_back(y);
        data_p().mNormals.push_back(z);
    }

    void addVertex(float x, float y, float z)
    {
        data_p().mVertices.push_back(x);
        data_p().mVertices.push_back(y);
        data_p().mVertices.push_back(z);
    }

    void addTexCoord(float x, float y)
    {
        data_p().mTexCoords.push_back(x);
        data_p().mTexCoords.push_back(y);
    }

    void addIndex(unsigned short i)
    {
        data_p().mIndices.push_back(i);
    }
};

}

#endif

