#pragma once

#include "Constants.h"

class TileMap;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void UnpackJson(const std::string& JSONfilename, TileMap* aTileMap);
	void HoldTexture(TextureHandle aTextureName, GLuint aTexture);

	[[nodiscard]] Frame GetFrameAtIndex(const std::string& anIndex) const;
	[[nodiscard]] ivec2 GetTextureSize(int anIndex) const;
	[[nodiscard]] GLuint GetaTexture(TextureHandle aTextureName) const;

protected:
	std::map<std::string, Frame> m_AnimationsMap;
	std::map<TextureHandle, GLuint> m_MyTextures;
	std::vector<ivec2> m_MyTextureSize;
	TileMap* m_MyTileMap;
};