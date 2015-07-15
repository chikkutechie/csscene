
#ifndef RQUATERNIONITEM_H
#define RQUATERNIONITEM_H

#include "ritem.h"
#include "rquaternion.h"

#include <string>

namespace chikkooos
{

class RQuaternionItem: public RItem
{
public:
	RQuaternionItem(float s=1.0f, float x=0.0f, float y=0.0f, float z=0.0f)
	 : mQuaternion(s, x, y, z)
	{}

	RQuaternionItem(const float * data)
	 : mQuaternion(data)
	{}

	RQuaternionItem(float angle, const RVector & axis)
	 : mQuaternion(angle, axis)
	{}

    RMatrix matrix() const
    {
    	return mQuaternion.matrix();
    }

    RQuaternion & quaternion()
    {
    	return mQuaternion;
    }

    void setQuaternion(const RQuaternion & q)
    {
    	mQuaternion = q;
    }

    const RQuaternion & quaternion() const
    {
    	return mQuaternion;
    }

    void draw(RGc & gc) const;

    RItem * clone();
    void setProperties(RPropertyMap const & map, std::string const & element);

private:
    RQuaternion mQuaternion;
};

}

#endif
