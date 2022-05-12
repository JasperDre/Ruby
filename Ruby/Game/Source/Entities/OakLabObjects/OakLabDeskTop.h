#pragma once

#include "Entities/Entity.h"

#include <array>

class Mesh;
class ResourceManager;
class TileMap;

class OakLabDeskTop : public Entity
{
public:
	OakLabDeskTop(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~OakLabDeskTop() override;

	void Update(float deltatime) override {}
	void Draw(Vector2Float camPos, Vector2Float camProject) override;

private:
	std::vector<Frame> m_MyFrames;
	std::array<unsigned short, 6> OakHOakLabDeskMap;
	Vector2Float m_MyTileUVOffset;
	Vector2Float m_MyTileUVScale;
	Vector2Float OaklabDeskPosition;
	ResourceManager* m_MyResourceManager;
	TileMap* m_MyTileMap;
};