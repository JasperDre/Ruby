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
		const ForestTileType type = static_cast<ForestTileType>(i + 6);
		TileInfo nullTile = TileInfo(type);

		if (nullTile.myForestType == ForestTileType::ForestNullWall)
		{
			nullTile.myIsWalkable = false;
		}
		else
		{
			nullTile.myIsWalkable = true;
			nullTile.myIsDoor = true;
		}

		myTileInfoMap.insert(std::pair<ForestTileType, TileInfo>(static_cast<ForestTileType>(i + 6), nullTile));
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
		ForestTileType type = myWoodsTypeSelecter.find(anIndex)->second;

		//Check to see if the TileInfo does not exists, if so make a new TileInfo
		if (myTileInfoMap.find(type) == myTileInfoMap.end())
		{
			TileInfo tileInfo = TileInfo(type);

			if (tileInfo.myForestType == ForestTileType::ForestGrass || tileInfo.myForestType == ForestTileType::ForestWildGrass)
			{
				tileInfo.myIsWalkable = true;
			}
			else if (tileInfo.myForestType == ForestTileType::ForestNullDoor) //if the tile is a door
			{
				tileInfo.myIsWalkable = true;
				tileInfo.myIsDoor = true;
			}
			else
			{
				tileInfo.myIsWalkable = false;
			}

			//push the frame attributes into the Variant vector
			tileInfo.myVariant.push_back(aFrame);

			//insert the new TileInfo into the TileInfo Map
			myTileInfoMap.insert(std::pair<ForestTileType, TileInfo>(type, tileInfo));
		}
		//if the TileInfo does exist then push back the new frame attributes into its variant vector
		else
		{
			myTileInfoMap.at(type).myVariant.push_back(aFrame);
		}
	}
}

TileInfo TileMapWoods::GetTileFromWoodsMap(ForestTileType aType) const
{
	return myTileInfoMap.find(aType)->second;
}

bool TileMapWoods::IsTileAtPlayer(Vector2Int playerColumnRow) const
{
	const int index = (NUM_FOREST_COLUMNS * playerColumnRow.y) + playerColumnRow.x;
	constexpr short typeMask = 15;
	const TileInfo tileInfo = myTileInfoMap.find(static_cast<ForestTileType>(typeMask & GetBitMap()[index]))->second;

	if (tileInfo.myForestType == ForestTileType::ForestNullDoor)
	{
		Event* doorEvent = new DoorEvent(13);
		myGame->GetEventManager()->QueueEvent(doorEvent);
	}

	return tileInfo.myIsWalkable;
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
	const int indexOnMap = (aRow * NUM_FOREST_COLUMNS) + aColumn;

	return indexOnMap;
}

Vector2Int TileMapWoods::GetColumRowFromIndex(int anIndex) const
{
	return Vector2Int(anIndex % NUM_FOREST_COLUMNS, anIndex / NUM_FOREST_COLUMNS);
}
