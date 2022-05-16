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
}
