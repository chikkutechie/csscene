
#include "rtextureitem.h"
#include "rresource.h"
#include "rdataprovider.h"

namespace chikkooos
{

RTextureItem::RTextureItem(std::string const & filename, RItem * parent)
 : RItem(parent)
{
    set(filename);
}

void RTextureItem::set(std::string const & filename)
{
    RTexture t;
    t.set(filename);
    setTexture(t);
}

void RTextureItem::draw(RGc & gc) const
{
    RTexture of = gc.texture();

    gc.setTexture(mTexture);

    RItem::draw(gc);

    gc.setTexture(of);
}

RItem * RTextureItem::clone()
{
    return new RTextureItem();
}

RTexture RTextureItem::fromProperty(RPropertyMap const & map)
{
    RTexture t;
    if (map.has("name")) {
        return RDataProvider::instance().texture(map.getString("name"));
    }
    return t;
}

void RTextureItem::setProperties(RPropertyMap const & map, std::string const & element)
{
    if (map.has("resource")) {
        setTexture(RResource::instance()->texture(map.getInt("resource")));
    } else if (map.has("name")) {
        setTexture(RDataProvider::instance().texture(map.getString("name")));
    }
}

}

