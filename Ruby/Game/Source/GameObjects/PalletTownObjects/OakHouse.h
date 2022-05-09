#pragma once

#include "GameObjects/GameObject.h"

class Mesh;
class ResourceManager;
class TileMap;


class OakHouse : public GameObject
{
public:
	OakHouse(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~OakHouse() override;

	void Update(float deltatime) override {}
	void Draw(vec2 camPos, vec2 projecScale) override;

private:
	std::vector<Frame> m_MyFrames;
	const unsigned short OakHouseMap[7]{ 0, 1, 2, 3, 4, 5, 6 };
	const unsigned short OakHouse_NumTiles = 7;
	vec2 m_MyTileUVOffset;
	vec2 m_MyTileUVScale;
	vec2 OakHousePosition;
	ResourceManager* m_MyResourceManager;
	TileMap* m_MyTileMap;
};
