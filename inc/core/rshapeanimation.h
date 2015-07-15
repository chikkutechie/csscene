
#ifndef RSHAPEANIMATION_H
#define RSHAPEANIMATION_H

#include "ranimation.h"
#include "rshape.h"
#include "rsmartpointer.h"

#include <vector>

namespace chikkooos
{

class RShapeAnimation: public RAnimation
{
public:
	RShapeAnimation()
     : mIndex(-1),
       mGoBackward(false)
	{}

    void addShape(RSmartPointer<RShape>const & shape)
    {
        mShapes.push_back(shape);
    }

    RSmartPointer<RShape> shape() const
    {
        int i = mIndex;
        if (mGoBackward) {
            i = (mShapes.size()-1) - i;
        }
        if (i >= 0 && (unsigned int)i < mShapes.size()) {
            return mShapes[i];
        }
        return RSmartPointer<RShape>();
    }

    void reset()
    {
        mShapes.clear();
    }

protected:
    void doReverse();

	void update(float elapsed);

protected:
    typedef std::vector<RSmartPointer<RShape> > Shapes;
    typedef Shapes::iterator ShapesIter;
    typedef Shapes::const_iterator ShapesConstIter;

    Shapes mShapes;
    int mIndex;
    bool mGoBackward;
};

}

#endif
