#include "TileMap.h"

TileMap::TileMap(GameCore* aGameCore, Areas aArea)
{
	myGame = aGameCore;
	myArea = aArea;
}

TileInfo TileMap::GetTileFromPalletMap(Tile_Type /*aType*/) const
{
	return TileInfo(static_cast<Tile_Type>(0));
}

TileInfo TileMap::GetTileFromOakLabMap(OakLab_Tile_Type /*aType*/) const
{
	return TileInfo(static_cast<OakLab_Tile_Type>(0));
}

TileInfo TileMap::GetTileFromWoodsMap(Forest_Tile_Type /*aType*/) const
{
	return TileInfo(static_cast<Forest_Tile_Type>(0));
}