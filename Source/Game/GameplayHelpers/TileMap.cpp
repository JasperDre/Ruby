#include "TileMap.h"

TileMap::TileMap(GameCore* aGameCore, Area aArea)
{
	myGame = aGameCore;
	myArea = aArea;
}

TileInfo TileMap::GetTileFromPalletTownMap(PalletTownTileType /*aType*/) const
{
	return TileInfo(static_cast<PalletTownTileType>(0));
}

TileInfo TileMap::GetTileFromOakLabMap(OakLabTileType /*aType*/) const
{
	return TileInfo(static_cast<OakLabTileType>(0));
}

TileInfo TileMap::GetTileFromWoodsMap(ForestTileType /*aType*/) const
{
	return TileInfo(static_cast<ForestTileType>(0));
}