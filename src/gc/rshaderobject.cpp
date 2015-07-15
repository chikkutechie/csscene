
#include "rshaderobject.h"
#include <cstring>

namespace chikkooos
{

bool RShaderVariables::updateLoc(GLuint program)
{
    bool res = true;
    glUseProgram(program);
    for (VariableMapIter iter=data_p().mMap.begin(); iter != data_p().mMap.end(); ++iter) {
        if (iter->second.mType == Uniform) {
            iter->second.mLoc = glGetUniformLocation(program, iter->first.c_str());
        } else {
            iter->second.mLoc = glGetAttribLocation(program, iter->first.c_str());
        }
        if (iter->second.mLoc < 0) {
            rLogE() << "retrieving location failed for " << iter->first << std::endl;
            res = false;
            break;
        }
    }
    glUseProgram(0);
    RCheckGLError();

    return res;
}

bool RShaderObjectData::create()
{
    if (!mCreated) {
        mVShader = glCreateShader(GL_VERTEX_SHADER);
        if (!mVShader) {
            rLogE() << "vertex shader creation failed" << std::endl;
            return false;
        }
        mFShader = glCreateShader(GL_FRAGMENT_SHADER);
        if (!mFShader) {
            glDeleteShader(mVShader);
            rLogE() << "fragment shader creation failed" << std::endl;
            return false;
        }
        mProgram = glCreateProgram();
        if (!mProgram) {
            glDeleteShader(mVShader);
            glDeleteShader(mFShader);
            rLogE() << "program creation failed" << std::endl;
            return false;
        }
        rLogI() << "Shader program created : " << mProgram << std::endl;
        RCheckGLError();
        mCreated = true;
    }

    return mCreated;
}

RShaderObjectData::~RShaderObjectData()
{
    if (mCreated) {
        rLogI() << "Shader program deleted : " << mProgram << std::endl;
        glDeleteProgram(mProgram);
        glDeleteShader(mVShader);
        glDeleteShader(mFShader);
        RCheckGLError();
    }
}

bool RShaderObject::attachAndLink()
{
    if (glIsProgram(program()) == GL_FALSE) {
        rLogE() << "not a valid program object " << std::endl;
        return false;
    }

    if (glIsShader(data_p().mVShader) == GL_FALSE) {
        rLogE() << "not a valid shader object " << std::endl;
        return false;
    }

    if (glIsShader(data_p().mFShader) == GL_FALSE) {
        rLogE() << "not a valid shader object " << std::endl;
        return false;
    }

    glAttachShader(program(), data_p().mVShader);
    glAttachShader(program(), data_p().mFShader);
    RCheckGLError();

    GLint lr = GL_TRUE;
    glGetProgramiv(program(), GL_ATTACHED_SHADERS, &lr);
    if (lr != 2) {
        rLogE() << "attached shader count is " << lr << std::endl;
    }

    glLinkProgram(program());
    RCheckGLError();

    glGetProgramiv(program(), GL_LINK_STATUS, &lr);
    if (lr != GL_TRUE) {
        char infoLog[1024] = {'\0'};
        glGetShaderInfoLog(program(), sizeof(infoLog)-1, 0, infoLog);
        rLogE() << "error : " << infoLog << std::endl;
        return false;
    }

    return true;
}

bool RShaderObject::create(const char * vSource, const char * fSource)
{
    if (!this->data_p().create()) {
        return false;
    }

    bool res = compileShader(data_p().mVShader, vSource);
    if (!res) {
        rLogE() << "vertex shader creation failed" << std::endl;
        return false;
    }

    res = compileShader(data_p().mFShader, fSource);
    if (!res) {
        rLogE() << "fragment shader creation failed" << std::endl;
        return false;
    }

    if (!attachAndLink()) {
        rLogE() << "attaching failed" << std::endl;
        return false;
    }

    return true;
}

RShaderVariables RShaderObject::getVariables()
{
    RShaderVariables vars;

    GLint maxVariableLength;
    GLint numberOfVariables;

    use();

    glGetProgramiv(program(), GL_ACTIVE_UNIFORMS, &numberOfVariables);
    glGetProgramiv(program(), GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxVariableLength);

    RSmartArrayPointer<char> variableName = new char[maxVariableLength];

    for(int index = 0; index < numberOfVariables; index++) {
        GLint size;
        GLenum type;

        glGetActiveUniform(program(), index, maxVariableLength,
                           0, &size, &type, variableName.data());


        vars.add(variableName.data(), RShaderVariables::Uniform);

    }

    glGetProgramiv(program(), GL_ACTIVE_ATTRIBUTES, &numberOfVariables);
    RCheckGLError();
    glGetProgramiv(program(), GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxVariableLength);
    RCheckGLError();

    variableName = new char[maxVariableLength];

    for(int index = 0; index < numberOfVariables; index++) {
        GLint size;
        GLenum type;

        glGetActiveAttrib(program(), index, maxVariableLength,
                           0, &size, &type, variableName.data());


        vars.add(variableName.data(), RShaderVariables::Attribute);
    }

    unuse();

    if (!vars.updateLoc(program())) {
        return RShaderVariables();
    }

    return vars;
}

bool RShaderObject::compileShader(GLuint &shader, const char *source)
{
    GLint lengths[2] = {std::strlen(source), 0};
    glShaderSource(shader, 1, &source, lengths);
    RCheckGLError();

    glCompileShader(shader);
    RCheckGLError();

    GLint result = GL_TRUE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

    if (result != GL_TRUE) {
        char infoLog[1024] = {'\0'};
        glGetShaderInfoLog(shader, sizeof(infoLog)-1, 0, infoLog);
        rLogE() << "error : " << infoLog << std::endl;
        return false;
    }

    return true;
}

}

