
#ifndef TRANSANIMATION_H
#define TRANSANIMATION_H

#include "ranimation.h"
#include "rtransformation.h"

namespace chikkooos
{

class RTransAnimation: public RAnimation
{
public:
	enum Type {
		Scaling,
		Translation,
		Rotation
	};
	
public:
	RTransAnimation()
	 : mType(Translation),
	   mSA(0),
	   mEA(0)
	{}

	void setType(Type t)
	{
		mType = t;
	}

    Type type() const
    {
        return mType;
    }
	
	void setAngles(float s, float e)
	{
		mSA = s;
		mEA = e;
	}
	
	void setPoints(RVector const & s, RVector const & e)
	{
		mSP = s;
		mEP = e;
	}
	
	const RTransformation & transformation() const
	{
		return mTrans;
	}

    const RVector & startPoint() const
    {
        return mSP;
    }

    const RVector & endPoint() const
    {
        return mEP;
    }

    float startAngle() const
    {
    	return mSA;
    }

    float endAngle() const
    {
    	return mEA;
    }

protected:
    void doReverse();

	void update( float elapsed);

protected:
	RTransformation mTrans;
	Type mType;
	float mSA;
	float mEA;
	RVector mSP;
	RVector mEP;
};

}

#endif
