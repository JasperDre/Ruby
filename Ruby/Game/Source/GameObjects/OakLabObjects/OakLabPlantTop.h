#pragma once

#include "GameObjects/GameObject.h"

#include <vector>

class Mesh;
class ResourceManager;
class TileMap;

class OakLabPlantTop : public GameObject
{
public:
	OakLabPlantTop(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~OakLabPlantTop() override;

	void Update(float deltatime) override;
	void Draw(vec2 camPos, vec2 camProject) override;

private:
	std::vector<Frame> m_MyFrames;
	const unsigned short OakLabPlantMap[2]{ 2, 3 };
	const unsigned short OakLabPlant_NumTiles = 2;
	vec2 m_MyTileUVOffset;
	vec2 m_MyTileUVScale;
	vec2 OaklabPlantPosition;
	ResourceManager* m_MyResourceManager;
	TileMap* m_MyTileMap;
};