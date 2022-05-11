#pragma once

#include "Entities/Entity.h"

class Mesh;
class ResourceManager;
class TileMap;

class OakLabTableTop : public Entity
{
public:
	OakLabTableTop(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~OakLabTableTop() override;

	void Update(float deltatime) override;
	void Draw(Vector2Float camPos, Vector2Float camProject) override;

private:
	std::vector<Frame> m_MyFrames;
	const unsigned short OakLabTableTopMap[3] = { 3, 4, 5 };
	const unsigned short OakLabTableTop_NumTiles = 3;
	Vector2Float m_MyTileUVOffset;
	Vector2Float m_MyTileUVScale;
	Vector2Float OakLabTableTopPosition;
	ResourceManager* m_MyResourceManager;
	TileMap* m_MyTileMap;
};