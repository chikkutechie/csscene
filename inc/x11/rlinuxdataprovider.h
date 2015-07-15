
#ifndef RLINUXDATAPROVIDER_H
#define RLINUXDATAPROVIDER_H

#include "rdataprovider.h"

namespace chikkooos
{

class RLinuxDataProvider: public RDataProvider
{
public:
    RTexture texture(std::string const & name);
    std::string path(std::string const & name);
    FileData* fileData(std::string const & name);

    static RDataProvider & instance();
protected:
    RLinuxDataProvider();
    RLinuxDataProvider(RLinuxDataProvider const &);
    RLinuxDataProvider& operator=(RLinuxDataProvider const &);
};

}

#endif

