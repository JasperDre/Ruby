#pragma once

#include "Entities/Entity.h"

#include <array>

class Mesh;
class ResourceManager;
class TileMap;

class RivalHouse : public Entity
{
public:
	RivalHouse(ResourceManager* aResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~RivalHouse() override;

	void Update(float deltatime) override {}
	void Draw(Vector2Float camPos, Vector2Float projecScale) override;

private:
	std::vector<Frame>m_MyFrames;
	std::array<unsigned short, 5> RivalHouseMap;
	Vector2Float m_MyTileUVOffset;
	Vector2Float m_MyTileUVScale;
	Vector2Float m_RivalHousePosition;
	TileMap* m_MyTileMap;
};