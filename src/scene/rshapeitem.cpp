
#include "rshapeitem.h"
#include "rmeshshape.h"
#include "rsolidcube.h"
#include "rsolidsphere.h"
#include "rrectangle.h"
#include "rresource.h"
#include "rlog.h"

namespace chikkooos
{

void RShapeItem::draw(RGc & gc) const
{
    if (!mShape.isNull()) {
        gc.draw(*mShape.data());

        if (mShadow) {
            gc.drawShadow(*mShape.data());
        }
    }
}

RItem * RShapeItem::clone()
{
    return new RShapeItem(*this);
}

void RShapeItem::setProperties(RPropertyMap const & map, std::string const & element)
{
    mShadow = map.getInt("shadow", mShadow);

    if (map.has("resource")) {
        setShape(RResource::instance()->shape(map.getInt("resource")));
    } else {
        if (element.compare("box") == 0 ||
            element.compare("cube") == 0) {
            setShape(new RSolidCube(map.getFloat("w"), map.getFloat("h"), map.getFloat("l")));
        } else if (element.compare("sphere") == 0) {
            setShape(new RSolidSphere(map.getFloat("r")));
        } else if (element.compare("rectangle") == 0) {
            float x1 = map.getFloat("x1");
            float x2 = map.getFloat("x2");
            float y1 = map.getFloat("y1");
            float y2 = map.getFloat("y2");
            setShape(new RRectangle(x1, x2, y1, y2));
        } else {
            setShape(RShapeItem::fromProperty(map));
        }
    }

    if (mShadow && !shape().isNull()) {
        shape()->createPlane();
    }
}

RShape * RShapeItem::fromProperty(RPropertyMap const & map)
{
    if (map.has("box")) {
        RVector v = map.getVector("box");
        return (new RSolidCube(v.x(), v.y(), v.z()));
    } else if (map.has("cube")) {
        RVector v = map.getVector("cube");
        return (new RSolidCube(v.x(), v.y(), v.z()));
    } else if (map.has("sphere")) {
        float v = map.getFloat("sphere");
        return (new RSolidSphere(v));
    } else if (map.has("rectangle")) {
        RVector v = map.getVector("rectangle");
        return (new RRectangle(v.x(), v.y(), v.z(), v.w()));
    } else {
        if (map.has("vertices")) {

            RMeshShape * mesh = new RMeshShape();

            std::string vertices = map.getString("vertices");
            std::string normals = map.getString("normals");
            std::string texcoords = map.getString("texcoords");
            std::string primitive = map.getString("primitive");
            std::string indices = map.getString("indices");

            float x = 0.0f;
            float y = 0.0f;
            float z = 0.0f;

            std::stringstream vs(vertices);

            while (vs >> x && vs >> y && vs >> z) {
                mesh->addVertex(x, y, z);
            }

            std::stringstream ns(normals);
            while (ns >> x && ns >> y && ns >> z) {
                mesh->addNormal(x, y, z);
            }

            std::stringstream ts(texcoords);
            while (ts >> x && ts >> y) {
                mesh->addTexCoord(x, y);
            }

            unsigned short vis;
            std::stringstream is(indices);
            while (is >> vis) {
                mesh->addIndex(vis);
            }

            GLenum glprimitive = GL_TRIANGLES;

            if (primitive.compare("points") == 0) {
                glprimitive = GL_POINTS;
            } else if (primitive.compare("lines") == 0) {
                glprimitive = GL_LINES;
            } else if (primitive.compare("line_loop") == 0) {
                glprimitive = GL_LINE_LOOP;
            } else if (primitive.compare("line_strip") == 0) {
                glprimitive = GL_LINE_STRIP;
            } else if (primitive.compare("traingles") == 0) {
                glprimitive = GL_TRIANGLES;
            } else if (primitive.compare("triangle_strip") == 0) {
                glprimitive = GL_TRIANGLE_STRIP;
            } else if (primitive.compare("triangle_fan") == 0) {
                glprimitive = GL_TRIANGLE_FAN;
            }

            mesh->setPrimitive(glprimitive);

            rLogI() << "vertices : "  << mesh->verticesCount()
                    << " normals : " << mesh->normalsCount() 
                    << " texcoords : " << mesh->texcoordsCount()
                    << " indices : " << mesh->indicesCount()
                    << " primitive : " << (primitive.empty() ? "triangles" : primitive) << std::endl;

            return mesh;
        }
    }

    return 0;
}

}

