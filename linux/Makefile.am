
SUBDIRS = gles1 gles2

lib_LIBRARIES = libchikkooos_@ARCH@.a

libchikkooos_@ARCH@_a_SOURCES = \
    ../src/math/rtransformation.cpp \
    ../src/math/rquaternion.cpp \
    ../src/math/rmatrix.cpp \
    \
    ../src/gc/rshaderobject.cpp \
    ../src/gc/rbufferobject.cpp \
    ../src/gc/rtexture.cpp \
    ../src/gc/rtextureregion.cpp \
    \
    ../src/x11/rlinuxdataprovider.cpp \
    \
    ../src/ui/rspriteitem.cpp \
    ../src/ui/rlayoutitem.cpp \
    ../src/ui/rlinearlayout.cpp \
    ../src/ui/rscrollview.cpp \
    ../src/ui/rbutton.cpp \
    ../src/ui/rtoggle.cpp \
    ../src/ui/ruiitem.cpp \
    \
    ../src/core/rtransutils.cpp \
    ../src/core/rbeziercurve.cpp \
    ../src/core/rcommon.cpp \
    ../src/core/rcamera.cpp \
    ../src/core/rlog.cpp \
    ../src/core/rtime.cpp \
    ../src/core/rbmpimagehandler.cpp \
    ../src/core/rpngimagehandler.cpp \
    ../src/core/rimagehandlercreator.cpp \
    ../src/core/ranimation.cpp \
    ../src/core/rtransanimation.cpp \
    ../src/core/rlightanimation.cpp \
    ../src/core/rtextureanimation.cpp \
    ../src/core/rshapeanimation.cpp \
    ../src/core/rcameraanimation.cpp \
    ../src/core/rcontext.cpp \
    ../src/core/rshape.cpp \
    ../src/core/rsolidsphere.cpp \
    ../src/core/rellipse.cpp \
    ../src/core/rsolidcube.cpp \
    ../src/core/rparticles.cpp \
    ../src/core/rvelocityparticles.cpp \
    ../src/core/rlinearparticles.cpp \
    ../src/core/rbezierparticles.cpp \
    ../src/core/rbinder.cpp \
    ../src/core/rview.cpp \
    \
    ../src/gc/rgc.cpp \
    ../src/gc/rgles1gc.cpp \
    ../src/gc/rgles2gc.cpp \
    ../src/gc/rframebuffer.cpp \
    ../src/gc/rgles1framebufferimpl.cpp \
    ../src/gc/rgles2framebufferimpl.cpp \
    \
    ../src/scene/rparticleitem.cpp \
    ../src/scene/rscene.cpp \
    ../src/scene/ritemregister.cpp \
    ../src/scene/rpropertymap.cpp \
    ../src/scene/ritem.cpp \
    ../src/scene/rcameraitem.cpp \
    ../src/scene/rtransformationitem.cpp \
    ../src/scene/rlightitem.cpp \
    ../src/scene/rmaterialitem.cpp \
    ../src/scene/rfrustumitem.cpp \
    ../src/scene/rtextureitem.cpp \
    ../src/scene/rtextureregionitem.cpp \
    ../src/scene/rshapeitem.cpp \
    ../src/scene/ranimationitem.cpp \
    ../src/scene/rtransanimationitem.cpp \
    ../src/scene/rquaternionitem.cpp \
    ../src/scene/rcameraanimationitem.cpp \
    ../src/scene/rlightanimationitem.cpp \
    ../src/scene/rtextureanimationitem.cpp \
    ../src/scene/rshapeanimationitem.cpp \
    ../src/scene/rframebufferitem.cpp \
    ../src/scene/ritemcallback.cpp \
    ../src/scene/rgcsettings.cpp \
    ../src/scene/reventmanager.cpp \
    ../src/scene/rresource.cpp \
    \
    ../src/bullet/rgeometry.cpp \
    ../src/bullet/rbulletworld.cpp \
    ../src/bullet/rphysicsitem.cpp \
    ../src/bullet/rcharacteritem.cpp \
    ../src/bullet/rphysicsanimation.cpp \
    ../src/bullet/rphysicsobject.cpp \
    ../src/bullet/rphysicsanimationitem.cpp \
    \
    ../src/b2d/rb2dworld.cpp \
    ../src/b2d/rb2dbody.cpp \
    ../src/b2d/rb2dbodyitem.cpp \
    \
    ../src/chipmunk/rcpbody.cpp \
    ../src/chipmunk/rcpbodyitem.cpp \
    ../src/chipmunk/rcpworld.cpp \
    ../src/chipmunk/rcpshapeitem.cpp \
    ../src/chipmunk/rcpshape.cpp \
    ../src/chipmunk/rcpcollision.cpp \
    \
    ../src/glut/rglutbinder.cpp



INCLUDES = -I../inc \
           -I../inc/android \
           -I../inc/core \
           -I../inc/ui \
           -I../inc/bullet \
           -I../inc/b2d \
           -I../inc/chipmunk \
           -I../inc/gc \
           -I../inc/glut \
           -I../inc/math \
           -I../inc/scene \
           -I../inc/x11 \
           -I../external/tokamak/inc \
           -I../external/tinyxml \
           -I../external/lodepng \
           -I../external/bullet/src \
           -I../external/chipmunk/include \
           -I../external/box2d

LIBS = -lz -pthread -lGL -lGLU -lglut \
       -L../external/tokamak/linux -ltokamak
AM_CXXFLAGS = -DGL_GLEXT_PROTOTYPES  -DRGL_FULL

