
#include "rresource.h"
#include "rshapeitem.h"
#include "rtextureitem.h"

namespace chikkooos
{

RResource* RResource::instance()
{
    static RResource obj;
    return &obj;
}

RResource::RResource()
{}

void RResource::setProperties(RPropertyMap const & attr, std::string const & name)
{
    if (name.compare("resource") == 0) {
    } else if (name.compare("shape") == 0) {
        if (attr.has("id")) {
            int id = attr.getInt("id");
            RShape * s = RShapeItem::fromProperty(attr);
            if (s) {
                if (attr.getInt("buffer")) {
                    s->createBuffer();
                }
                if (!mShapes.insert(std::make_pair(id, s)).second) {
                    rLogW() << "insertion of " << name << "(" << id << ") failed" << std::endl;
                }
            }
        }
    } else if(name.compare("texture") == 0) {
        if (attr.has("id")) {
            int id = attr.getInt("id");
            RTexture t = RTextureItem::fromProperty(attr);
            if (!mTextures.insert(std::make_pair(id, t)).second) {
                rLogW() << "insertion of " << name << "(" << id << ") failed" << std::endl;
            }
        }
    } else {
        RResourceItem * item =  getItem(name);
        if (item) {
            item->setProperties(attr, name);
        } else {
            rLogW() << "Resource " << name << " not found" << std::endl;
        }
    }
}

void RResource::reset()
{
    rLogI() << "resetting resource" << std::endl;
    mShapes.clear();
    mTextures.clear();
}

void RResource::clearAll()
{
    rLogI() << "clearing resource" << std::endl;
    mShapes.clear();
    mTextures.clear();
    mItems.clear();
}

RTexture RResource::texture(int id) const
{
    RTexture t;
    TextureResourceConstIter iter = mTextures.find(id);
    if (iter != mTextures.end()) {
        t = iter->second;
    } else {
        rLogW() << "retrieving texture resource "<< id << " failed" << std::endl;
    }
    return t;
}

RSmartPointer<RShape> RResource::shape(int id) const
{
    RSmartPointer<RShape> s;

    ShapeResourceConstIter iter = mShapes.find(id);
    if (iter != mShapes.end()) {
        s = iter->second;
    } else {
        rLogW() << "retrieving shape resource "<< id << " failed" << std::endl;
    }
    return s;
}

}

