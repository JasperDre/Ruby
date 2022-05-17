#include "Sprite.h"

Sprite::Sprite(TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier)
	: Entity(aGameCore, aMesh, aTextureIdentifier)
	, myTileUVOffset(0.0f)
	, myTileUVScale(0.0f)
	, myTileMap(aTileMap)
{}
