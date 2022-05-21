#include "ShaderProgram.h"

#include <cassert>
#include <glad/glad.h>

#include "DebugUtility.h"
#include "FileUtility.h"

ShaderProgram::ShaderProgram()
{
    myVertShaderString = nullptr;
    myFragShaderString = nullptr;

    myVertShader = 0;
    myFragShader = 0;
    myProgram = 0;
}

ShaderProgram::~ShaderProgram()
{
    Cleanup();
}

void ShaderProgram::Cleanup()
{
    delete[] myVertShaderString;
    delete[] myFragShaderString;

    glDetachShader(myProgram, myVertShader);
    glDetachShader(myProgram, myFragShader);

    if (myVertShader)
        glDeleteShader(myVertShader);

    if (myFragShader)
        glDeleteShader(myFragShader);

    if (myProgram)
        glDeleteProgram(myProgram);

    myVertShaderString = nullptr;
    myFragShaderString = nullptr;

    myVertShader = 0;
    myFragShader = 0;
    myProgram = 0;
}

void ShaderProgram::CompileShader(unsigned int& shaderhandle, const char* shaderstring)
{
    const char* strings[] = { shaderstring };
    glShaderSource(shaderhandle, 1, strings, nullptr);
    glCompileShader(shaderhandle);

    int compiled = 0;
    glGetShaderiv(shaderhandle, GL_COMPILE_STATUS, &compiled);
    if (compiled == 0)
    {
        int infolen = 0;
        glGetShaderiv(shaderhandle, GL_INFO_LOG_LENGTH, &infolen);

        char* infobuffer = new char[infolen + 1];
        glGetShaderInfoLog(shaderhandle, infolen + 1, nullptr, infobuffer);
        DebugUtility::OutputMessage(infobuffer);
        assert(false);
        delete[] infobuffer;

        glDeleteShader(shaderhandle);
        shaderhandle = 0;
    }
}

bool ShaderProgram::LoadShaders(const char* vertfilename, const char* fragfilename)
{
    const bool isVertFileValid = FileUtility::IsFileValid(vertfilename);
    assert(isVertFileValid);
    if (!isVertFileValid)
        return false;

    const bool isFragFileValid = FileUtility::IsFileValid(fragfilename);
    assert(isFragFileValid);
    if (!isFragFileValid)
        return false;

    myVertShaderString = FileUtility::ReadFileIntoBuffer(vertfilename);
    myFragShaderString = FileUtility::ReadFileIntoBuffer(fragfilename);

    assert(myVertShaderString);
    assert(myFragShaderString);
    if (!myVertShaderString || !myFragShaderString)
        return false;

    return Reload();
}

bool ShaderProgram::Reload()
{
    assert(myVertShaderString);
    assert(myFragShaderString);

    myVertShader = glCreateShader(GL_VERTEX_SHADER);
    myFragShader = glCreateShader(GL_FRAGMENT_SHADER);

    CompileShader(myVertShader, myVertShaderString);
    CompileShader(myFragShader, myFragShaderString);

    if (myVertShader == 0 || myFragShader == 0)
    {
        Cleanup();
        return false;
    }

    myProgram = glCreateProgram();
    glAttachShader(myProgram, myVertShader);
    glAttachShader(myProgram, myFragShader);

    glLinkProgram(myProgram);

    int linked = 0;
    glGetProgramiv(myProgram, GL_LINK_STATUS, &linked);
    if (linked == 0)
    {
        int infolen = 0;
        glGetProgramiv(myProgram, GL_INFO_LOG_LENGTH, &infolen);

        char* infobuffer = new char[infolen + 1];
        glGetProgramInfoLog(myProgram, infolen + 1, nullptr, infobuffer);
        DebugUtility::OutputMessage(infobuffer);
        assert(false);
        delete[] infobuffer;

        Cleanup();
        return false;
    }

    return true;
}
