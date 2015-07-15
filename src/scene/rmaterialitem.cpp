
#include "rmaterialitem.h"

namespace chikkooos
{

void RMaterialItem::draw(RGc & gc) const
{
    RMaterial of = gc.material();

    gc.setMaterial(mMaterial);

    RItem::draw(gc);

    gc.setMaterial(of);
}

RItem * RMaterialItem::clone()
{
    return new RMaterialItem(*this);
}

void RMaterialItem::setProperties(RPropertyMap const & map, std::string const & element)
{
    mMaterial.setAmbient(map.getVector("ambient", mMaterial.ambient()));
    mMaterial.setDiffuse(map.getVector("diffuse", mMaterial.diffuse()));
    mMaterial.setSpecular(map.getVector("specular", mMaterial.specular()));
    mMaterial.setEmissive(map.getVector("emissive", mMaterial.emissive()));
    mMaterial.setShininess(map.getFloat("shininess", mMaterial.shininess()));
}

}

