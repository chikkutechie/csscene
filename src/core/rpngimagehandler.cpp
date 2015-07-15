 
#include "rpngimagehandler.h"
#include "rlog.h"
#include "lodepng.h"

namespace chikkooos
{

void RPNGImageHandler::reset()
{
    mPixels.clear();
}
    
bool RPNGImageHandler::load(const char * filename)
{
    rLogI() << "loading file " << filename << std::endl;

    bool status = false;
    std::ifstream file(filename,
                       std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        rLogE() << "file opening failed : " << filename << std::endl;
        return status;
    }
    file.seekg (0, std::ios::end);
    unsigned int size = (unsigned int)file.tellg();
    RSmartArrayPointer<unsigned char> data = new unsigned char[size];

    file.seekg (0, std::ios::beg);
    file.read ((char *)data.data(), size);
    file.close();
    
    status = load(data, size);
    
    return status;   
}
    
bool RPNGImageHandler::load(const unsigned char * data, unsigned int size)
{
    mPixels.clear();

    lodepng::State state;
    unsigned error = lodepng::decode(mPixels, mWidth, mHeight, state, data, size);
    if (error) {
        rLogE() << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
        return false;
    }
    if (mPixels.empty()) {
        rLogE() << "empty image " << std::endl;
        return false;
    }

    LodePNGColorMode& color = state.info_png.color;
    
    rLogI() << "Size: " << mPixels.size() << " [" << mWidth << " x " << mHeight << "]"
            << " Depth: " << color.bitdepth << ", "
            << lodepng_get_bpp(&color)  << " bpp" << std::endl;

    if (color.colortype == LCT_RGBA) {
        mFormat = RGBA;
    } else if (color.colortype == LCT_RGB) {
        mFormat = RGB;
    } else {
        rLogE() << "unsupported color type : " << color.colortype << std::endl;
        return false;
    }
    
    return true;
}

}


