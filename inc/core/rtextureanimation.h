
#ifndef RTEXTUREANIMATION_H
#define RTEXTUREANIMATION_H

#include "ranimation.h"
#include "rtexture.h"

#include <vector>

namespace chikkooos
{

class RTextureAnimation: public RAnimation
{
public:
	RTextureAnimation()
     : mIndex(-1),
       mGoBackward(false)
	{}

    void addImage(std::string const & filename);
    void addTexture(RTexture const & texture)
    {
        mTextures.push_back(texture);
    }

    RTexture texture() const
    {
        int i = mIndex;
        if (mGoBackward) {
            i = (mTextures.size()-1) - i;
        }
        if (i >= 0 && (unsigned int)i < mTextures.size()) {
            return mTextures[i];
        }
        return RTexture();
    }

    void reset()
    {
        mTextures.clear();
    }

protected:
    void doReverse();

	void update(float elapsed);

protected:
    typedef std::vector<RTexture> Textures;
    typedef Textures::iterator TexturesIter;
    typedef Textures::const_iterator TexturesConstIter;

    Textures mTextures;
    int mIndex;
    bool mGoBackward;
};

}

#endif
