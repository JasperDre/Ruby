#include "FrameworkPCH.h"

ShaderProgram::ShaderProgram()
{
    m_VertShaderString = nullptr;
    m_FragShaderString = nullptr;

    m_VertShader = 0;
    m_FragShader = 0;
    m_Program = 0;
}

ShaderProgram::ShaderProgram(const char* vertfilename, const char* fragfilename)
{
    m_VertShaderString = nullptr;
    m_FragShaderString = nullptr;

    m_VertShader = 0;
    m_FragShader = 0;
    m_Program = 0;

    Init(vertfilename, fragfilename);
}

ShaderProgram::ShaderProgram(const std::string& vertfilename, const std::string& fragfilename)
{
    m_VertShaderString = nullptr;
    m_FragShaderString = nullptr;

    m_VertShader = 0;
    m_FragShader = 0;
    m_Program = 0;

    Init(vertfilename.c_str(), fragfilename.c_str());
}

ShaderProgram::~ShaderProgram()
{
    Cleanup();
}

void ShaderProgram::Cleanup()
{
    delete[] m_VertShaderString;
    delete[] m_FragShaderString;

    glDetachShader(m_Program, m_VertShader);
    glDetachShader(m_Program, m_FragShader);

    if (m_VertShader)
        glDeleteShader(m_VertShader);

    if (m_FragShader)
        glDeleteShader(m_FragShader);

    if (m_Program)
        glDeleteProgram(m_Program);

    m_VertShaderString = nullptr;
    m_FragShaderString = nullptr;

    m_VertShader = 0;
    m_FragShader = 0;
    m_Program = 0;
}

void ShaderProgram::CompileShader(GLuint& shaderhandle, const char* shaderstring)
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

bool ShaderProgram::Init(const char* vertfilename, const char* fragfilename)
{
    const bool isVertFileValid = FileUtility::IsFileValid(vertfilename);
    assert(isVertFileValid);
    if (!isVertFileValid)
        return false;

    const bool isFragFileValid = FileUtility::IsFileValid(fragfilename);
    assert(isFragFileValid);
    if (!isFragFileValid)
        return false;

    m_VertShaderString = FileUtility::ReadFileIntoBuffer(vertfilename);
    m_FragShaderString = FileUtility::ReadFileIntoBuffer(fragfilename);

    assert(m_VertShaderString);
    assert(m_FragShaderString);
    if (!m_VertShaderString || !m_FragShaderString)
        return false;

    return Reload();
}

bool ShaderProgram::Reload()
{
    assert(m_VertShaderString);
    assert(m_FragShaderString);

    m_VertShader = glCreateShader(GL_VERTEX_SHADER);
    m_FragShader = glCreateShader(GL_FRAGMENT_SHADER);

    CompileShader(m_VertShader, m_VertShaderString);
    CompileShader(m_FragShader, m_FragShaderString);

    if (m_VertShader == 0 || m_FragShader == 0)
    {
        Cleanup();
        return false;
    }

    m_Program = glCreateProgram();
    glAttachShader(m_Program, m_VertShader);
    glAttachShader(m_Program, m_FragShader);

    glLinkProgram(m_Program);

    int linked = 0;
    glGetProgramiv(m_Program, GL_LINK_STATUS, &linked);
    if (linked == 0)
    {
        int infolen = 0;
        glGetProgramiv(m_Program, GL_INFO_LOG_LENGTH, &infolen);

        char* infobuffer = new char[infolen + 1];
        glGetProgramInfoLog(m_Program, infolen + 1, nullptr, infobuffer);
        DebugUtility::OutputMessage(infobuffer);
        assert(false);
        delete[] infobuffer;

        Cleanup();
        return false;
    }

    return true;
}