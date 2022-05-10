#pragma once

#include "GameObjects/GameObject.h"

class ResourceManager;
class TileMap;
class Mesh;
class GameCore;
class Canvas;

class PalletTownMap : public GameObject
{
public:
	PalletTownMap(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~PalletTownMap() override;

	void Update(float deltatime) override;
	void Draw(vec2 camPos, vec2 projecScale) override;

private:
	Canvas* m_MyCanvas;
	TileMap* m_MyTileMap;
	ResourceManager* m_MyResourceManager;
};