
#ifndef RLIGHTANIMATION_H
#define RLIGHTANIMATION_H

#include "ranimation.h"
#include "rlight.h"

namespace chikkooos
{

class RLightAnimation: public RAnimation
{
public:
	RLightAnimation()
	{}

    const RLight & fromLight() const
    {
        return mFromLight;
    }

    RLight & fromLight()
    {
        return mFromLight;
    }

    void setFromLight(RLight const & l)
    {
        mFromLight = l;
        mLight = l;
    }

    const RLight & toLight() const
    {
        return mToLight;
    }

    RLight & toLight()
    {
        return mToLight;
    }

    void setToLight(RLight const & l)
    {
        mToLight = l;
    }

    RLight & light()
    {
        return mLight;
    }

    const RLight & light() const
    {
        return mLight;
    }

protected:
    void doReverse();

	void update(float elapsed);

protected:
	RLight mFromLight;
	RLight mToLight;
	RLight mLight;
};

}

#endif
