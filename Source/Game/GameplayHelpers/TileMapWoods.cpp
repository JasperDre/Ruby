#include "TileMapWoods.h"

#include <cassert>

#include "Events/DoorEvent.h"
#include "Events/EventManager.h"
#include "Game/Game.h"
#include "GameplayHelpers/TileMap.h"

TileMapWoods::TileMapWoods(GameCore* aGameCore, Area anArea)
	: TileMap(aGameCore, anArea)
{
	for (int i = 0; i < 2; i++)
	{
		const ForestTileType aType = static_cast<ForestTileType>(i + 6);

		TileInfo aNullTile = TileInfo(aType);

		if (aNullTile.myForestType == ForestTileType::ForestNullWall)
		{
			aNullTile.myIsWalkable = false;
		}
		else
		{
			aNullTile.myIsWalkable = true;
			aNullTile.myIsDoor = true;
		}

		myTileInfoMap.insert(std::pair<ForestTileType, TileInfo>(static_cast<ForestTileType>(i + 6), aNullTile));
	}
}

TileMapWoods::~TileMapWoods()
{
	myTileInfoMap.clear();
}

void TileMapWoods::AddTile(const std::string& anIndex, const Frame& aFrame)
{
	if (myArea == Area::Woods)
	{
		//Find the Tile Type from the index string
		ForestTileType aType = myWoodsTypeSelecter.find(anIndex)->second;

		//Check to see if the TileInfo does not exists, if so make a new TileInfo
		if (myTileInfoMap.find(aType) == myTileInfoMap.end())
		{

			TileInfo myNewTile = TileInfo(aType);

			if (myNewTile.myForestType == ForestTileType::ForestGrass || myNewTile.myForestType == ForestTileType::ForestWildGrass)
			{
				myNewTile.myIsWalkable = true;
			}
			else if (myNewTile.myForestType == ForestTileType::ForestNullDoor) //if the tile is a door
			{
				myNewTile.myIsWalkable = true;
				myNewTile.myIsDoor = true;
			}
			else
			{
				myNewTile.myIsWalkable = false;
			}

			//push the frame attributes into the Variant vector
			myNewTile.myVariant.push_back(aFrame);

			//insert the new TileInfo into the TileInfo Map
			myTileInfoMap.insert(std::pair<ForestTileType, TileInfo>(aType, myNewTile));
		}
		//if the TileInfo does exist then push back the new frame attributes into its variant vector
		else
		{
			myTileInfoMap.at(aType).myVariant.push_back(aFrame);
		}
	}
}

TileInfo TileMapWoods::GetTileFromWoodsMap(ForestTileType aType) const
{
	return myTileInfoMap.find(aType)->second;
}

bool TileMapWoods::IsTileAtPlayer(Vector2Int playerColumnRow) const
{
	const int anIndex = (NUM_FOREST_COLUMNS * playerColumnRow.y) + playerColumnRow.x;
	constexpr short TypeMask = 15;
	const TileInfo aTileInfo = myTileInfoMap.find(static_cast<ForestTileType>(TypeMask & GetBitMap()[anIndex]))->second;

	if (aTileInfo.myForestType == ForestTileType::ForestNullDoor)
	{
		Event* doorEvent = new DoorEvent(13);
		myGame->GetEventManager()->QueueEvent(doorEvent);
	}

	return aTileInfo.myIsWalkable;
}

bool TileMapWoods::IsTileAtNPC(Vector2Int npcColumnRow) const
{
	const int index = (NUM_COLUMNS * npcColumnRow.y) + npcColumnRow.x;
	constexpr short typeMask = 15;
	const TileInfo tileInfo = myTileInfoMap.find(static_cast<ForestTileType>(typeMask & GetBitMap()[index]))->second;

	return tileInfo.myIsWalkable;
}

TileInfo TileMapWoods::GetTileAtIndex(int anIndex) const
{
	constexpr short typeMask = 15;
	TileInfo tileInfo = myTileInfoMap.find(static_cast<ForestTileType>(typeMask & GetBitMap()[anIndex]))->second;

	return tileInfo;
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
