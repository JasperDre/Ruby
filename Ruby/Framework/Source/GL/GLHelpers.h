#pragma once

#include <string>

namespace GLHelpers
{
	void CheckForGLErrors();
	GLuint LoadTexture(const std::string& filename);
	GLuint LoadTextureCubemap(const char** filenames, GLuint oldtexturehandle = 0);
	void Flip32BitImageVertically(unsigned char* buffer, unsigned int width, unsigned int height);
}
