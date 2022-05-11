#pragma once

#include "Entities/Entity.h"

class Mesh;
class ResourceManager;
class TileMap;

class RivalHouse : public Entity
{
public:
	RivalHouse(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~RivalHouse() override;

	void Update(float deltatime) override;
	void Draw(Vector2Float camPos, Vector2Float projecScale) override;

private:
	std::vector<Frame>m_MyFrames;
	const unsigned short RivalHouseMap[5] = { 0, 1, 2, 3, 4};
	const unsigned short RivalHouse_NumTiles = 5;
	Vector2Float m_MyTileUVOffset;
	Vector2Float m_MyTileUVScale;
	Vector2Float m_RivalHousePosition;
	ResourceManager* m_MyResourceManager;
	TileMap* m_MyTileMap;
};