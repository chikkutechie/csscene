
#include <android/log.h>
#include <jni.h>
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <jni.h>

#include "randroidbinder.h"
#include "randroidassetmanager.h"
#include "rview.h"

extern "C" {
    JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height);

    JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_step(JNIEnv * env, jobject obj);

    JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_setAssetManager(JNIEnv * env, jobject obj, jobject assetManager);

    JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_swipeLeftToRight(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_swipeRightToLeft(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_swipeTopToBottom(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_swipeBottomToTop(JNIEnv * env, jobject obj);

    JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_singleTap(JNIEnv * env, jobject obj, jint width, jint height);
    JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_doubleTap(JNIEnv * env, jobject obj, jint width, jint height);

    JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_touchDown(JNIEnv * env, jobject obj, jint x, jint y);
    JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_touchUp(JNIEnv * env, jobject obj, jint x, jint y);

    JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_touchScroll(JNIEnv * env, jobject obj, jint x, jint y);

    JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_keyEvent(JNIEnv * env, jobject obj, jint key   , jint x, jint y);

    JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_pause(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_resume(JNIEnv * env, jobject obj);

};

JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
    chikkooos::RAndroidBinder::reshape(width, height);
}

JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_step(JNIEnv * env, jobject obj)
{
    chikkooos::RAndroidBinder::timer(0);
    chikkooos::RAndroidBinder::display();
}

JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_setAssetManager(JNIEnv * env, jobject obj, jobject assetManager)
{
	AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
	chikkooos::RAndroidAssetManager::setAssetManager(mgr);
}

JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_swipeLeftToRight(JNIEnv * env, jobject obj)
{
    chikkooos::RBinder::instance().swipeLeftToRight();
}

JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_swipeRightToLeft(JNIEnv * env, jobject obj)
{
    chikkooos::RBinder::instance().swipeRightToLeft();
}

JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_swipeTopToBottom(JNIEnv * env, jobject obj)
{
    chikkooos::RBinder::instance().swipeTopToBottom();
}

JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_swipeBottomToTop(JNIEnv * env, jobject obj)
{
    chikkooos::RBinder::instance().swipeBottomToTop();
}

JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_singleTap(JNIEnv * env, jobject obj, jint x, jint y)
{
    chikkooos::RBinder::instance().singleTap(x, y);
}

JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_doubleTap(JNIEnv * env, jobject obj, jint x, jint y)
{
    chikkooos::RBinder::instance().doubleTap(x, y);
}

JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_touchDown(JNIEnv * env, jobject obj, jint x, jint y)
{
    chikkooos::RBinder::instance().touchDown(x, y);
}

JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_touchUp(JNIEnv * env, jobject obj, jint x, jint y)
{
    chikkooos::RBinder::instance().touchUp(x, y);
}


JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_touchScroll(JNIEnv * env, jobject obj, jint x, jint y)
{
    chikkooos::RBinder::instance().touchScroll(x, y);
}

JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_keyEvent(JNIEnv * env, jobject obj, jint key   , jint x, jint y)
{
    chikkooos::RBinder::instance().keyPress(key, x, y);
}

JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_pause(JNIEnv * env, jobject obj)
{
    chikkooos::RBinder::instance().pause();
}

JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_resume(JNIEnv * env, jobject obj)
{
    chikkooos::RBinder::instance().resume();
}

