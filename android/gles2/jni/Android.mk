LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

COMMON_SRC := ../../../src

LOCAL_SRC_FILES := \
        $(COMMON_SRC)/gc/rgles2framebufferimpl.cpp \
        $(COMMON_SRC)/gc/rshaderobject.cpp \
        $(COMMON_SRC)/gc/rgles2gc.cpp

LOCAL_SRC_FILES += \
        $(COMMON_SRC)/android/randroidbinder.cpp \
        $(COMMON_SRC)/android/randroidlogdevice.cpp \
        $(COMMON_SRC)/android/randroidnativeadapter.cpp \
        $(COMMON_SRC)/android/randroiddataprovider.cpp \
        $(COMMON_SRC)/android/randroidassetmanager.cpp \
        \
        $(COMMON_SRC)/math/rmatrix.cpp \
        $(COMMON_SRC)/math/rtransformation.cpp \
        $(COMMON_SRC)/math/rquaternion.cpp \
        \
        $(COMMON_SRC)/ui/rspriteitem.cpp \
        $(COMMON_SRC)/ui/rlayoutitem.cpp \
        $(COMMON_SRC)/ui/rlinearlayout.cpp \
        $(COMMON_SRC)/ui/rscrollview.cpp \
        $(COMMON_SRC)/ui/rbutton.cpp \
        $(COMMON_SRC)/ui/rtoggle.cpp \
        $(COMMON_SRC)/ui/ruiitem.cpp \
        \
        $(COMMON_SRC)/gc/rbufferobject.cpp \
        $(COMMON_SRC)/gc/rframebuffer.cpp \
        $(COMMON_SRC)/gc/rgc.cpp \
        $(COMMON_SRC)/gc/rtexture.cpp \
        $(COMMON_SRC)/gc/rtextureregion.cpp \
        \
        $(COMMON_SRC)/core/rtransutils.cpp \
        $(COMMON_SRC)/core/rbeziercurve.cpp \
        $(COMMON_SRC)/core/rbinder.cpp \
        $(COMMON_SRC)/core/ranimation.cpp \
        $(COMMON_SRC)/core/rbezierparticles.cpp \
        $(COMMON_SRC)/core/rbmpimagehandler.cpp \
        $(COMMON_SRC)/core/rcamera.cpp \
        $(COMMON_SRC)/core/rcameraanimation.cpp \
        $(COMMON_SRC)/core/rcontext.cpp \
        $(COMMON_SRC)/core/rimagehandlercreator.cpp \
        $(COMMON_SRC)/core/rlinearparticles.cpp \
        $(COMMON_SRC)/core/rlog.cpp \
        $(COMMON_SRC)/core/rlightanimation.cpp \
        $(COMMON_SRC)/core/rparticles.cpp \
        $(COMMON_SRC)/core/rpngimagehandler.cpp \
        $(COMMON_SRC)/core/rshape.cpp \
        $(COMMON_SRC)/core/rshapeanimation.cpp \
        $(COMMON_SRC)/core/rsolidcube.cpp \
        $(COMMON_SRC)/core/rsolidsphere.cpp \
        $(COMMON_SRC)/core/rellipse.cpp \
        $(COMMON_SRC)/core/rtextureanimation.cpp \
        $(COMMON_SRC)/core/rtime.cpp \
        $(COMMON_SRC)/core/rtransanimation.cpp \
        $(COMMON_SRC)/core/rvelocityparticles.cpp \
        $(COMMON_SRC)/core/rview.cpp \
        \
        $(COMMON_SRC)/scene/ranimationitem.cpp \
        $(COMMON_SRC)/scene/rcameraitem.cpp \
        $(COMMON_SRC)/scene/rcameraanimationitem.cpp \
        $(COMMON_SRC)/scene/rframebufferitem.cpp \
        $(COMMON_SRC)/scene/rfrustumitem.cpp \
        $(COMMON_SRC)/scene/ritem.cpp \
        $(COMMON_SRC)/scene/ritemregister.cpp \
        $(COMMON_SRC)/scene/rlightanimationitem.cpp \
        $(COMMON_SRC)/scene/rlightitem.cpp \
        $(COMMON_SRC)/scene/rmaterialitem.cpp \
        $(COMMON_SRC)/scene/rparticleitem.cpp \
        $(COMMON_SRC)/scene/rscene.cpp \
        $(COMMON_SRC)/scene/rpropertymap.cpp \
        $(COMMON_SRC)/scene/rshapeanimationitem.cpp \
        $(COMMON_SRC)/scene/rshapeitem.cpp \
        $(COMMON_SRC)/scene/rtextureanimationitem.cpp \
        $(COMMON_SRC)/scene/rtextureitem.cpp \
        $(COMMON_SRC)/scene/rtextureregionitem.cpp \
        $(COMMON_SRC)/scene/ritemcallback.cpp \
        $(COMMON_SRC)/scene/rtransanimationitem.cpp \
        $(COMMON_SRC)/scene/rquaternionitem.cpp \
        $(COMMON_SRC)/scene/rtransformationitem.cpp \
        $(COMMON_SRC)/scene/rgcsettings.cpp \
        $(COMMON_SRC)/scene/reventmanager.cpp \
        $(COMMON_SRC)/scene/rresource.cpp \
 
LOCAL_SRC_FILES += \
        $(COMMON_SRC)/bullet/rgeometry.cpp \
        $(COMMON_SRC)/bullet/rbulletworld.cpp \
        $(COMMON_SRC)/bullet/rphysicsitem.cpp \
        $(COMMON_SRC)/bullet/rcharacteritem.cpp \
        $(COMMON_SRC)/bullet/rphysicsanimation.cpp \
        $(COMMON_SRC)/bullet/rphysicsobject.cpp \
        $(COMMON_SRC)/bullet/rphysicsanimationitem.cpp

LOCAL_SRC_FILES += \
        $(COMMON_SRC)/b2d/rb2dworld.cpp \
        $(COMMON_SRC)/b2d/rb2dbody.cpp \
        $(COMMON_SRC)/b2d/rb2dbodyitem.cpp

LOCAL_SRC_FILES += \
        $(COMMON_SRC)/chipmunk/rcpworld.cpp \
        $(COMMON_SRC)/chipmunk/rcpbody.cpp \
        $(COMMON_SRC)/chipmunk/rcpbodyitem.cpp \
        $(COMMON_SRC)/chipmunk/rcpshapeitem.cpp \
        $(COMMON_SRC)/chipmunk/rcpcollision.cpp \
        $(COMMON_SRC)/chipmunk/rcpshape.cpp

LOCAL_MODULE := libcsscene_gles2
LOCAL_CFLAGS := -DHAVE_BULLET -DRDEBUG -DGL_GLEXT_PROTOTYPES -DNO_GLUT -DR_ES2 -DHAVE_BOX2D -DHAVE_CHIPMUNK
LOCAL_CFLAGS += -I../../inc/gc -I../../inc/bullet -I../../inc/b2d -I../../inc/chipmunk \
                -I../../inc/core -I../../inc/gc  -I../../inc/math  -I../../inc/scene \
                -I../../inc/android -I../../inc/ui -I../../inc \
                -I../../external/tinyxml -I../../external/lodepng -I../../external/bullet/src  \
                -I../../external/box2d/Box2D -I../../external/box2d -I../../external/chipmunk/include

include $(BUILD_STATIC_LIBRARY)

