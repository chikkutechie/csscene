
#ifndef SHADEROBJECT_H
#define SHADEROBJECT_H

#include "rcommon.h"
#include "rsmartpointer.h"
#include "rsharedobject.h"
#include "rlog.h"

#include <map>
#include <iostream>

namespace chikkooos
{

class RShaderVariablesData
{
public:
    enum Type
    {
        Uniform,
        Attribute
    };

    class RLocation
    {
    public:
        RLocation(Type t=Uniform)
         : mType(t)
        {}

        GLint mLoc;
        Type mType;
    };

    typedef std::map<std::string, RLocation> VariableMap;
    typedef VariableMap::iterator VariableMapIter;
    typedef VariableMap::const_iterator VariableMapConstIter;

    VariableMap mMap;
};

class RShaderVariables: public RSharedObject<RShaderVariablesData>
{
public:
	typedef RShaderVariablesData::Type Type;
    typedef RShaderVariablesData::RLocation RLocation;
    typedef RShaderVariablesData::VariableMapIter VariableMapIter;
    typedef RShaderVariablesData::VariableMapConstIter VariableMapConstIter;

    static const RShaderVariablesData::Type Uniform = RShaderVariablesData::Uniform;
    static const RShaderVariablesData::Type Attribute = RShaderVariablesData::Attribute;

public:
    bool empty() const
    {
    	return data_p().mMap.empty();
    }

    void clear()
    {
    	data_p().mMap.clear();
    }

    void add(std::string const &v, Type t=Uniform)
    {
        data_p().mMap.insert(std::pair<std::string, RLocation>(v, RLocation(t)));
    }

    GLint operator[](std::string const &v) const
    {
        VariableMapConstIter iter = data_p().mMap.find(v);
        if (iter == data_p().mMap.end()) {
            rLogE() << "shader variable " << v << " not found " << std::endl;
        }
        return const_cast<RShaderVariables *>(this)->data_p().mMap[v].mLoc;
    }

    GLint operator[](std::string const &v)
    {
        VariableMapIter iter = data_p().mMap.find(v);
        if (iter == data_p().mMap.end()) {
            rLogE() << "shader variable " << v << " not found " << std::endl;
        }
        return data_p().mMap[v].mLoc;
    }

    bool updateLoc(GLuint program);

private:
};

class RShaderObjectData
{
public:
	RShaderObjectData()
     : mCreated(false),
       mProgram(0),
       mVShader(0),
       mFShader(0)
	{}

	bool create();

	~RShaderObjectData();

private:
	RShaderObjectData(RShaderObjectData const &);
	RShaderObjectData & operator=(RShaderObjectData const &);

public:
	bool mCreated;
    GLuint mProgram;
    GLuint mVShader;
    GLuint mFShader;
};

class RShaderObject: public RSharedObject<RShaderObjectData>
{
public:
	RShaderObject()
	{}

	GLuint & program()
	{
		return data_p().mProgram;
	}

	void use()
	{
		glUseProgram(program());
	}

	void unuse()
	{
		glUseProgram(0);
	}

	const GLuint & program() const
	{
		return data_p().mProgram;
	}

    bool attachAndLink();

    bool create(const char * vSource, const char * fSource);

    RShaderVariables getVariables();

private:
    bool compileShader(GLuint &shader, const char *source);
};

}

#endif

