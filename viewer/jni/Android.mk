
LOCAL_PATH := $(call my-dir)

HAVE_BULLET := 1
HAVE_BOX2D := 1
HAVE_CHIPMUNK := 1

#
# Build the prebuilt static libraries
#

include $(CLEAR_VARS)
LOCAL_MODULE := libbullet
LOCAL_SRC_FILES := \
                   ../../external/bullet/android/$(TARGET_ARCH_ABI)/libbullet.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libbox2d
LOCAL_SRC_FILES := \
                   ../../external/box2d/android/$(TARGET_ARCH_ABI)/libbox2d.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libchipmunk
LOCAL_SRC_FILES := \
                   ../../external/chipmunk/android/$(TARGET_ARCH_ABI)/libchipmunk.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := liblodepng
LOCAL_SRC_FILES := \
                   ../../external/lodepng/android/$(TARGET_ARCH_ABI)/liblodepng.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libtinyxml
LOCAL_SRC_FILES := \
                   ../../external/tinyxml/android/$(TARGET_ARCH_ABI)/libtinyxml.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libcsscenegles1
LOCAL_STATIC_LIBRARIES := lodepng bullet box2d tinyxml chipmunk
LOCAL_SRC_FILES := \
                   ../../android/gles1/obj/local/$(TARGET_ARCH_ABI)/libcsscene_gles1.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libcsscenegles2
LOCAL_STATIC_LIBRARIES := lodepng bullet box2d tinyxml chipmunk
LOCAL_SRC_FILES := \
                   ../../android/gles2/obj/local/$(TARGET_ARCH_ABI)/libcsscene_gles2.a
include $(PREBUILT_STATIC_LIBRARY)

######################################
#  Build the gles1 library           #
######################################

include $(CLEAR_VARS)

LOCAL_SRC_FILES := main.cpp

LOCAL_MODULE    := libviewergles1

LOCAL_CFLAGS := -DHAVE_BULLET -DRDEBUG -DGL_GLEXT_PROTOTYPES -DNO_GLUT -DR_ES -DHAVE_BOX2D -DHAVE_CHIPMUNK
LOCAL_CFLAGS += -I../external/tinyxml -I. -I../inc -I../external/lodepng -I../external/bullet/src  \
                -I../external/box2d/Box2D -I../external/box2d -I../external/chipmunk/include \
                -I../inc/bullet -I../inc/b2d -I../inc/chipmunk -I../inc/core -I../inc/gc  -I../inc/math  -I../inc/scene -I../inc/android -I../inc/ui

LOCAL_STATIC_LIBRARIES := csscenegles1 tinyxml lodepng bullet box2d chipmunk

LOCAL_LDLIBS := -llog -lGLESv1_CM -landroid

include $(BUILD_SHARED_LIBRARY)

######################################
#  Build the gles2 library           #
######################################

include $(CLEAR_VARS)

LOCAL_SRC_FILES := main.cpp

LOCAL_MODULE    := libviewergles2

LOCAL_CFLAGS := -DHAVE_BULLET -DRDEBUG -DGL_GLEXT_PROTOTYPES -DNO_GLUT -DR_ES2 -DHAVE_BOX2D -DHAVE_CHIPMUNK
LOCAL_CFLAGS += -I../external/tinyxml -I. -I../inc -I../external/lodepng -I../external/bullet/src \
                -I../external/box2d/Box2D -I../external/box2d -I../external/chipmunk/include \
                -I../inc/bullet -I../inc/b2d -I../inc/chipmunk -I../inc/core -I../inc/gc  -I../inc/math  -I../inc/scene -I../inc/android -I../inc/ui

LOCAL_STATIC_LIBRARIES := csscenegles2 tinyxml lodepng bullet box2d chipmunk
LOCAL_LDLIBS := \
               -llog -lGLESv2 -landroid

include $(BUILD_SHARED_LIBRARY)


