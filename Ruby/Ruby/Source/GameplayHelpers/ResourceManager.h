#pragma once
#include "Constants.h"

class TileMap;

using namespace std;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	void UnpackJson(const std::string& JSONfilename, TileMap* aTileMap);
	 
	Frame GetFrameat(const std::string& anIndex);

	ivec2 GetTextureSize(int anIndex);

	GLuint GetaTexture(TextureHandle aTextureName);

	void HoldTexture(TextureHandle aTextureName, GLuint aTexture);

protected:

	TileMap* m_MyTileMap;;
	map<string, Frame> m_AnimationsMap;
	
	map<TextureHandle, GLuint>m_MyTextures;

	vector<ivec2>m_MyTextureSize;

};