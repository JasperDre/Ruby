#pragma once

class ShaderProgram
{
public:
    ShaderProgram();
    virtual ~ShaderProgram();

    void Cleanup();
    static void CompileShader(unsigned int& shaderhandle, const char* shaderstring);
    bool LoadShaders(const char* vertfilename, const char* fragfilename);
    bool Reload();

    [[nodiscard]] unsigned int GetProgram() const { return myProgram; }

private:
    char* myVertShaderString;
    char* myFragShaderString;
    unsigned int myVertShader;
    unsigned int myFragShader;
    unsigned int myProgram;
};
