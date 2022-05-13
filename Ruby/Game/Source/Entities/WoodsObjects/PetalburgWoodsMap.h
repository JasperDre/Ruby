#pragma once

#include "Entities/Level.h"

class ResourceManager;
class TileMap;
class Mesh;
class GameCore;
class Canvas;

class PetalburgWoodsMap : public Level
{
public:
	PetalburgWoodsMap(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier);
	~PetalburgWoodsMap() override;

	void Update(float deltatime) override {}
	void Draw(Vector2Float camPos, Vector2Float projecScale) override;
};
