#pragma once

#include "Constants.h"

class TileMap;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void UnpackJson(const std::string& JSONfilename, TileMap* aTileMap);
	 
	Frame GetFrameat(const std::string& anIndex) const;

	ivec2 GetTextureSize(int anIndex) const;

	GLuint GetaTexture(TextureHandle aTextureName) const;

	void HoldTexture(TextureHandle aTextureName, GLuint aTexture);

protected:
	std::map<std::string, Frame> m_AnimationsMap;
	std::map<TextureHandle, GLuint> m_MyTextures;
	std::vector<ivec2> m_MyTextureSize;
	TileMap* m_MyTileMap;
};