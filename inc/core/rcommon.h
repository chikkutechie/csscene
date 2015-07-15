
#ifndef RCOMMON_H
#define RCOMMON_H

#ifdef NO_GLUT
#else
#if defined(R_ES) || defined(R_ES2)
#include <glut.h>
#else
#if defined(WIN32) || defined(WIN64)
#include <GL/glew.h>
#endif
#include <GL/glut.h>
#endif
#endif

#if defined(R_ES2)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#elif defined(R_ES)
#include <GLES/gl.h>
#include <GLES/glext.h>
#endif

#include <math.h>
#include <string>
#include <iostream>
#include <iomanip>

#ifndef PACKAGE
#define PACKAGE "chikkooos"
#endif

#ifndef PACKAGE_NAME
#define PACKAGE_NAME "chikkooos"
#endif

#include "rsmartpointer.h"
#include "rvector.h"

namespace chikkooos
{

static const float Epsilon = 0.000001f;

static const int WindowPositionX = 100;
static const int WindowPositionY = 100;

static const int WindowWidth = 480;
static const int WindowHeight = 800;

static const unsigned int TimerDelay = 20;

inline float radToDeg(float x)
{
    return ((x)* 57.29577951f);
}

inline float degToRad(float x)
{
    return ((x) * 0.0174532925f);
}

inline std::string glErrorToString(GLenum code)
{
    std::string errorstr;

    switch (code) {
        case 0x0:
        errorstr = "GL_NO_ERROR";
        break;

        case 0x0500:
        errorstr = "GL_INVALID_ENUM";
        break;

        case 0x0501:
        errorstr = "GL_INVALID_VALUE";
        break;

        case 0x0502:
        errorstr = "GL_INVALID_OPERATION";
        break;

        case 0x0503:
        errorstr = "GL_STACK_OVERFLOW";
        break;

        case 0x0504:
        errorstr = "GL_STACK_UNDERFLOW";
        break;

        case 0x0505:
        errorstr = "GL_OUT_OF_MEMORY";
        break;
    }

    return errorstr;
}

}

#if defined(RGLERRORTRACE)
#define RCheckGLError() do { \
                            GLenum error = glGetError(); \
                            if (error != GL_NO_ERROR) { \
                                rLogE() << "glGetError() : " << chikkooos::glErrorToString(error) << "(" << error << ")" << std::endl; \
                            } \
                        } while (0)

#else
#define RCheckGLError()
#endif


#endif

