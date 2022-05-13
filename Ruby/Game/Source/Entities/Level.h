#pragma once

#include "Entities/Entity.h"

class Canvas;
class TileMap;

class Level : public Entity
{
public:
	Level(TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier);
	~Level() override = default;

protected:
	TileMap* myTileMap;
	Canvas* myCanvas;
};
