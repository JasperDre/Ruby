#include "GamePCH.h"
#include "Level.h"

Level::Level(TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier)
	: Entity(aGameCore, aMesh, aTextureIdentifier)
	, myTileMap(aTileMap)
	, myCanvas(nullptr)
{}
