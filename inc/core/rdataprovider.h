
#ifndef RDATAPROVIDER_H
#define RDATAPROVIDER_H

#include "rtexture.h"

#include <string>

namespace chikkooos
{

class RDataProvider
{
public:
    class FileData
    {
    public:
        FileData()
         : mLength(0),
           mData(0)
        {}

        ~FileData()
        {
            delete [] mData;
        }

        int mLength;
        char * mData;

    private:
        FileData(FileData const &);
        FileData & operator=(FileData const &);
    };

public:
    static RDataProvider & instance();

    virtual RTexture texture(std::string const & name) = 0;
//    virtual std::string path(std::string const & name) = 0;

    virtual FileData * fileData(std::string const & name) = 0;

protected:
    RDataProvider()
    {}
    RDataProvider(RDataProvider const &);
    RDataProvider& operator=(RDataProvider const &);
};

}

#endif

