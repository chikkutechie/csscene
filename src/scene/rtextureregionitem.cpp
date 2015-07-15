
#include "rtextureregionitem.h"

namespace chikkooos
{

void RTextureRegionItem::draw(RGc & gc) const
{
    if (mDirty) {
        const_cast<RTextureRegionItem *>(this)->create(gc.texture());
    }

    const RTextureTransform  * tt = gc.textureTransform();

    gc.setTextureTransform(&mTextureRegion);

    RItem::draw(gc);

    gc.setTextureTransform(tt);
}

void RTextureRegionItem::create(RTexture const & texture)
{
    mTextureRegion = RTextureRegion(texture, mX, mY, mWidth, mHeight);
    mDirty = false;
}

RItem * RTextureRegionItem::clone()
{
    return new RTextureRegionItem();
}

void RTextureRegionItem::setProperties(RPropertyMap const & map, std::string const & element)
{
    mWidth = map.getInt("width");
    mHeight = map.getInt("height");
    mX = map.getInt("x");
    my = map.getInt("y");
}

}

