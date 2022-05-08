#pragma once
class GameObject;
class ResourceManager;
class TileMap;
class Mesh;
class GameCore;
class Canvas;

class OakLabMap : public GameObject
{
public:
	OakLabMap(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~OakLabMap();

	void Update(float deltatime);
	void Draw(vec2 camPos, vec2 projecScale);

private:

	TileMap* m_MyTileMap;
	ResourceManager* m_MyResourceManager;

	Canvas* m_MyCanvas;
};