#pragma once

#include "Entities/Entity.h"

#include <array>

class Mesh;
class ResourceManager;
class TileMap;

class OakLabPlantTop : public Entity
{
public:
	OakLabPlantTop(ResourceManager* aResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~OakLabPlantTop() override;

	void Update(float deltatime) override {}
	void Draw(Vector2Float camPos, Vector2Float camProject) override;

private:
	std::vector<Frame> m_MyFrames;
	std::array<unsigned short, 2> OakLabPlantMap;
	Vector2Float m_MyTileUVOffset;
	Vector2Float m_MyTileUVScale;
	Vector2Float OaklabPlantPosition;
	TileMap* m_MyTileMap;
};