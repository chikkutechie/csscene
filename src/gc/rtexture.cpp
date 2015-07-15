
#include "rcommon.h"
#include "rtexture.h"
#include "rimagehandlercreator.h"

namespace chikkooos
{

#if defined(R_ES)
#define glGenerateMipmap glGenerateMipmapOES
#endif


bool RTexture::set(const std::string & filename, int index)
{
    rLogI() << "Texture file : " << filename << std::endl;

    if (!this->data_p().create()) {
        return false;
    }

    RSmartPointer<RImageHandler> imageHandler = RImageHandlerCreator::createHandler(filename);
    if (imageHandler.isNull() || !imageHandler->load(filename.c_str())) {
        rLogE() << "loading image " << filename.c_str() << " failed" << std::endl;
        return false;
    }

    return set(*(imageHandler.data()), index);
}

bool RTexture::set(RImageHandler const & image, int index)
{
    GLint format = GL_RGB;
    if (image.format() == RImageHandler::RGBA) {
        format = GL_RGBA;
        rLogI() << "Image format : GL_RGBA" << std::endl;
    }

    return set(image.defaultSize().width(),
                  image.defaultSize().height(),
                  image.data(),
                  index, 0, format);
}

bool RTexture::set(GLsizei width, GLsizei height, const GLvoid *pixels,
             int index, int level, GLint format,
             GLint border, GLenum type)
{
    data_p().mWidth = width;
    data_p().mHeight = height;

    if (!this->data_p().create()) {
        return false;
    }

    bind(index);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    RCheckGLError();

    glTexImage2D(GL_TEXTURE_2D, level, format,
                 width, height, border, format, type, pixels);
    RCheckGLError();

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        rLogE() << "glGetError() " << error << std::endl;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->data_p().mMagFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->data_p().mMinFilter);

    if (this->data_p().mGenerateMipmap) {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    RCheckGLError();

    unbind();

    return true;
}

}

