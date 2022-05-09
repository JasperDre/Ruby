#pragma once

#include "GameObjects/GameObject.h"

class Mesh;
class ResourceManager;
class TileMap;

class RivalHouse : public GameObject
{
public:
	RivalHouse(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~RivalHouse() override;

	void Update(float deltatime) override;
	void Draw(vec2 camPos, vec2 projecScale) override;

private:
	std::vector<Frame>m_MyFrames;
	const unsigned short RivalHouseMap[5] = { 0, 1, 2, 3, 4};
	const unsigned short RivalHouse_NumTiles = 5;
	vec2 m_MyTileUVOffset;
	vec2 m_MyTileUVScale;
	vec2 m_RivalHousePosition;
	ResourceManager* m_MyResourceManager;
	TileMap* m_MyTileMap;
};