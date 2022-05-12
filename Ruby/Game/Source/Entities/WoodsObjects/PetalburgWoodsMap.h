#pragma once

#include "Entities/Entity.h"

class ResourceManager;
class TileMap;
class Mesh;
class GameCore;
class Canvas;

class PetalburgWoodsMap : public Entity
{
public:
	PetalburgWoodsMap(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~PetalburgWoodsMap() override;

	void Update(float deltatime) override {}
	void Draw(Vector2Float camPos, Vector2Float projecScale) override;

private:
	TileMap* m_MyTileMap;
	ResourceManager* m_MyResourceManager;
	Canvas* m_MyCanvas;
};
