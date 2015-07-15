 
#ifndef BMPFORMATHANDLER_H
#define BMPFORMATHANDLER_H

#include "rimagehandler.h"

namespace chikkooos
{

class RBMPImageHandler: public RImageHandler
{
public:
    struct FileHeader
    {
        unsigned short  mType;
        unsigned int    mSize;
        unsigned short  mReserved1;
        unsigned short  mReserved2;
        unsigned int    mOffsetbits;
    }; 

    struct InfoHeader
    {
        unsigned int   mSize;
        unsigned int   mWidth;
        unsigned int   mHeight;
        unsigned short mPlanes;
        unsigned short mBitcount;
        unsigned int   mCompression;
        unsigned int   mSizeimage;
        int            mXpelspermeter;
        int            mYpelspermeter;
        unsigned int   mColorsused;
        unsigned int   mColorsimportant;
    }; 

    struct Pixel{
        unsigned char   mBlue;
        unsigned char   mGreen;
        unsigned char   mRed;
    }; 

public:
    RBMPImageHandler()
    {
        reset();
    }
    
    RBMPImageHandler(const char * filename)
     : mPixels(0)
    {
        load(filename);
    }
    
    RBMPImageHandler(const unsigned char * data, unsigned int size)
     : mPixels(0)
    {
        load(data, size);
    }
    
    ~RBMPImageHandler()
    {
        reset();
    }
 
    FileHeader fileHeader() const
    {
        return mFileHeader;
    }

    InfoHeader infoHeader() const
    {
        return mInfoHeader;
    }

    const unsigned char * data() const
    {
        return mPixels;
    }

    Format format() const
    {
        return RGB;
    }

    RSizeI defaultSize() const
    {
        return RSizeI(mInfoHeader.mWidth, mInfoHeader.mHeight);
    }

    void reset();
    
    bool load(const char * filename);
    
    bool load(const unsigned char * data, unsigned int size);

private:
    FileHeader mFileHeader;
    InfoHeader mInfoHeader;
    RSmartArrayPointer<unsigned char> mPixels;
};

}

#endif

