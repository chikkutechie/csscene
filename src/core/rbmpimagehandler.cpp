 
#include "rcommon.h"
#include "rbmpimagehandler.h"
#include "rlog.h"

namespace chikkooos
{

void RBMPImageHandler::reset()
{
    mPixels = 0;
    std::memset(&mFileHeader, 0x00, sizeof(mFileHeader));
    std::memset(&mInfoHeader, 0x00, sizeof(mInfoHeader));
}

bool RBMPImageHandler::load(const char * filename)
{
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

bool RBMPImageHandler::load(const unsigned char * data, unsigned int size)
{
    reset();

    if (size < sizeof(mFileHeader) + sizeof(mInfoHeader)) {
        return false;
    }

    if (data[0] != 'B' ||
        data[1] != 'M') {
        rLogE() << "bmp header not found" << (char)data[0] << (char)data[1] << std::endl;
        return false;
    }

    int offset = 0;

    std::memcpy(&mFileHeader.mType, data + offset, sizeof(mFileHeader.mType));
    offset += sizeof(mFileHeader.mType);

    std::memcpy(&mFileHeader.mSize, data + offset, sizeof(mFileHeader.mSize));
    offset += sizeof(mFileHeader.mSize);

    std::memcpy(&mFileHeader.mReserved1, data + offset, sizeof(mFileHeader.mReserved1));
    offset += sizeof(mFileHeader.mReserved1);

    std::memcpy(&mFileHeader.mReserved2, data + offset, sizeof(mFileHeader.mReserved2));
    offset += sizeof(mFileHeader.mReserved2);

    std::memcpy(&mFileHeader.mOffsetbits, data + offset, sizeof(mFileHeader.mOffsetbits));
    offset += sizeof(mFileHeader.mOffsetbits);

    std::memcpy(&mInfoHeader.mSize, data + offset, sizeof(mInfoHeader.mSize));
    offset += sizeof(mInfoHeader.mSize);

    std::memcpy(&mInfoHeader.mWidth, data + offset, sizeof(mInfoHeader.mWidth));
    offset += sizeof(mInfoHeader.mWidth);

    std::memcpy(&mInfoHeader.mHeight, data + offset, sizeof(mInfoHeader.mHeight));
    offset += sizeof(mInfoHeader.mHeight);

    std::memcpy(&mInfoHeader.mPlanes, data + offset, sizeof(mInfoHeader.mPlanes));
    offset += sizeof(mInfoHeader.mPlanes);
    
    std::memcpy(&mInfoHeader.mBitcount, data + offset, sizeof(mInfoHeader.mBitcount));
    offset += sizeof(mInfoHeader.mBitcount);
    
    std::memcpy(&mInfoHeader.mCompression, data + offset, sizeof(mInfoHeader.mCompression));
    offset += sizeof(mInfoHeader.mCompression);
    
    std::memcpy(&mInfoHeader.mSizeimage, data + offset, sizeof(mInfoHeader.mSizeimage));
    offset += sizeof(mInfoHeader.mSizeimage);
    
    std::memcpy(&mInfoHeader.mXpelspermeter, data + offset, sizeof(mInfoHeader.mXpelspermeter));
    offset += sizeof(mInfoHeader.mXpelspermeter);
    
    std::memcpy(&mInfoHeader.mYpelspermeter, data + offset, sizeof(mInfoHeader.mYpelspermeter));
    offset += sizeof(mInfoHeader.mYpelspermeter);
    
    std::memcpy(&mInfoHeader.mColorsused, data + offset, sizeof(mInfoHeader.mColorsused));
    offset += sizeof(mInfoHeader.mColorsused);
    
    std::memcpy(&mInfoHeader.mColorsimportant, data + offset, sizeof(mInfoHeader.mColorsimportant));
    offset += sizeof(mInfoHeader.mColorsimportant);
    
    if (mInfoHeader.mCompression) {
        rLogE() << "compression used " << mInfoHeader.mCompression << std::endl;
        return false;
    }

    unsigned int dataSize = size - mFileHeader.mOffsetbits;
    mPixels = new unsigned char[dataSize];

    memcpy(mPixels, data + mFileHeader.mOffsetbits, dataSize);

    return true;
}

}

