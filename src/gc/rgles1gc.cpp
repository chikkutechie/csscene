
#include "rcommon.h"
#include "rgles1gc.h"
#include "rlog.h"

#include <stdexcept>

namespace chikkooos
{

#if defined(R_ES)

#define RClearDepth(x) glClearDepthf(x)
#define RDepthRange(x, y) glDepthRangef(x, y)

#define glBlendEquation glBlendEquationOES

#define GL_FUNC_ADD GL_FUNC_ADD_OES
#define GL_POINT_SPRITE  GL_POINT_SPRITE_OES
#define GL_COORD_REPLACE GL_COORD_REPLACE_OES

#else

#define RClearDepth(x) glClearDepth(x)
#define RDepthRange(x, y) glDepthRange(x, y)

#endif


namespace {
static const GLenum LightNames[] = {GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3,
                                    GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};
static const unsigned int LightNamesLength = sizeof(LightNames)/sizeof(LightNames[0]);
}

RGles1Gc::RGles1Gc()
{}

RGles1Gc::~RGles1Gc()
{}

bool RGles1Gc::doInitialize()
{
    rLogI() << "RGles2Gc::doInitialize" << std::endl;

    glViewport(data_p().mViewX, data_p().mViewY,
               data_p().mViewWidth, data_p().mViewHeight);

    glClearColor(backgroundColor().r(), backgroundColor().g(),
                 backgroundColor().b(), backgroundColor().a());

    enable(GL_TEXTURE_2D);

    glDepthFunc(GL_LEQUAL);

	glShadeModel(GL_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glShadeModel(GL_SMOOTH);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, data_p().mGlobalAmbientColor.data());

    data_p().mInitialized = true;

    RCheckGLError();

    return true;
}

void RGles1Gc::draw(RParticles const & ps)
{
    if (ps.count() == 0) {
        return;
    }

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(frustum().matrix().data());

    glMatrixMode(GL_MODELVIEW);
    chikkooos::RTransformation t = camera().transformation().multiply(transformation());
    glLoadMatrixf(t.matrix().data());

    if (!data_p().mTexture.isNull()) {
        enable(GL_POINT_SPRITE);
        glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);

        bindTexture(data_p().mTexture);

        glPointSize(ps.size());

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, ps.vertices());
        glDrawArrays(GL_POINTS, 0, ps.count());

        glDisableClientState(GL_VERTEX_ARRAY);
        disable(GL_POINT_SPRITE);
        glPointSize(1.0f);
        RCheckGLError();
    }
}

void RGles1Gc::draw(RShape const & s)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (data_p().mTexture.isNull()) {
        unbindTexture();
    } else {
        drawTexture(s);
    }

    if (data_p().mLights.size() > 0) {
        drawLight(s);
    } else {
        disable(GL_LIGHTING);
    }

    if (data_p().mTexture.isNull() && !(data_p().mLights.size() > 0)) {
        drawSimple(s);
    }

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(frustum().matrix().data());

    glMatrixMode(GL_MODELVIEW);
    chikkooos::RTransformation t = camera().transformation().multiply(transformation());
    glLoadMatrixf(t.matrix().data());

    bool buffer = false;

    if (s.hasBuffer()) {
        const RShapeBuffer & sb = s.getBuffer();
        if (sb.hasVertices()) {
            sb.bindVertices();
            glVertexPointer(3, GL_FLOAT, 0, 0);
            sb.unbind();
            buffer = true;
        }
    }

    glEnableClientState(GL_VERTEX_ARRAY);

    if (!buffer) {
        glVertexPointer(3, GL_FLOAT, 0, s.vertices());
    }

    if (s.indicesCount() > 0) {
        bool indices = false;
        if (buffer) {
            const RShapeBuffer & sb = s.getBuffer();
            if (sb.hasIndices()) {
                sb.bindIndices();
                glDrawElements(s.primitive(), s.indicesCount(), GL_UNSIGNED_SHORT, 0);
                sb.unbind();
                indices = true;
            }
        }
        if (!indices) {
            glDrawElements(s.primitive(), s.indicesCount(), GL_UNSIGNED_SHORT, s.indices());
        }
    } else {
        glDrawArrays(s.primitive(), 0, s.verticesCount());
    }

    if (!data_p().mTexture.isNull()) {
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    }

    if (data_p().mLights.size() > 0) {
        glDisableClientState(GL_NORMAL_ARRAY);
        disable(GL_LIGHTING);
        for (unsigned int i=0; i < LightNamesLength; ++i) {
            disable(LightNames[i]);
        }
    }

    glDisableClientState(GL_VERTEX_ARRAY);
}

void RGles1Gc::drawSimple(RShape const & s)
{
    glColor4f(foregroundColor().r(), foregroundColor().g(),
              foregroundColor().b(), foregroundColor().a());
}

