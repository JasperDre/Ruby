#pragma once
class Entity;
class Mesh;
class ResourceManager;
class TileMap;

class PlayerHouse : public Entity
{
public:
	PlayerHouse(ResourceManager* aSpriteMap, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~PlayerHouse();

	void Update(float deltatime);

	void Draw(vec2 camPos, vec2 projecScale);


private:
	std::vector<Frame>m_MyFrames;
	const unsigned short PlayerHouseMap[5] = {	0, 1, 2, 3, 4};
	const unsigned short PlayerHouse_NumTiles = 5;
	ResourceManager* m_MyResourceManager;
	TileMap* m_MyTileMap;
	vec2 m_MyTileUVOffset;
	vec2 m_MyTileUVScale;
	vec2 m_PlayerHousePosition;
};