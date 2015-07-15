
#include "rtextureanimationitem.h"
#include "rresource.h"

namespace chikkooos
{

void RTextureAnimationItem::draw(RGc & gc) const
{
    if (mAnimation.state() == RAnimation::None) {
        const_cast<RTextureAnimationItem *>(this)->mAnimation.start();
    } else if (mAnimation.state() == RAnimation::Running) {
        const_cast<RTextureAnimationItem *>(this)->mAnimation.step();
    }
    RTexture of = gc.texture();

    gc.setTexture(mAnimation.texture());

    RItem::draw(gc);

    gc.setTexture(of);
}

RItem * RTextureAnimationItem::clone()
{
    return new RTextureAnimationItem(*this);
}

void RTextureAnimationItem::setProperties(RPropertyMap const & map, std::string const & element)
{
    RAnimationItem::setProperties(map, element);

    if (map.has("textures")) {
        int t;
        std::stringstream is(map.getString("textures"));
        while (is >> t) {
            mAnimation.addTexture(RResource::instance()->texture(t));
        }
    }
}

}

