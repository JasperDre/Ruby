#pragma once

#include "GameObjects/GameObject.h"

class ResourceManager;
class TileMap;
class Mesh;
class GameCore;
class Canvas;

class PetalburgWoodsMap : public GameObject
{
public:
	PetalburgWoodsMap(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~PetalburgWoodsMap();

	void Update(float deltatime);
	void Draw(vec2 camPos, vec2 projecScale);

private:

	TileMap* m_MyTileMap;
	ResourceManager* m_MyResourceManager;

	Canvas* m_MyCanvas;
};
