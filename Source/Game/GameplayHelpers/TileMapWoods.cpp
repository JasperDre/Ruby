#include "GamePCH.h"

#include "GameplayHelpers/TileMap.h"
#include "TileMapWoods.h"

#include "Game/Game.h"

TileMapWoods::TileMapWoods(GameCore* myGame, Areas anArea)
	: TileMap(myGame, anArea)
{
	for (int i = 0; i < 2; i++)
	{
		const Forest_Tile_Type aType = static_cast<Forest_Tile_Type>(i + 6);

		TileInfo aNullTile = TileInfo(aType);

		if (aNullTile.MyForestType == Forest_Null_Wall)
		{
			aNullTile.IsWalkable = false;
		}
		else
		{
			aNullTile.IsWalkable = true;
			aNullTile.IsDoor = true;
		}

		myTileInfoMap.insert(std::pair<Forest_Tile_Type, TileInfo>(static_cast<Forest_Tile_Type>(i + 6), aNullTile));
	}
}

TileMapWoods::~TileMapWoods()
{
	myTileInfoMap.clear();
}

void TileMapWoods::AddTile(const std::string& anIndex, Frame aFrame)
{
	if (m_MyArea == Areas::Area_Woods)
	{
		//Find the Tile Type from the index string
		Forest_Tile_Type aType = WoodsTypeSelecter.find(anIndex)->second;

		//Check to see if the TileInfo does not exists, if so make a new TileInfo
		if (myTileInfoMap.find(aType) == myTileInfoMap.end())
		{

			TileInfo myNewTile = TileInfo(aType);

			if (myNewTile.MyForestType == Forest_Grass_ || myNewTile.MyForestType == Forest_Wild_Grass_)
			{
				myNewTile.IsWalkable = true;
			}
			else if (myNewTile.MyForestType == Forest_Null_Door) //if the tile is a door
			{
				myNewTile.IsWalkable = true;
				myNewTile.IsDoor = true;
			}
			else
			{
				myNewTile.IsWalkable = false;
			}

			//push the frame attributes into the Variant vector
			myNewTile.MyVariant.push_back(aFrame);

			//insert the new TileInfo into the TileInfo Map
			myTileInfoMap.insert(std::pair<Forest_Tile_Type, TileInfo>(aType, myNewTile));
		}
		//if the TileInfo does exist then push back the new frame attributes into its variant vector
		else
		{
			myTileInfoMap.at(aType).MyVariant.push_back(aFrame);
		}
	}
}

TileInfo TileMapWoods::GetTileFromWoodsMap(Forest_Tile_Type aType) const
{
	return myTileInfoMap.find(aType)->second;
}

bool TileMapWoods::GetTileAtPlayer(Vector2Int playerColumnRow) const
{
	const int anIndex = (NUM_FOREST_COLUMNS * playerColumnRow.y) + playerColumnRow.x;
	constexpr short TypeMask = 15;
	const TileInfo aTileInfo = myTileInfoMap.find(static_cast<Forest_Tile_Type>(TypeMask & ForestBitMap[anIndex]))->second;

	if (aTileInfo.MyForestType == Forest_Null_Door)
	{
		Event* doorEvent = new DoorEvent(13);
		m_pMyGame->GetEventManager()->QueueEvent(doorEvent);
	}

	return aTileInfo.IsWalkable;

}

bool TileMapWoods::GetTileAtNPC(Vector2Int npcColumnRow) const
{
	const int anIndex = (NUM_COLUMNS * npcColumnRow.y) + npcColumnRow.x;
	constexpr short TypeMask = 15;
	const TileInfo aTileInfo = myTileInfoMap.find(static_cast<Forest_Tile_Type>(TypeMask & ForestBitMap[anIndex]))->second;

	return aTileInfo.IsWalkable;
}

TileInfo TileMapWoods::GetTileAtIndex(int anIndex) const
{
	constexpr short TypeMask = 15;
	TileInfo aTileInfo = myTileInfoMap.find(static_cast<Forest_Tile_Type>(TypeMask & ForestBitMap[anIndex]))->second;

	return aTileInfo;
}

int TileMapWoods::GetMapWidth() const
{
	return NUM_FOREST_COLUMNS;
}

int TileMapWoods::GetMapHeight() const
{
	return NUM_FOREST_ROWS;
}

int TileMapWoods::GetIndexFromColumnRow(int aColumn, int aRow) const
{
	assert(aColumn >= 0 && aRow >= 0 && aColumn <= NUM_FOREST_COLUMNS && aRow <= NUM_FOREST_ROWS);
	const int anIndexOnMap = (aRow * NUM_FOREST_COLUMNS) + aColumn;

	return anIndexOnMap;
}

Vector2Int TileMapWoods::GetColumRowFromIndex(int anIndex) const
{
	return Vector2Int(anIndex % NUM_FOREST_COLUMNS, anIndex / NUM_FOREST_COLUMNS);
}

