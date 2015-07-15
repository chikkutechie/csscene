
#ifndef RVIEWERASSETMANAGER_H
#define RVIEWERASSETMANAGER_H

#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

namespace chikkooos
{

class RAndroidAssetManager
{
public:
    static void setAssetManager(AAssetManager * mgr)
    {
        mManager = mgr;
    }

    static AAssetManager*  assetManager()
    {
        return mManager;
    }

private:
    static AAssetManager* mManager;
};

}

#endif

