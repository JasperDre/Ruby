#pragma once

class GameObject;
class Mesh;
class ResourceManager;
class TileMap;

class OakLabDeskTop : public GameObject
{
public:
	OakLabDeskTop(ResourceManager * myResourceManager, TileMap * myTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture);
	~OakLabDeskTop();

	virtual void Update(float deltatime) override;

	virtual void Draw(vec2 camPos, vec2 camProject) override;

private:

	const unsigned short OakHOakLabDeskMap[6]{ 11, 10, 9, 8, 7, 6};

	const unsigned short OakLabDesk_NumTiles = 6;

	ResourceManager* m_MyResourceManager;
	TileMap* m_MyTileMap;
	std::vector<Frame> m_MyFrames;

	vec2 m_MyTileUVOffset;
	vec2 m_MyTileUVScale;

	vec2 OaklabDeskPosition;
};