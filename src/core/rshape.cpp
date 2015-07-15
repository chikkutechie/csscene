
#include "rshape.h"
#include "rlog.h"
#include <cstdlib>

namespace chikkooos
{

bool RShapeBuffer::create(RShape & s)
{
    mEmpty = true;
    mHasVertices = false;
    mHasNormals = false;
    mHasTexCoords = false;
    mHasIndices = false;

    if (s.verticesSize() > 0) {
        if (mBuffer.set(s.verticesSize(), s.vertices(), Verticies)) {
            mEmpty = false;
            mHasVertices = true;
        } else {
            rLogE() << "creating vertex buffer failed" << std::endl;
        }
    }

    if (s.normalsSize() > 0) {
        if (mBuffer.set(s.normalsSize(), s.normals(), Normals)) {
            mEmpty = false;
            mHasNormals = true;
        } else {
            rLogE() << "creating normal buffer failed" << std::endl;
        }
    }

    if (s.texcoordsSize() > 0) {
        if (mBuffer.set(s.texcoordsSize(), s.texcoords(), TexCoords)) {
            mEmpty = false;
            mHasTexCoords = true;
        } else {
            rLogE() << "creating tex coord buffer failed" << std::endl;
        }
    }

    if (s.indicesSize() > 0) {
        if (mBuffer.set(s.indicesSize(), s.indices(), Indices, GL_ELEMENT_ARRAY_BUFFER)) {
            mEmpty = false;
            mHasIndices = true;
        } else {
            rLogE() << "creating index buffer failed" << std::endl;
        }
    }

    return mEmpty;
}

void RShapeBuffer::bindVertices() const
{
    mBuffer.bind(Verticies);
}

void RShapeBuffer::bindNormals() const
{
    mBuffer.bind(Normals);
}

void RShapeBuffer::bindTexCoords() const
{
    mBuffer.bind(TexCoords);
}

void RShapeBuffer::bindIndices() const
{
    mBuffer.bind(Indices, GL_ELEMENT_ARRAY_BUFFER);
}

void RShapeBuffer::unbind() const
{
    mBuffer.unbind();
    mBuffer.unbind(GL_ELEMENT_ARRAY_BUFFER);
}

RShapePlane::Plane::Plane()
{
    mPointIndex[0] = 0;
    mPointIndex[1] = 0;
    mPointIndex[2] = 0;
    mNeighIndex[0] = 0;
    mNeighIndex[1] = 0;
    mNeighIndex[2] = 0;
    mVisible = false;
    mCoeffA = 0.0f;
    mCoeffB = 0.0f;
    mCoeffC = 0.0f;
    mCoeffD = 0.0f;
}

void RShapePlane::create()
{
    if (mShape->primitive() != GL_TRIANGLES) {
        return;
    }

    mPlanes.clear();

    int iCount = mShape->indicesCount();
    if (iCount > 0) {
        for (int i=0; i<iCount; i += 3) {
            Plane p;
            p.mPointIndex[0] = mShape->indices()[i+0];
            p.mPointIndex[1] = mShape->indices()[i+1];
            p.mPointIndex[2] = mShape->indices()[i+2];
            mPlanes.push_back(p);
        }
    } else {
        for (int i=0; i<mShape->verticesCount(); i+=3) {
            Plane p;
            p.mPointIndex[0] = i+0;
            p.mPointIndex[1] = i+1;
            p.mPointIndex[2] = i+2;
            mPlanes.push_back(p);
        }
    }

    setConnectivity();

    for (unsigned int i=0; i<mPlanes.size(); ++i) {
        calcPlane(mPlanes[i]);
    }
}

void RShapePlane::setConnectivity()
{
    int p1i, p2i, p1j, p2j;
    int P1i, P2i, P1j, P2j;
    int i,j,ki,kj;

    for(i=0; i<(int)mPlanes.size()-1; i++) {
        for(j=i+1; j<(int)mPlanes.size(); j++) {
            for(ki=0; ki<3; ki++) {
                if(!mPlanes[i].mNeighIndex[ki]) {
                    for(kj=0;kj<3;kj++) {
                        p1i=ki;
                        p1j=kj;
                        p2i=(ki+1)%3;
                        p2j=(kj+1)%3;

                        p1i=mPlanes[i].mPointIndex[p1i];
                        p2i=mPlanes[i].mPointIndex[p2i];
                        p1j=mPlanes[j].mPointIndex[p1j];
                        p2j=mPlanes[j].mPointIndex[p2j];

                        P1i=((p1i+p2i)-std::abs(p1i-p2i))/2;
                        P2i=((p1i+p2i)+std::abs(p1i-p2i))/2;
                        P1j=((p1j+p2j)-std::abs(p1j-p2j))/2;
                        P2j=((p1j+p2j)+std::abs(p1j-p2j))/2;

                        if((P1i==P1j) && (P2i==P2j)) {
                            mPlanes[i].mNeighIndex[ki] = j+1;     
                            mPlanes[j].mNeighIndex[kj] = i+1;     
                        }
                    }
                }
            }
        }
    }
}

RVector RShapePlane::point(int index) const
{
    const float * p = mShape->vertices() + (3*index);
    return RVector(p[0], p[1], p[2]);
}

void RShapePlane::calcPlane(RShapePlane::Plane & plane)
{
    RVector v[4];

    for (int i=0; i<3; i++) {
        v[i+1] = point(plane.mPointIndex[i]);
    }

    plane.mCoeffA = v[1].y()*(v[2].z()-v[3].z()) + v[2].y()*(v[3].z()-v[1].z()) + v[3].y()*(v[1].z()-v[2].z());
    plane.mCoeffB = v[1].z()*(v[2].x()-v[3].x()) + v[2].z()*(v[3].x()-v[1].x()) + v[3].z()*(v[1].x()-v[2].x());
    plane.mCoeffC = v[1].x()*(v[2].y()-v[3].y()) + v[2].x()*(v[3].y()-v[1].y()) + v[3].x()*(v[1].y()-v[2].y());
    plane.mCoeffD =-(v[1].x()*(v[2].y()*v[3].z() - v[3].y()*v[2].z()) +
                      v[2].x()*(v[3].y()*v[1].z() - v[1].y()*v[3].z()) +
                      v[3].x()*(v[1].y()*v[2].z() - v[2].y()*v[1].z()));
}


}

