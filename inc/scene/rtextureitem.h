
#ifndef RTEXTUREITEM_H
#define RTEXTUREITEM_H

#include "ritem.h"
#include "rtexture.h"

namespace chikkooos
{

class RTextureItem: public RItem
{
public:
    RTextureItem(RItem * parent = 0)
     : RItem(parent)
    {}

    RTextureItem(std::string const & filename, RItem * parent = 0);

    void setTexture(RTexture const & f)
    {
        mTexture = f;
    }

    RTexture texture() const
    {
        return mTexture;
    }
    
    void set(std::string const & filename);

    void draw(RGc & gc) const;

    RItem * clone();
    void setProperties(RPropertyMap const & map, std::string const & element);

    static RTexture fromProperty(RPropertyMap const & map);

protected:
    RTexture mTexture;
};

}

#endif

