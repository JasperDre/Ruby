#include "FrameworkPCH.h"
#include "GLHelpers.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace GLHelpers
{
    void CheckForGLErrors()
    {
        const GLenum error = glGetError();
        if (error == GL_NO_ERROR)
            return;

        const char* errorString;
        switch (error)
        {
            case GL_INVALID_ENUM:
            {
                errorString = "GL_INVALID_ENUM";
                break;
            }
            case GL_INVALID_VALUE:
            {
                errorString = "GL_INVALID_VALUE";
                break;
            }
            case GL_INVALID_OPERATION:
            {
                errorString = "GL_INVALID_OPERATION";
                break;
            }
            case GL_STACK_OVERFLOW:
            {
                errorString = "GL_STACK_OVERFLOW";
                break;
            }
            case GL_STACK_UNDERFLOW:
            {
                errorString = "GL_STACK_UNDERFLOW";
                break;
            }
            case GL_OUT_OF_MEMORY:
            {
                errorString = "GL_OUT_OF_MEMORY";
                break;
            }
            case GL_INVALID_FRAMEBUFFER_OPERATION:
            {
                errorString = "GL_INVALID_FRAMEBUFFER_OPERATION";
                break;
            }
            default:
            {
                errorString = "Unknown error";
                break;
            }
        }

        DebugUtility::OutputMessage("%s\n", errorString);
        assert(error == GL_NO_ERROR);
    }

    void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei /*length*/, const char* message, const void* /*userParam*/)
    {
        // Ignore insignificant error codes
        if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
            return;

        std::string errorMessage;
        switch (source)
        {
            case GL_DEBUG_SOURCE_API:
            {
                errorMessage += "Source: API\n";
                break;
            }
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            {
                errorMessage += "Source: Window System\n";
                break;
            }
            case GL_DEBUG_SOURCE_SHADER_COMPILER:
            {
                errorMessage += "Source: Shader Compiler\n";
                break;
            }
            case GL_DEBUG_SOURCE_THIRD_PARTY:
            {
                errorMessage += "Source: Third Party\n";
                break;
            }
            case GL_DEBUG_SOURCE_APPLICATION:
            {
                errorMessage += "Source: Application\n";
                break;
            }
            case GL_DEBUG_SOURCE_OTHER:
            {
                errorMessage += "Source: Other\n";
                break;
            }
            default:
            {
                errorMessage += "Source: Unkown\n";
                break;
            }
        }

        switch (type)
        {
            case GL_DEBUG_TYPE_ERROR:
            {
                errorMessage += "Type: Error\n";
                break;
            }
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            {
                errorMessage += "Type: Deprecated Behaviour\n";
                break;
            }
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            {
                errorMessage += "Type: Undefined Behaviour\n";
                break;
            }
            case GL_DEBUG_TYPE_PORTABILITY:
            {
                errorMessage += "Type: Portability\n";
                break;
            }
            case GL_DEBUG_TYPE_PERFORMANCE:
            {
                errorMessage += "Type: Performance\n";
                break;
            }
            case GL_DEBUG_TYPE_MARKER:
            {
                errorMessage += "Type: Marker\n";
                break;
            }
            case GL_DEBUG_TYPE_PUSH_GROUP:
            {
                errorMessage += "Type: Push Group\n";
                break;
            }
            case GL_DEBUG_TYPE_POP_GROUP:
            {
                errorMessage += "Type: Pop Group\n";
                break;
            }
            case GL_DEBUG_TYPE_OTHER:
            {
                errorMessage += "Type: Other\n";
                break;
            }
            default:
            {
                errorMessage += "Type: Unkown\n";
                break;
            }
        }

        switch (severity)
        {
            case GL_DEBUG_SEVERITY_HIGH:
            {
                errorMessage += "Severity: High\n";
                break;
            }
            case GL_DEBUG_SEVERITY_MEDIUM:
            {
                errorMessage += "Severity: Medium\n";
                break;
            }
            case GL_DEBUG_SEVERITY_LOW:
            {
                errorMessage += "Severity: Low\n";
                break;
            }
            case GL_DEBUG_SEVERITY_NOTIFICATION:
            {
                errorMessage += "Severity: Notification\n";
                break;
            }
            default:
            {
                errorMessage += "Severity: Unkown\n";
                break;
            }
        }

        errorMessage += message;

        DebugUtility::OutputMessage("%s\n", errorMessage.c_str());
        assert(errorMessage.empty());
    }

    void GLFWErrorCallback(int anError, const char* aDescription)
    {
        DebugUtility::OutputMessage("%i %s\n", anError, aDescription);
        assert(!aDescription);
    }

    unsigned char* LoadImage(const std::string& filename, int& aWidth, int& aHeight, int& aNumberOfComponents)
    {
        const bool isFileValid = FileUtility::IsFileValid(filename);
        assert(isFileValid);
        if (!isFileValid)
            return nullptr;

        unsigned char* image = stbi_load(filename.c_str(), &aWidth, &aHeight, &aNumberOfComponents, STBI_default);
        if (!image)
        {
            stbi_image_free(image);
            return nullptr;
        }

        return image;
    }

    GLuint LoadTexture(const std::string& filename)
    {
        const bool isFileValid = FileUtility::IsFileValid(filename);
        assert(isFileValid);
        if (!isFileValid)
            return 0;

        int width = 0;
        int height = 0;
        int numberOfComponents = 0;
        unsigned char* image = LoadImage(filename, width, height, numberOfComponents);
        if (!image)
        {
            stbi_image_free(image);
            return 0;
        }

        Flip32BitImageVertically(image, width, height);

        GLuint texhandle = 0;
        glGenTextures(1, &texhandle);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texhandle);
        const GLenum format = numberOfComponents == 3 ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, image);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);

        return texhandle;
    }

    GLuint LoadTextureCubemap(const char** filenames, GLuint oldtexturehandle)
    {
        GLuint texhandle = oldtexturehandle;
        if (texhandle == 0)
            glGenTextures(1, &texhandle);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texhandle);

        for (int i = 0; i < 6; i++)
        {
            const bool isFileValid = FileUtility::IsFileValid(filenames[i]);
            assert(isFileValid);
            if (!isFileValid)
                return 0;

            int width = 0;
            int height = 0;
            int numberOfComponents = 0;
            unsigned char* image = stbi_load(filenames[i], &width, &height, &numberOfComponents, STBI_default);
            if (!image)
            {
                stbi_image_free(image);
                return 0;
            }

            Flip32BitImageVertically(image, width, height);

            const GLenum format = numberOfComponents == 3 ? GL_RGB : GL_RGBA;
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, image);
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

        return texhandle;
    }

    void Flip32BitImageVertically(unsigned char* buffer, unsigned int width, unsigned int height)
    {
        unsigned int* temp = new unsigned int[width];
        const unsigned int linesize = width * sizeof(unsigned int);

        unsigned int* buffer32 = reinterpret_cast<unsigned*>(buffer);
        for (unsigned int y = 0; y < height / 2; y++)
        {
            const unsigned int LineOffsetY = y * width;
            const unsigned int LineOffsetHminusY = (height - 1 - y) * width;

            memcpy(temp, &buffer32[LineOffsetY], linesize);
            memcpy(&buffer32[LineOffsetY], &buffer32[LineOffsetHminusY], linesize);
            memcpy(&buffer32[LineOffsetHminusY], temp, linesize);
        }

        delete[] temp;
    }

    GLint GetAttributeLocation(GLuint aShaderProgram, const char* aName)
    {
        return glGetAttribLocation(aShaderProgram, aName);
    }

    GLint GetUniformLocation(GLuint aShaderProgram, const char* aName)
    {
        return glGetUniformLocation(aShaderProgram, aName);
    }

    void SetUniform1f(GLuint aShaderProgram, const char* aName, float aValue)
    {
        const GLint uniform = GetUniformLocation(aShaderProgram, aName);
        if (uniform != -1)
            glUniform1f(uniform, aValue);
    }

    void SetUniform2f(GLuint aShaderProgram, const char* aName, Vector2Float aValue)
    {
        const GLint uniform = GetUniformLocation(aShaderProgram, aName);
        if (uniform != -1)
            glUniform2f(uniform, aValue.myX, aValue.myY);
    }

    void SetUniform1i(GLuint aShaderProgram, const char* aName, int aValue)
    {
        const GLint uniform = GetUniformLocation(aShaderProgram, aName);
        if (uniform != -1)
            glUniform1i(uniform, aValue);
    }
}
