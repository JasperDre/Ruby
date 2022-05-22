#pragma once

#include <map>
#include <string>
#include <vector>

#include "Constants.h"
#include "Frame.h"
#include "Math/Vector2Int.h"

class TileMap;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void UnpackJson(const std::string& aFilepath, TileMap* aTileMap);
	void HoldTexture(TextureHandle aTextureName, unsigned int aTexture);

	[[nodiscard]] Frame GetFrameAtIndex(const std::string& anIndex) const;
	[[nodiscard]] Vector2Int GetTextureSize(int anIndex) const;
	[[nodiscard]] unsigned int GetTexture(TextureHandle aTextureName) const;
	[[nodiscard]] const std::map<TextureHandle, unsigned int>& GetTextures() const { return myTextures; }

protected:
	std::map<std::string, Frame> myAnimationsMap;
	std::map<TextureHandle, unsigned int> myTextures;
	std::vector<Vector2Int> myTextureSizes;
	TileMap* myTileMap;
};