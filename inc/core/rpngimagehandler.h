 
#ifndef RPNGFORMATHANDLER_H
#define RPNGFORMATHANDLER_H

#include "rimagehandler.h"

#include <vector>

namespace chikkooos
{

class RPNGImageHandler: public RImageHandler
{
public:
    RPNGImageHandler()
    {
        reset();
    }
    
    ~RPNGImageHandler()
    {
        reset();
    }
 
    const unsigned char * data() const
    {
        return &mPixels[0];
    }

    RSizeI defaultSize() const
    {
        return RSizeI(mWidth, mHeight);
    }

    Format format() const
    {
        return mFormat;
    }

    void reset();
    
    bool load(const char * filename);
    
    bool load(const unsigned char * data, unsigned int size);

private:
    unsigned int mWidth;
    unsigned int mHeight;
    Format mFormat;
    std::vector<unsigned char> mPixels;
};

}

#endif

