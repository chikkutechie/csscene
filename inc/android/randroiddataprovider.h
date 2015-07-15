
#ifndef RVIEWERDATAPROVIDER_H
#define RVIEWERDATAPROVIDER_H

#include "rdataprovider.h"

namespace chikkooos
{

class RAndroidDataProvider: public RDataProvider
{
public:
    RTexture texture(std::string const & name);
    std::string path(std::string const & name);
    FileData * fileData(std::string const & name);

    static RDataProvider & instance();
protected:
    RAndroidDataProvider();
    RAndroidDataProvider(RAndroidDataProvider const &);
    RAndroidDataProvider& operator=(RAndroidDataProvider const &);
};


}


#endif