void RGles1Gc::drawTexture(RShape const & s)
{
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    bindTexture(data_p().mTexture);

    if (data_p().mTextureTransform) {
        //TODO : need to cache the value and load if required only
        glMatrixMode(GL_TEXTURE);
        glLoadMatrixf(data_p().mTextureTransform->matrix4x4());
    } else {
        //TODO : need to cache the value and load if required only
        glMatrixMode(GL_TEXTURE);
        glLoadIdentity();
    }

    bool buffer = false;
    if (s.hasBuffer()) {
        const RShapeBuffer & sb = s.getBuffer();
        if (sb.hasTexCoords()) {
            sb.bindTexCoords();
            glTexCoordPointer(2, GL_FLOAT, 0, 0);
            sb.unbind();
            buffer = true;
        }
    }

    if (!buffer) {
        glTexCoordPointer(2, GL_FLOAT, 0, s.texcoords());
    }
}

void RGles1Gc::drawLight(RShape const & s)
{
    enable(GL_LIGHTING);

    // material properties
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material().ambient().data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material().diffuse().data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material().specular().data());
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material().emissive().data());
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material().shininess());

    // lights properties
    disable(GL_NORMALIZE);

    unsigned int i = 0;
    for (LightsIter iter = data_p().mLights.begin();
            iter != data_p().mLights.end() && i < LightNamesLength;
            ++iter, ++i) {

        enable(LightNames[i]);

        const RLight &l = **iter;

        glLightfv(LightNames[i], GL_AMBIENT, l.ambient().data());
        glLightfv(LightNames[i], GL_DIFFUSE, l.diffuse().data());
        glLightfv(LightNames[i], GL_SPECULAR, l.specular().data());
        glLightfv(LightNames[i], GL_POSITION, l.position().data());

        if (!(*iter)->isDirectionLight()) {
            if ((*iter)->isSpotLight()) {
                glLightfv(LightNames[i], GL_SPOT_DIRECTION, l.direction().data());
                glLightf(LightNames[i], GL_SPOT_EXPONENT, l.spotExponent());
                glLightf(LightNames[i], GL_SPOT_CUTOFF, l.spotCutoff());
            }
            // spot light and point light
            glLightf(LightNames[i], GL_CONSTANT_ATTENUATION, l.constAttenuation());
            glLightf(LightNames[i], GL_LINEAR_ATTENUATION, l.linearAttenuation());
            glLightf(LightNames[i], GL_QUADRATIC_ATTENUATION, l.quadAttenuation());
        }
    }

    // load normals
    glEnableClientState(GL_NORMAL_ARRAY);

    bool buffer = false;
    if (s.hasBuffer()) {
        const RShapeBuffer & sb = s.getBuffer();
        if (sb.hasNormals()) {
            sb.bindNormals();
            glNormalPointer(GL_FLOAT, 0, 0);
            sb.unbind();
            buffer = true;
        }
    }

    if (!buffer) {
        glNormalPointer(GL_FLOAT, 0, s.normals());
    }
}

void RGles1Gc::drawShadow(RShape const & s)
{
    if (s.hasPlane()) {
        const RShapePlane & sp = s.getPlane();
        if (!sp.isNull()) {
            unsigned int i=0;
            for (LightsIter iter = data_p().mLights.begin();
                iter != data_p().mLights.end() && i < LightNamesLength;
                ++iter, ++i) {
                drawShadow(sp, (*iter)->position());
            }
        }
    }
}

