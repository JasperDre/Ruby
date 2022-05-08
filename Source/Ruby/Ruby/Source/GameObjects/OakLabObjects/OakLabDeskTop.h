#pragma once

#include "GameObjects/GameObject.h"

class Mesh;
class ResourceManager;
class TileMap;

using namespace std;

class OakLabDeskTop : public GameObject
{
public:
	OakLabDeskTop(ResourceManager * myResourceManager, TileMap * myTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture);
	~OakLabDeskTop() override;

	void Update(float deltatime) override;
	void Draw(vec2 camPos, vec2 camProject) override;

private:
	vector<Frame> m_MyFrames;
	const unsigned short OakHOakLabDeskMap[6]{ 11, 10, 9, 8, 7, 6};
	const unsigned short OakLabDesk_NumTiles = 6;
	vec2 m_MyTileUVOffset;
	vec2 m_MyTileUVScale;
	vec2 OaklabDeskPosition;
	ResourceManager* m_MyResourceManager;
	TileMap* m_MyTileMap;
};