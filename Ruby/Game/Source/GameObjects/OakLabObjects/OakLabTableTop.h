#pragma once

#include "GameObjects/GameObject.h"

class Mesh;
class ResourceManager;
class TileMap;

class OakLabTableTop : public GameObject
{
public:
	OakLabTableTop(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~OakLabTableTop() override;

	void Update(float deltatime) override;
	void Draw(vec2 camPos, vec2 camProject) override;

private:
	std::vector<Frame> m_MyFrames;
	const unsigned short OakLabTableTopMap[3] = { 3, 4, 5 };
	const unsigned short OakLabTableTop_NumTiles = 3;
	vec2 m_MyTileUVOffset;
	vec2 m_MyTileUVScale;
	vec2 OakLabTableTopPosition;
	ResourceManager* m_MyResourceManager;
	TileMap* m_MyTileMap;
};