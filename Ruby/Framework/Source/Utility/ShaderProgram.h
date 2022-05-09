#pragma once

#include <string>

class ShaderProgram
{
protected:
    char* m_VertShaderString;
    char* m_FragShaderString;

    GLuint m_VertShader;
    GLuint m_FragShader;
    GLuint m_Program;

public:
    ShaderProgram();
    ShaderProgram(const char* vertfilename, const char* fragfilename);
    ShaderProgram(const std::string& vertfilename, const std::string& fragfilename);
    virtual ~ShaderProgram();

    void Cleanup();

    void CompileShader(GLuint& shaderhandle, const char* shaderstring);
    bool Init(const char* vertfilename, const char* fragfilename);
    bool Reload();

    GLuint GetProgram() { return m_Program; }
};