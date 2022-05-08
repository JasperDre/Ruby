#pragma once

#include "GameObjects/GameObject.h"

class Mesh;
class ResourceManager;
class TileMap;

class PlayerHouse : public GameObject
{
public:
	PlayerHouse(ResourceManager* aResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~PlayerHouse() override;

	void Update(float deltatime) override {}

	void Draw(vec2 camPos, vec2 projecScale) override;

private:
	std::vector<Frame>m_MyFrames;
	const unsigned short PlayerHouseMap[5] = {	0, 1, 2, 3, 4};
	const unsigned short PlayerHouse_NumTiles = 5;
	vec2 m_MyTileUVOffset;
	vec2 m_MyTileUVScale;
	vec2 m_PlayerHousePosition;
	TileMap* m_MyTileMap;
	ResourceManager* m_MyResourceManager;
};