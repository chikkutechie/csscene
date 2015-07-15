 
#ifndef RFORMATHANDLER_H
#define RFORMATHANDLER_H

#include "rcommon.h"

#include <cstring>
#include <fstream>
#include <cstring>
#include <iostream>

#include "rsmartpointer.h"
#include "rutils.h"

namespace chikkooos
{

class RImageHandler
{
public:
    enum Format
    {
        RGBA,
        RGB
    };

public:
    RImageHandler()
    {}
    
    virtual ~RImageHandler()
    {}
 
    virtual const unsigned char * data() const = 0;

    virtual RSizeI defaultSize() const = 0;

    virtual Format format() const = 0;

    virtual void reset() = 0;
    
    virtual bool load(const char * filename) = 0;
    
    virtual bool load(const unsigned char * data, unsigned int size) = 0;
};

}

#endif

