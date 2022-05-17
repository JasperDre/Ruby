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
    static void CompileShader(unsigned int& shaderhandle, const char* shaderstring);
    bool Init(const char* vertfilename, const char* fragfilename);
    bool Reload();

    [[nodiscard]] unsigned int GetProgram() const { return myProgram; }

private:
    char* myVertShaderString;
    char* myFragShaderString;
    unsigned int myVertShader;
    unsigned int myFragShader;
    unsigned int myProgram;
};
