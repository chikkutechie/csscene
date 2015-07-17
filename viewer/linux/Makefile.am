
SUBDIRS = gles1 gles2

bin_PROGRAMS = \
				viewer

viewer_SOURCES = main.cpp

INCLUDES = \
           -I../../inc/b2d \
           -I../../inc/chipmunk \
           -I../../inc -I../jni  -I../../inc/bullet  -I../../inc/core -I../../inc/gc \
           -I../../inc/glut  -I../../inc/math  -I../../inc/scene -I../../inc/x11 \
           -I../../external/bullet/src \
           -I../../external/box2d \
           -I../../external/chipmunk/include

LIBS = \
       -L../../external/box2d/Box2D/linux -lbox2d_@ARCH@ \
       -L../../external/bullet/linux -lbullet_@ARCH@ \
       -L../../external/chipmunk/linux -lchipmunk_@ARCH@ \
       -L../../external/tinyxml/linux -ltinyxml_@ARCH@ \
       -L../../external/lodepng/linux -llodepng_@ARCH@ \
       -L../../linux -lchikkooos_@ARCH@ \
       -lGL -lGLU -lglut -lEGL

AM_CXXFLAGS = -DGL_GLEXT_PROTOTYPES

DEPS_LIBS = ../../linux/libchikkooos_@ARCH@.a

AM_CPPFLAGS = $(DEPS_CFLAGS)

viewer_LDADD = $(DEPS_LIBS)

