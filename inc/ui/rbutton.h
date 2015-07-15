
#ifndef RBUTTON_H
#define RBUTTON_H

#include <string>

#include "ruiitem.h"
#include "rfrustum.h"
#include "rcamera.h"
#include "rtransformation.h"

#include "scene/revent.h"
#include "ui/rspriteitem.h"

namespace chikkooos
{

class RButton: public RUIItem
{
public:
    RButton()
     : mIsPressed(false),
       mCreated(false)
    {}

    virtual void setBoundedRect(float x, float y, float w, float h);

    virtual void update(float dt);

    virtual void draw(RGc & gc) const;

    virtual RItem * clone();

    virtual void setProperties(RPropertyMap const & map, std::string const & element);

    virtual void onMouseEvent(int button, int state, int x, int y);

    virtual void onTouchDown(int x, int y);

    virtual void onTouchUp(int x, int y);

    void create(std::string const & pressed, std::string const & normal);
    void create();

protected:
    void onClick(int x, int y);

protected:
    RSmartPointer<RItem> mPressedSprite;
    RSmartPointer<RItem> mNormalSprite;

    mutable RFrustum mProjection;
    mutable RCamera mCamera;
    mutable RTransformation mTransformation;

    bool mIsPressed;
    bool mCreated;

    std::string mPressedItemName;
    std::string mNormalItemName;

};

}

#endif
