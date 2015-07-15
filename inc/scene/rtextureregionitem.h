
#ifndef RTEXTUREREGIONITEM_H
#define RTEXTUREREGIONITEM_H

#include "ritem.h"
#include "rtextureregion.h"

namespace chikkooos
{

class RTextureRegionItem: public RItem
{
public:
    RTextureRegionItem(RItem * parent = 0)
     : RItem(parent),
       mDirty(true)
    {}

    void setTextureRegion(RTextureRegion const & r)
    {
        mTextureRegion = r;
    }

    RTextureRegion textureRegion() const
    {
        return mTextureRegion;
    }

    void set(std::string const & filename);

    void draw(RGc & gc) const;

    RItem * clone();
    void setProperties(RPropertyMap const & map, std::string const & element);

private:
    void create(RTexture const & texture);

protected:
    RTextureRegion mTextureRegion;
    int mWidth;
    int mHeight;
    int mX;
    int my;
    int mDirty;
};

}

#endif

