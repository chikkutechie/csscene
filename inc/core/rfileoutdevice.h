
#ifndef RFILEOUTDEVICE_H
#define RFILEOUTDEVICE_H

#include "rbasicoutdevice.h"

#include <fstream>

namespace chikkooos
{

class RFileOutDevice: public RBasicOutDevice
{
public:
    RFileOutDevice(std::string const & filename, 
                   std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out)
    {
        mOut = 0;
        mOut = new std::fstream(filename.c_str(), mode);
    }

    ~RFileOutDevice()
    {
        ((std::fstream *)mOut)->close();
        delete mOut;
    }

};

}

#endif

