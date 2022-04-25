#pragma once

#include "../Entity.h"

class ResourceManager;
class TileMap;
class Mesh;
class GameCore;
class Canvas;

class PalletTownMap final : public Entity
{
public:
	PalletTownMap(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~PalletTownMap() override;

	void Update(float deltatime) override;
	void Draw(vec2 camPos, vec2 projecScale) override;

private:
	TileMap* m_MyTileMap;
	ResourceManager* m_MyResourceManager;
	Canvas* m_MyCanvas;
};