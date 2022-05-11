#pragma once

#include "GameObjects/Entity.h"

#include <vector>

class Mesh;
class ResourceManager;
class TileMap;

class OakLabPlantTop : public Entity
{
public:
	OakLabPlantTop(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~OakLabPlantTop() override;

	void Update(float deltatime) override;
	void Draw(Vector2Float camPos, Vector2Float camProject) override;

private:
	std::vector<Frame> m_MyFrames;
	const unsigned short OakLabPlantMap[2]{ 2, 3 };
	const unsigned short OakLabPlant_NumTiles = 2;
	Vector2Float m_MyTileUVOffset;
	Vector2Float m_MyTileUVScale;
	Vector2Float OaklabPlantPosition;
	ResourceManager* m_MyResourceManager;
	TileMap* m_MyTileMap;
};