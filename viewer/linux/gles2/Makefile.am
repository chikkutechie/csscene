

bin_PROGRAMS = \
				viewer

viewer_SOURCES = ../main.cpp

INCLUDES = \
           -I../../../inc/b2d \
           -I../../../inc/chipmunk \
           -I../../../external/bullet/src -I../../../external/box2d \
           -I../../../external/chipmunk/include \
           -I../../../inc -I../../jni  -I../../../inc/bullet \
           -I../../../inc/core -I../../../inc/gc  -I../../../inc/glut \
           -I../../../inc/math  -I../../../inc/scene -I../../../inc/x11

LIBS = \
       -L../../../external/box2d/linux -lbox2d_@ARCH@ \
       -L../../../external/bullet/linux -lbullet_@ARCH@ \
       -L../../../external/chipmunk/linux -lchipmunk_@ARCH@ \
       -L../../../external/tinyxml/linux -ltinyxml_@ARCH@ \
       -L../../../external/lodepng/linux -llodepng_@ARCH@ \
       -L../../../linux/gles2 -lchikkooos_@ARCH@ \
       -lEGL -lX11 -lGLESv2
AM_CXXFLAGS = -g3 -Wall -DGL_GLEXT_PROTOTYPES -DR_ES2 -DNO_GLUT

DEPS_LIBS = ../../../linux/gles2/libchikkooos_@ARCH@.a

AM_CPPFLAGS = $(DEPS_CFLAGS)
viewer_LDADD = $(DEPS_LIBS)