void RGles1Gc::drawShadow(const RShapePlane & s, RVector const & lp)
{
    unsigned int    i, j, k, jj;
    unsigned int    p1, p2;
    RVector         v1, v2;
    float           side;

    enable(GL_POLYGON_OFFSET_FACTOR);
    enable(GL_POLYGON_OFFSET_UNITS);
    enable(GL_POLYGON_OFFSET_FILL);

    glPolygonOffset(-1.0f, -1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(frustum().matrix().data());

    glMatrixMode(GL_MODELVIEW);
    chikkooos::RTransformation t = camera().transformation().multiply(transformation());
    glLoadMatrixf(t.matrix().data());

    //set visual parameter
    for (i=0; i<s.planes().size(); i++) {
        const RShapePlane::Plane & plane = s.at(i);
        side =  plane.mCoeffA*lp.x()+
                plane.mCoeffB*lp.y()+
                plane.mCoeffC*lp.z()+
                plane.mCoeffD*lp.w();
        if (side >0) {
            plane.mVisible = true;
        } else {
            plane.mVisible = false;
        }
    }

    disable(GL_LIGHTING);
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);

    enable(GL_STENCIL_TEST);
    glColorMask(0, 0, 0, 0);
    glStencilFunc(GL_ALWAYS, 1, 0xffffffff);

    // first pass, stencil operation decreases stencil value
    glFrontFace(GL_CCW);
    glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);

    for (i=0; i<s.planes().size();i++) {
        const RShapePlane::Plane & plane = s.at(i);
        if (plane.mVisible) {
            for (j=0;j<3;j++) {
                k = plane.mNeighIndex[j];
                if ((!k) || (!s.at(k-1).mVisible)) {
                    p1 = plane.mPointIndex[j];
                    jj = (j+1)%3;
                    p2 = plane.mPointIndex[jj];

                    v1.setX((s.point(p1).x() - lp.x())*100.0f);
                    v1.setY((s.point(p1).y() - lp.y())*100.0f);
                    v1.setZ((s.point(p1).z() - lp.z())*100.0f);

                    v2.setX((s.point(p2).x() - lp.x())*100.0f);
                    v2.setY((s.point(p2).y() - lp.y())*100.0f);
                    v2.setZ((s.point(p2).z() - lp.z())*100.0f);

                    float vertices[] = {
                        s.point(p1).x(), s.point(p1).y(), s.point(p1).z(),
                        s.point(p1).x() + v1.x(), s.point(p1).y() + v1.y(), s.point(p1).z() + v1.z(),
                        s.point(p2).x(), s.point(p2).y(), s.point(p2).z(),
                        s.point(p2).x() + v2.x(), s.point(p2).y() + v2.y(), s.point(p2).z() + v2.z()
                    };

                    glEnableClientState(GL_VERTEX_ARRAY);
                    glVertexPointer(3, GL_FLOAT, 0, vertices);
                    glDrawArrays(GL_TRIANGLE_STRIP, 0, (sizeof(vertices)/sizeof(vertices[0]))/3);
                    glDisableClientState(GL_VERTEX_ARRAY);
                }
            }
        }
    }

    glFrontFace(GL_CW);
    glStencilOp(GL_KEEP, GL_KEEP, GL_DECR);

    for (i=0; i<s.planes().size();i++){
        const RShapePlane::Plane & plane = s.at(i);
        if (plane.mVisible) {
            for (j=0;j<3;j++){
                k = plane.mNeighIndex[j];
                if ((!k) || (!s.at(k-1).mVisible)){
                    p1 = plane.mPointIndex[j];
                    jj = (j+1)%3;
                    p2 = plane.mPointIndex[jj];

                    v1.setX((s.point(p1).x() - lp.x())*100.0f);
                    v1.setY((s.point(p1).y() - lp.y())*100.0f);
                    v1.setZ((s.point(p1).z() - lp.z())*100.0f);

                    v2.setX((s.point(p2).x() - lp.x())*100.0f);
                    v2.setY((s.point(p2).y() - lp.y())*100.0f);
                    v2.setZ((s.point(p2).z() - lp.z())*100.0f);

                    float vertices[] = {
                        s.point(p1).x(),
                        s.point(p1).y(),
                        s.point(p1).z(),
                        s.point(p1).x() + v1.x(),
                        s.point(p1).y() + v1.y(),
                        s.point(p1).z() + v1.z(),
                        s.point(p2).x(),
                        s.point(p2).y(),
                        s.point(p2).z(),
                        s.point(p2).x() + v2.x(),
                        s.point(p2).y() + v2.y(),
                        s.point(p2).z() + v2.z()
                    };
                    glEnableClientState(GL_VERTEX_ARRAY);
                    glVertexPointer(3, GL_FLOAT, 0, vertices);
                    glDrawArrays(GL_TRIANGLE_STRIP, 0, (sizeof(vertices)/sizeof(vertices[0]))/3);
                    glDisableClientState(GL_VERTEX_ARRAY);
                }
            }
        }
    }

    glFrontFace(GL_CCW);
    glColorMask(1, 1, 1, 1);

    glColor4f(0.0f, 0.0f, 0.0f, 0.4f);
    enable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glStencilFunc(GL_NOTEQUAL, 0, 0xffffffff);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    glPushMatrix();
    glLoadIdentity();

    float vertices[] = {
        -0.1f, 0.1f,-0.10f,
        -0.1f,-0.1f,-0.10f,
         0.1f, 0.1f,-0.10f,
         0.1f,-0.1f,-0.10f
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (sizeof(vertices)/sizeof(vertices[0]))/3);
    glDisableClientState(GL_VERTEX_ARRAY);

    glPopMatrix();
    disable(GL_BLEND);

    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);
    disable(GL_STENCIL_TEST);
    glShadeModel(GL_SMOOTH);

    disable(GL_POLYGON_OFFSET_FACTOR);
    disable(GL_POLYGON_OFFSET_UNITS);
    disable(GL_POLYGON_OFFSET_FILL);
}

}

