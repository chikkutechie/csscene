
#ifndef TEXTUREOBJECT_H
#define TEXTUREOBJECT_H

#include <iostream>

#include "rcommon.h"
#include "rsmartpointer.h"
#include "rimagehandler.h"
#include "rlog.h"

namespace chikkooos
{

class RTextureData
{
public:
	RTextureData()
     : mCreated(false),
       mCount(1),
       mTexture(0),
       mMagFilter(GL_LINEAR),
       mMinFilter(GL_LINEAR),
       mGenerateMipmap(true),
       mWidth(0),
       mHeight(0)
	{}

	bool create()
	{
		if (!mCreated) {
			mTexture = new GLuint[mCount];
	  		glGenTextures(mCount, mTexture);
            rLogI() << "texture created : " << mTexture[0] << std::endl;
            RCheckGLError();
			mCreated = true;
		}
		return mCreated;
	}

	~RTextureData()
	{
		if (mCreated) {
			glDeleteTextures(mCount, mTexture);
            rLogI() << "texture removed : " << mTexture[0] << std::endl;
            RCheckGLError();
		}
	}

private:
	RTextureData(RTextureData const &);
	RTextureData & operator=(RTextureData const &);

public:
	bool mCreated;
	int mCount;
    RSmartArrayPointer<GLuint> mTexture;
    GLenum mMagFilter;
    GLenum mMinFilter;
    bool mGenerateMipmap;
    int mWidth;
    int mHeight;
};

class RTexture: public RSharedObject<RTextureData>
{
public:
	RTexture(int count = 1)
	{
		data_p().mCount = count;
	}

    bool operator==(RTexture const & oth) const
    {
        return &data_p() == &oth.data_p();
    }

    bool operator!=(RTexture const & oth) const
    {
        return !(*this == oth);
    }

    int width() const
    {
        return data_p().mWidth;
    }

    int height() const
    {
        return data_p().mHeight;
    }

	GLuint & handle(int index=0)
	{
		return data_p().mTexture[index];
	}

	const GLuint & handle(int index=0) const
	{
		return data_p().mTexture[index];
	}

	void bind(int index=0) const
	{
        glBindTexture(GL_TEXTURE_2D, handle(index));
	}

	void unbind(int index=0) const
	{
        glBindTexture(GL_TEXTURE_2D, 0);
	}

    bool isNull() const
    {
        return !data_p().mCreated;
    }

	bool set(RImageHandler const & image, int index=0);

	bool set(const std::string & filename, int index=0);

	bool set(GLsizei width, GLsizei height, const GLvoid *pixels,
			 int index=0, int level=0, GLint format=GL_RGB,
			 GLint border=0, GLenum type = GL_UNSIGNED_BYTE);
};

}

#endif
