

bin_PROGRAMS = \
				viewer

viewer_SOURCES = ../main.cpp

INCLUDES = \
           -I../../../inc/b2d \
           -I../../../inc/chipmunk \
           -I../../../external/chipmunk/include \
           -I../../../external/bullet/src -I../../../external/box2d \
           -I../../../inc -I../../jni  -I../../../inc/bullet  -I../../../inc/core \
           -I../../../inc/gc  -I../../../inc/glut  -I../../../inc/math  -I../../../inc/scene -I../../../inc/x11

LIBS = \
       -L../../../external/box2d/linux -lbox2d_@ARCH@ \
       -L../../../external/bullet/linux -lbullet_@ARCH@ \
       -L../../../external/chipmunk/linux -lchipmunk_@ARCH@ \
       -L../../../external/tinyxml/linux -ltinyxml_@ARCH@ \
       -L../../../external/lodepng/linux -llodepng_@ARCH@ \
       -L../../../linux/gles1 -lchikkooos_@ARCH@ \
       -lEGL -lX11 -lGLESv1_CM

AM_CXXFLAGS = -DGL_GLEXT_PROTOTYPES -DR_ES -DNO_GLUT

DEPS_LIBS = ../../../linux/gles1/libchikkooos_@ARCH@.a

AM_CPPFLAGS = $(DEPS_CFLAGS)
viewer_LDADD = $(DEPS_LIBS)

