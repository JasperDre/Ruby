#pragma once

#include "GameObjects/Entity.h"

class Mesh;
class ResourceManager;
class TileMap;

class OakLabDeskTop : public Entity
{
public:
	OakLabDeskTop(ResourceManager * myResourceManager, TileMap * myTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture);
	~OakLabDeskTop() override;

	void Update(float deltatime) override;
	void Draw(Vector2Float camPos, Vector2Float camProject) override;

private:
	std::vector<Frame> m_MyFrames;
	const unsigned short OakHOakLabDeskMap[6]{ 11, 10, 9, 8, 7, 6};
	const unsigned short OakLabDesk_NumTiles = 6;
	Vector2Float m_MyTileUVOffset;
	Vector2Float m_MyTileUVScale;
	Vector2Float OaklabDeskPosition;
	ResourceManager* m_MyResourceManager;
	TileMap* m_MyTileMap;
};