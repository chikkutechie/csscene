
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
       -L../../external/box2d/Box2D/linux -lbox2d \
       -L../../external/bullet/linux -lbullet \
       -L../../external/chipmunk/linux -lchipmunk \
       -L../../external/tinyxml/linux -ltinyxml \
       -L../../external/lodepng/linux -llodepng \
       -L../../linux -lchikkooos \
       -lGL -lGLU -lglut -lEGL

CXXFLAGS = -g3 -Wall -DGL_GLEXT_PROTOTYPES

CFLAGS = -g3 -Wall

LDFLAGS = -g3

DEPS_LIBS = ../../linux/libchikkooos.a

CPPFLAGS = $(DEPS_CFLAGS)

viewer_LDADD = $(DEPS_LIBS)

