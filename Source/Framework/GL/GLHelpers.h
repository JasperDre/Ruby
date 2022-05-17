#pragma once

#include <string>
#include <glad/glad.h>

#include "Math/Vector2Float.h"

namespace GLHelpers
{
	void CheckForGLErrors();
	void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, unsigned int id, GLenum severity, int length, const char* message, const void* userParam);
	void GLFWErrorCallback(int anError, const char* aDescription);
	unsigned char* LoadImage(const std::string& filename, int& aWidth, int& aHeight, int& aNumberOfComponents);
	unsigned int LoadTexture(const std::string& filename);
	unsigned int LoadTextureCubemap(const char** filenames, unsigned int oldtexturehandle = 0);
	void Flip32BitImageVertically(unsigned char* buffer, unsigned int width, unsigned int height);
	int GetAttributeLocation(unsigned int aShaderProgram, const char* aName);
	int GetUniformLocation(unsigned int aShaderProgram, const char* aName);
	void SetUniform1f(unsigned int aShaderProgram, const char* aName, float aValue);
	void SetUniform2f(unsigned int aShaderProgram, const char* aName, Vector2Float aValue);
	void SetUniform1i(unsigned int aShaderProgram, const char* aName, int aValue);
}
