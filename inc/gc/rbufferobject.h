
#ifndef BUFFEROBJECT_H
#define BUFFEROBJECT_H

#include <iostream>

#include "rcommon.h"
#include "rsmartpointer.h"

namespace chikkooos
{

class RBufferObjectData
{
public:
	RBufferObjectData()
     : mCreated(false),
       mCount(1),
       mBuffer(0)
	{}

	bool create();

	~RBufferObjectData();

private:
	RBufferObjectData(RBufferObjectData const &);
	RBufferObjectData & operator=(RBufferObjectData const &);
	
public:
	bool mCreated;
	int mCount;
    RSmartArrayPointer<GLuint> mBuffer;
};

class RBufferObject: public RSharedObject<RBufferObjectData>
{
public:
	RBufferObject(int count = 1)
	{
		data_p().mCount = count;
	}
	
    bool operator==(RBufferObject const & oth) const
    {
        return &data_p() == &oth.data_p();
    }

    bool operator!=(RBufferObject const & oth) const
    {
        return !(*this == oth);
    }

	GLuint & handle(int index=0)
	{
		return data_p().mBuffer[index];
	}

	const GLuint & handle(int index=0) const
	{
		return data_p().mBuffer[index];
	}

	void bind(int index=0, GLenum target=GL_ARRAY_BUFFER) const
	{
		glBindBuffer(target, handle(index));
	}
	
	void unbind(GLenum target=GL_ARRAY_BUFFER) const
	{
		glBindBuffer(target, 0);
	}

	bool set(GLsizeiptr size, const GLvoid *data, int index=0, GLenum target=GL_ARRAY_BUFFER, GLenum usage=GL_STATIC_DRAW);
};

}

#endif
