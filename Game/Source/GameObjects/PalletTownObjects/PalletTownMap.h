#pragma once
class GameObject;
class ResourceManager;
class TileMap;
class Mesh;
class GameCore;
class Canvas;

class PalletTownMap : public GameObject
{
public:
	PalletTownMap(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~PalletTownMap();

	void Update(float deltatime);
	void Draw(vec2 camPos, vec2 projecScale);

private:

	TileMap* m_MyTileMap;
	ResourceManager* m_MyResourceManager;

	Canvas* m_MyCanvas;
};