
#include "ritemregister.h"
#include "ritem.h"
#include "rcameraitem.h"
#include "rfrustumitem.h"
#include "rlightitem.h"
#include "rmaterialitem.h"
#include "rshapeitem.h"
#include "rtextureitem.h"
#include "rtextureregionitem.h"
#include "rtransformationitem.h"
#include "rlightanimationitem.h"
#include "rtextureanimationitem.h"
#include "rshapeanimationitem.h"
#include "rtransanimationitem.h"
#include "rparticleitem.h"

#if defined(HAVE_BULLET)
#include "rphysicsitem.h"
#include "rcharacteritem.h"
#include "rphysicsanimationitem.h"
#endif

#if defined(HAVE_BOX2D)
#include "rb2dworld.h"
#include "rb2dbodyitem.h"
#endif

#if defined(HAVE_CHIPMUNK)
#include "rcpworld.h"
#include "rcpbodyitem.h"
#include "rcpshapeitem.h"
#endif

#include "rcameraanimationitem.h"
#include "rquaternionitem.h"
#include "rgcsettings.h"
#include "rspriteitem.h"

#include "rbutton.h"
#include "rtoggle.h"
#include "rscrollview.h"

#include "rlog.h"

namespace chikkooos
{

RItemRegister * RItemRegister::instance()
{
    static RItemRegister _instance;
    return &_instance;
}

bool RItemRegister::addItem(std::string const & name, RItem * item)
{
    return instance()->add(name, item);
}

void RItemRegister::removeItem(std::string const & name)
{
    return instance()->remove(name);
}

RItem * RItemRegister::getItem(std::string const & name)
{
    return instance()->get(name);
}

bool RItemRegister::hasItem(std::string const & name)
{
    return instance()->has(name);
}

RItemRegister::RItemRegister()
{
    add("item", new RItem());

    add("rotate", new RTransformationItem());
    add("scale", new RTransformationItem());
    add("translate", new RTransformationItem());

    add("camera", new RCameraItem());

    add("parallel", new RFrustumItem());
    add("perspective", new RFrustumItem());
    add("perspectivetheta", new RFrustumItem());

    add("cameraanimation", new RCameraAnimationItem());
    add("translateanimation", new RTransAnimationItem());
    add("scaleanimation", new RTransAnimationItem());
    add("rotateanimation", new RTransAnimationItem());
    add("lightanimation", new RLightAnimationItem());
    add("textureanimation", new RTextureAnimationItem());
    add("shapeanimation", new RShapeAnimationItem());

    add("light", new RLightItem());

    add("material", new RMaterialItem());

    add("texture", new RTextureItem());
    add("textureregion", new RTextureRegionItem());

    add("shape", new RShapeItem());
    add("cube", new RShapeItem());
    add("box", new RShapeItem());
    add("sphere", new RShapeItem());
    add("rectangle", new RShapeItem());

    add("velocityparticles", new RParticleItem());
    add("linearparticles", new RParticleItem());
    add("bezierparticles", new RParticleItem());

#if defined(HAVE_BULLET)
    add("bulletworld", new RBulletWorld());
    add("dynamicbody", new RPhysicsItem(RPhysicsItem::Dynamic));
    add("staticbody", new RPhysicsItem(RPhysicsItem::Static));
    add("character", new RCharacterItem());
    add("physicsanimation", new RPhysicsAnimationItem());
#endif

#if defined(HAVE_BOX2D)
    add("b2dworld", new RB2DWorld());
    add("b2dbody", new RB2DBodyItem());
#endif

#if defined(HAVE_CHIPMUNK)
    add("cpworld", new RCPWorld());
    add("cpbody", new RCPBodyItem());
    add("cpshape", new RCPShapeItem());
#endif

    add("depthtest", new RGCSettings());
    add("blending", new RGCSettings());
    add("culling", new RGCSettings());

    add("sprite", new RSpriteItem());

    add("button", new RButton());
    add("toggle", new RToggle());
    add("scrollview", new RScrollView());
}

bool RItemRegister::add(std::string const & name, RItem * item)
{
    return mItems.insert(std::make_pair(name, item)).second;
}

void RItemRegister::remove(std::string const & name)
{
    mItems.erase(name);
}

RItem * RItemRegister::get(std::string const & name)
{
    ItemMapIter iter = mItems.find(name);
    if (iter != mItems.end()) {
        return iter->second.data()->clone();
    } else {
        rLogW() << "item " << name << " not found" << std::endl;
    }

    return 0;
}

bool RItemRegister::has(std::string const & name) const
{
    return (mItems.find(name) != mItems.end());
}

}
