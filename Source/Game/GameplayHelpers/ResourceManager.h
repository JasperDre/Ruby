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
	[[nodiscard]] Vector2Int GetTextureSize(int anIndex) const;
	[[nodiscard]] GLuint GetaTexture(TextureHandle aTextureName) const;

protected:
	std::map<std::string, Frame> myAnimationsMap;
	std::map<TextureHandle, GLuint> myTextures;
	std::vector<Vector2Int> myTextureSize;
	TileMap* myTileMap;
};