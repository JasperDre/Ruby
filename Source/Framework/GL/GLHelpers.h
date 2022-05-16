#pragma once

#include <string>

namespace GLHelpers
{
	void CheckForGLErrors();
	void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam);
	void GLFWErrorCallback(int anError, const char* aDescription);
	unsigned char* LoadImage(const std::string& filename, int& aWidth, int& aHeight, int& aNumberOfComponents);
	GLuint LoadTexture(const std::string& filename);
	GLuint LoadTextureCubemap(const char** filenames, GLuint oldtexturehandle = 0);
	void Flip32BitImageVertically(unsigned char* buffer, unsigned int width, unsigned int height);
	GLint GetAttributeLocation(GLuint aShaderProgram, const char* aName);
	GLint GetUniformLocation(GLuint aShaderProgram, const char* aName);
	void SetUniform1f(GLuint aShaderProgram, const char* aName, float aValue);
	void SetUniform2f(GLuint aShaderProgram, const char* aName, Vector2Float aValue);
	void SetUniform1i(GLuint aShaderProgram, const char* aName, int aValue);
}
