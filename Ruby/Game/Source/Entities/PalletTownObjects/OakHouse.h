#pragma once

#include "Entities/Entity.h"

#include <array>

class Mesh;
class ResourceManager;
class TileMap;

class OakHouse : public Entity
{
public:
	OakHouse(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~OakHouse() override;

	void Update(float deltatime) override {}
	void Draw(Vector2Float camPos, Vector2Float projecScale) override;

private:
	std::vector<Frame> m_MyFrames;
	std::array<unsigned short, 7> OakHouseMap;
	Vector2Float m_MyTileUVOffset;
	Vector2Float m_MyTileUVScale;
	Vector2Float OakHousePosition;
	ResourceManager* m_MyResourceManager;
	TileMap* m_MyTileMap;
};
