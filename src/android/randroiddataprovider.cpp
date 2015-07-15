
#include "rcommon.h"
#include "randroiddataprovider.h"
#include "rlog.h"
#include "randroidassetmanager.h"
#include "rpngimagehandler.h"

#include <cstdlib>
#include <fstream>

#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

namespace chikkooos
{

RDataProvider & RAndroidDataProvider::instance()
{
    static RAndroidDataProvider provider;
    return provider;
}

RAndroidDataProvider::RAndroidDataProvider()
{}

RDataProvider & RDataProvider::instance()
{
    return RAndroidDataProvider::instance();
}

RTexture RAndroidDataProvider::texture(std::string const & name)
{
    rLogI() << "Loading texture file : " << name << std::endl;

    RTexture tex;

    RSmartPointer<FileData> fd = fileData(name);
    if (!fd.isNull()) {
        RPNGImageHandler pih;
        if (pih.load((unsigned char *)fd->mData, fd->mLength)) {
            tex.set(pih);
        } else {
            rLogE() << "loading texture failed " << name << std::endl;
        }
    } else {
        rLogE() << "loading texture file failed" << name << std::endl;
    }

    return tex;
}

std::string RAndroidDataProvider::path(std::string const & name)
{
    return std::string();
}

RDataProvider::FileData * RAndroidDataProvider::fileData(std::string const & name)
{
	if (RAndroidAssetManager::assetManager() == 0) {
        rLogE() << "asset manager not set" << std::endl;
        return 0;
	}

    if (name.empty()) {
        rLogE() << "asset name empty" << std::endl;
        return 0;
    }

	AAsset* asset = AAssetManager_open(RAndroidAssetManager::assetManager(),
									   (const char *) name.c_str(), AASSET_MODE_UNKNOWN);
	if (asset == 0) {
        rLogE() << "asset open failed : " << name << std::endl;
		return 0;
	}

    FileData * data = new FileData();
    data->mLength = AAsset_getLength(asset);

    data->mData = new char[data->mLength+1];

    AAsset_read(asset, data->mData, data->mLength);
	data->mData[data->mLength] = '\0';

    AAsset_close(asset);

    return data;
}

}

