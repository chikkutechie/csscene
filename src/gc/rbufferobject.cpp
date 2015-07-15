
#include "rcommon.h"
#include "rbufferobject.h"
#include "rlog.h"

namespace chikkooos
{

bool RBufferObjectData::create()
{
    if (!mCreated) {
        mBuffer = new GLuint[mCount];
        glGenBuffers(mCount, mBuffer);
        rLogI() << "buffer created" << std::endl;
        RCheckGLError();
        mCreated = true;
    }
    
    return mCreated;
}

RBufferObjectData::~RBufferObjectData()
{
    if (mCreated) {
        glDeleteBuffers(mCount, mBuffer);
        rLogI() << "buffer removed" << std::endl;
        RCheckGLError();
    }
}

bool RBufferObject::set(GLsizeiptr size, const GLvoid *data, int index, GLenum target, GLenum usage)
{
    if (!this->data_p().create()) {
        rLogE() << "buffer creation failed : " << glGetError() << std::endl;
        return false;
    }
    
    if (glIsBuffer(handle(index) == GL_FALSE)) {
        rLogE() << "not a valid buffer" << std::endl;
        return false;
    }

    bind(index, target);
    glBufferData(target, size, data, usage);
    RCheckGLError();
    unbind(target);
    
    return true;
}

}

