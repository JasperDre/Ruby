#include "GamePCH.h"
#include "TileMap.h"

#include "GameplayHelpers/ResourceManager.h"

TileMap::TileMap(GameCore* myGame, Areas aArea)
{
	m_pMyGame = myGame;
	m_MyArea = aArea;
}

TileInfo TileMap::GetTileFromPalletMap(Tile_Type aType)
{
	return TileInfo(Tile_Type(0));
}

TileInfo TileMap::GetTileFromOakLabMap(OakLab_Tile_Type aType)
{
	return TileInfo(OakLab_Tile_Type(0));
}

TileInfo TileMap::GetTileFromWoodsMap(Forest_Tile_Type aType)
{
	return TileInfo(Forest_Tile_Type(0));
}