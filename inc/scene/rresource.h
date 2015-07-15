
#ifndef RRESOURCE_H
#define RRESOURCE_H

#include "rcommon.h"
#include "rvector.h"
#include "rpropertymap.h"
#include "rsmartpointer.h"
#include "rshape.h"
#include "rtexture.h"

#include <string>
#include <map>

namespace chikkooos
{

class RResourceItem
{
public:
    virtual ~RResourceItem()
    {}

    virtual void setProperties(RPropertyMap const & map, std::string const & name) = 0;
};

class RResource
{
public:
    static RResource* instance();

public:
    void setProperties(RPropertyMap const & map, std::string const & name);
    void reset();
    void clearAll();

    RSmartPointer<RShape> shape(int id) const;
    RTexture texture(int id) const;

    void registerItem(std::string const &name, RResourceItem *item)
    {
        mItems.insert(std::make_pair(name, item));
    }

    const RResourceItem * getItem(std::string const &name) const
    {
        ResourceItemsConstIter iter = mItems.find(name);
        if (iter != mItems.end()) {
            return iter->second;
        }
        return 0;
    }

    RResourceItem * getItem(std::string const &name)
    {
        ResourceItemsIter iter = mItems.find(name);
        if (iter != mItems.end()) {
            return iter->second;
        }
        return 0;
    }

private:
    RResource();
    RResource(RResource const & oth);
    RResource& operator=(RResource const & oth);

private:
    typedef std::map<int, RSmartPointer<RShape> > ShapeResource;
    typedef ShapeResource::iterator ShapeResourceIter;
    typedef ShapeResource::const_iterator ShapeResourceConstIter;

    typedef std::map<int, RTexture> TextureResource;
    typedef TextureResource::iterator TextureResourceIter;
    typedef TextureResource::const_iterator TextureResourceConstIter;

    typedef std::map<std::string, RSmartPointer<RResourceItem> > ResourceItems;
    typedef ResourceItems::iterator ResourceItemsIter;
    typedef ResourceItems::const_iterator ResourceItemsConstIter;


private:
    ShapeResource mShapes;
    TextureResource mTextures;
    ResourceItems mItems;
};

}

#endif

