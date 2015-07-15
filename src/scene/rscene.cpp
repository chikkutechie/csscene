
#include "rscene.h"
#include "ritem.h"
#include "tinyxml.h"
#include "ritemregister.h"

#if defined(HAVE_BULLET)
#include "rbulletworld.h"
#endif

#if defined(HAVE_BOX2D)
#include "rb2dworld.h"
#endif

#if defined(HAVE_CHIPMUNK)
#include "rcpworld.h"
#endif

#include "rresource.h"
#include "rview.h"

namespace chikkooos
{

RScene::RScene(RView * view)
 : mRootItem(0),
   mView(view)
{}

RScene::~RScene()
{}

void RScene::draw(RGc & gc) const
{
    gc.clear();
    if (mRootItem) {
        mRootItem->draw(gc);
        gc.finish();
    }
}

void RScene::update(float dt)
{
    for (unsigned int i=0; i<mItemToRemove.size(); ++i) {
        if (mItemToRemove[i]->parent()) {
            mItemToRemove[i]->parent()->remove(mItemToRemove[i]);
        }
    }
    mItemToRemove.clear();

    if (mRootItem) {
        mRootItem->update(dt);
    }
}

RItem * RScene::load(TiXmlNode* node)
{
    if (!node) {
        return 0;
    }

    const std::string package(PACKAGE);

    int t = node->Type();
    switch (t) {
        case TiXmlNode::ELEMENT: {
            if (package.compare(node->Value()) == 0) {
                rLogI() << "creating the scene " << std::endl;
                return createScene(node->FirstChild());
            }
        }
    }

    for (TiXmlNode* child = node->FirstChild(); child != 0; child = child->NextSibling()) {
        RItem * item = load(child);
        if (item) {
            return item;
        }
    }

    return 0;
}

RItem * RScene::createScene(TiXmlNode* node)
{
    if (!node) {
        return 0;
    }

    const std::string item("item");
    const std::string resource("resource");

    int t = node->Type();
    switch (t) {
        case TiXmlNode::ELEMENT: {
            if (item.compare(node->Value()) == 0) {
                return createItems(node, 0);
            } else if (resource.compare(node->Value()) == 0) {
                createResource(node);
            }
        }
    }

    return createScene(node->NextSibling());
}

#if 0
void RScene::createB2DWorld(TiXmlNode* node)
{
#if defined(HAVE_BOX2D)

    if (!node) {
        return;
    }

    int t = node->Type();
    switch (t) {
        case TiXmlNode::ELEMENT: {
            RPropertyMap attributes = toPropertyMap(node->ToElement()->FirstAttribute());
            RB2DWorld::instance()->setProperties(attributes, node->Value());
        }
    }

    for (TiXmlNode* child = node->FirstChild(); child != 0; child = child->NextSibling()) {
        createB2DWorld(child);
    }

#endif
}

void RScene::createCPWorld(TiXmlNode* node)
{
#if defined(HAVE_CHIPMUNK)

    if (!node) {
        return;
    }

    int t = node->Type();
    switch (t) {
        case TiXmlNode::ELEMENT: {
            RPropertyMap attributes = toPropertyMap(node->ToElement()->FirstAttribute());
            RCPWorld::instance()->setProperties(attributes, node->Value());
        }
    }

    for (TiXmlNode* child = node->FirstChild(); child != 0; child = child->NextSibling()) {
        createCPWorld(child);
    }

#endif
}

void RScene::createBulletWorld(TiXmlNode* node)
{
    if (!node) {
        return;
    }

    int t = node->Type();
    switch (t) {
        case TiXmlNode::ELEMENT: {
            RPropertyMap attributes = toPropertyMap(node->ToElement()->FirstAttribute());
#if defined(HAVE_BULLET)
            RBulletWorld::instance()->setProperties(attributes, node->Value());
#endif
        }
    }

    for (TiXmlNode* child = node->FirstChild(); child != 0; child = child->NextSibling()) {
        createBulletWorld(child);
    }
}

#endif

RItem * RScene::createItems(TiXmlNode* node, RItem * parent)
{
    if (!node) {
        return 0;
    }

    RItem * item = 0;

    int t = node->Type();

    switch (t) {
        case TiXmlNode::ELEMENT: {
            item = RItemRegister::getItem(node->Value());
            if (item) {
                item->setScene(this);
                item->setParent(parent);
                item->setName(node->Value());
                loadItems(item, node->ToElement());
            } else {
                rLogW() << "item " << node->Value() << " not found" << std::endl;
            }
        }
    }

    if (item) {
        for (TiXmlNode* child = node->FirstChild(); child != 0; child = child->NextSibling()) {
            createItems(child, item);
        }
    }

    return item;
}

void RScene::createResource(TiXmlNode* node)
{
    if (!node) {
        return;
    }

    int t = node->Type();

    switch (t) {
        case TiXmlNode::ELEMENT: {
            RPropertyMap attributes = toPropertyMap(node->ToElement()->FirstAttribute());
            RResource::instance()->setProperties(attributes, node->Value());
        }
    }

    for (TiXmlNode* child = node->FirstChild(); child != 0; child = child->NextSibling()) {
        createResource(child);
    }
}

void RScene::loadItems(RItem * item, TiXmlElement* element)
{
    if (!element) {
        return;
    }

    RPropertyMap attributes = toPropertyMap(element->FirstAttribute());

    int id = attributes.getInt("id", item->id());
    item->setId(id);
    item->setProperties(attributes, element->Value());
}

RPropertyMap RScene::toPropertyMap(TiXmlAttribute* attrib)
{
    RPropertyMap attributes;

    while (attrib) {
        attributes.insert(attrib->Name(), attrib->Value());
        attrib = attrib->Next();
    }

    return attributes;
}

bool RScene::load(std::string const & filename)
{
    TiXmlDocument doc;
    bool loadOkay = doc.LoadFile(filename.c_str());
    if (loadOkay) {
        RResource::instance()->reset();
        RItem * item = load(&doc);
        if (item) {
            setRootItem(item);
            return true;
        }
    } else {
        rLogE() << " error in loading scene " << filename
                << "(" << doc.ErrorRow() << ":" << doc.ErrorCol() << ") : " << doc.ErrorDesc() << std::endl;
    }

    return false;
}

bool RScene::loadFromData(const char * data)
{

    TiXmlDocument doc;
    bool loadOkay = doc.Parse(data);
    if (loadOkay) {
        RResource::instance()->reset();
        RItem * item = load(&doc);
        if (item) {
            setRootItem(item);
            return true;
        } else {
            rLogE() << "could not create item from scene data " << std::endl;
        }
    } else {
        rLogE() << "error in loading scene "
                << "(" << doc.ErrorRow() << ":" << doc.ErrorCol() << ") : " << doc.ErrorDesc() << std::endl;
    }

    return false;
}

RScene * RScene::currentScene()
{
    return RView::instance()->scene();
}


}

