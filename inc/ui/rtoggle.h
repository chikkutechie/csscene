
#ifndef RTOGGLE_H
#define RTOGGLE_H

#include "ruiitem.h"
#include "rfrustum.h"
#include "rcamera.h"
#include "rtransformation.h"

#include "scene/revent.h"
#include "ui/rspriteitem.h"

namespace chikkooos
{

class RToggle: public RUIItem
{
public:
    RToggle()
     : mOnState(true),
       mIsPressed(false)
    {}

    virtual void setBoundedRect(float x, float y, float w, float h);

    virtual void draw(RGc & gc) const;

    virtual RItem * clone();

    virtual void setProperties(RPropertyMap const & map, std::string const & element);

    virtual void onMouseEvent(int button, int state, int x, int y);

    virtual void onSingleTap(int x, int y);


private:
    void onClick(int x, int y);

private:
    RSpriteItem mOnSprite;
    RSpriteItem mOffSprite;

    mutable RFrustum mProjection;
    mutable RCamera mCamera;
    mutable RTransformation mTransformation;

    bool mOnState;
    bool mIsPressed;
};

}

#endif

