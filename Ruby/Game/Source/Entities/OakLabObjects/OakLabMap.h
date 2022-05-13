#pragma once

#include "Entities/Level.h"

class ResourceManager;
class TileMap;
class Mesh;
class GameCore;
class Canvas;

class OakLabMap : public Level
{
public:
	OakLabMap(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier);
	~OakLabMap() override;

	void Update(float deltatime) override {}
	void Draw(Vector2Float camPos, Vector2Float projecScale) override;
};