#pragma once

#include <string>

class ShaderProgram
{
public:
    ShaderProgram();
    ShaderProgram(const char* aVertexShaderFilepath, const char* aFragmentShaderFilepath);
    ShaderProgram(const std::string& aVertexShaderFilepath, const std::string& aFragmentShaderFilepath);
    virtual ~ShaderProgram();

    void Cleanup();
    static void CompileShader(GLuint& shaderhandle, const char* shaderstring);
    bool Init(const char* vertfilename, const char* fragfilename);
    bool Reload();

    [[nodiscard]] GLuint GetProgram() const { return myProgram; }

private:
    char* myVertShaderString;
    char* myFragShaderString;
    GLuint myVertShader;
    GLuint myFragShader;
    GLuint myProgram;
};