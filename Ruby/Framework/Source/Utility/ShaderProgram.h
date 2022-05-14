#pragma once

#include <string>

class ShaderProgram
{
public:
    ShaderProgram();
    ShaderProgram(const char* vertfilename, const char* fragfilename);
    ShaderProgram(const std::string& vertfilename, const std::string& fragfilename);
    virtual ~ShaderProgram();

    void Cleanup();
    static void CompileShader(GLuint& shaderhandle, const char* shaderstring);
    bool Init(const char* vertfilename, const char* fragfilename);
    bool Reload();

    [[nodiscard]] GLuint GetProgram() const { return m_Program; }

private:
    char* m_VertShaderString;
    char* m_FragShaderString;
    GLuint m_VertShader;
    GLuint m_FragShader;
    GLuint m_Program;
};