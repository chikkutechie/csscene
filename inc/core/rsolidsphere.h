
#ifndef RSOLIdSPHERE_H
#define RSOLIdSPHERE_H

#include "rshape.h"

#include <vector>

namespace chikkooos
{

class RSolidSphere: public RShape
{
public:
    RSolidSphere(float radius = 1.0f)
     : mRadius(radius)
    {
        create(radius);
    }

    float radius() const
    {
        return mRadius;
    }

private:
    void create(float r);
  
private:
    float mRadius;
};
  
}

#endif



