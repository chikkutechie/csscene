
#include "rlinuxdataprovider.h"
#include "rlog.h"
#include "rpngimagehandler.h"

#include <cstdlib>
#include <fstream>

namespace chikkooos
{

RDataProvider & RLinuxDataProvider::instance()
{
    static RLinuxDataProvider provider;
    return provider;
}

RLinuxDataProvider::RLinuxDataProvider()
{}

RDataProvider & RDataProvider::instance()
{
    return RLinuxDataProvider::instance();
}

RTexture RLinuxDataProvider::texture(std::string const & name)
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
    }

    return tex;
}

std::string RLinuxDataProvider::path(std::string const & name)
{
    return name;
}

RDataProvider::FileData * RLinuxDataProvider::fileData(std::string const & name)
{
    std::string filepath = path(name);

    std::ifstream file(filepath.c_str(),
                       std::ios::in | std::ios::binary);

    if (!file.is_open()) {
        rLogE() << "file opening failed : " << filepath << std::endl;
        return 0;
    }
    FileData * data = new FileData();
    file.seekg (0, std::ios::end);
    data->mLength = (unsigned int)file.tellg();
    data->mData = new char[data->mLength+1];
    data->mData[data->mLength] = '\0';

    file.seekg (0, std::ios::beg);
    file.read ((char *)data->mData, data->mLength);
    file.close();

    return data;
}

}

