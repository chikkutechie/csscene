
#include <android/log.h>
#include <jni.h>
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include "rviewer.h"
#include "randroidbinder.h"
#include "rview.h"
#include "randroidassetmanager.h"
#include "rcontext.h"

static std::string SceneFileName = "data/physics.xml";
chikkooos::ViewerRenderer * vr = 0;

extern "C" {
    JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_main(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_chikkooos_android_viewer_ViewerJNILib_setSceneFile(JNIEnv * env, jobject obj, jstring scenefilename);
};

JNIEXPORT void JNICALL Java_com_chikkooos_android_viewer_ViewerJNILib_setSceneFile(JNIEnv * env, jobject obj, jstring filename)
{
    const char *utf8 = env->GetStringUTFChars(filename, 0);
    if (utf8 != 0) {
        SceneFileName = utf8;
        if (vr) {
            vr->setSceneMap(SceneFileName);
        }
        env->ReleaseStringUTFChars(filename, utf8);
    }
}

JNIEXPORT void JNICALL Java_com_chikkooos_android_common_GL2JNILib_main(JNIEnv * env, jobject obj)
{
    static bool initialized = false;
    if (!initialized) {
        chikkooos::RBinder & binder = chikkooos::RBinder::instance();
        vr = new chikkooos::ViewerRenderer();
        vr->setSceneMap(SceneFileName);
        binder.setRenderer(vr);

        if (!binder.initialize()) {
        	rLogE() << "scene initialization failed" << std::endl;
            return;
        }
        rLogI() << "scene initialized" << std::endl;

        initialized = true;
    }
}

