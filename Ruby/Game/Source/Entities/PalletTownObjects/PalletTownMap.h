#pragma once

#include "Entities/Entity.h"

class ResourceManager;
class TileMap;
class Mesh;
class GameCore;
class Canvas;

class PalletTownMap : public Entity
{
public:
	PalletTownMap(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~PalletTownMap() override;

	void Update(float deltatime) override {}
	void Draw(Vector2Float camPos, Vector2Float projecScale) override;

private:
	Canvas* m_MyCanvas;
	TileMap* m_MyTileMap;
	ResourceManager* m_MyResourceManager;
};