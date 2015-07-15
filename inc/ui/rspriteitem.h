
#ifndef RSPRITEITEM_H
#define RSPRITEITEM_H

#include "ruiitem.h"
#include "rmeshshape.h"

namespace chikkooos
{

class RSpriteItem: public RUIItem
{
protected:
    RMeshShape mShape;
    bool mFlip;
    RTexture mTexture;

    mutable RFrustum mProjection;
    mutable RCamera mCamera;
    mutable RTransformation mTransformation;

    bool mIsPressed;

public:
    RSpriteItem();

    void setBoundedRect(float x, float y, float w, float h);

    void set(float x, float y, float w, float h, bool flip = false);

    virtual void draw(RGc & gc) const;

    virtual RItem * clone();

    virtual void setProperties(RPropertyMap const & map, std::string const & element);

    void setImage(std::string const &filename);

    virtual void onMouseEvent(int button, int state, int x, int y);

    virtual void onSingleTap(int x, int y);


private:
    void onClick(int x, int y);
};

}

#endif
