#include "TileMapPalletTown.h"

#include <cassert>

#include "Events/DoorEvent.h"
#include "Events/EventManager.h"
#include "Game/Game.h"
#include "GameplayHelpers/TileMap.h"

TileMapPalletTown::TileMapPalletTown(GameCore* aGameCore, Area anArea) : TileMap(aGameCore, anArea)
{
	for (int i = 0; i < 2; i++)
	{
		const Tile_Type aType = static_cast<Tile_Type>(i + 13);
		TileInfo aNullTile = TileInfo(aType);

		if (aNullTile.myType == Town_Null_Wall_)
		{
			aNullTile.myIsWalkable = false;
		}
		else
		{
			aNullTile.myIsWalkable = true;
			aNullTile.myIsDoor = true;
		}

		myTileInfoMap.insert(std::pair<Tile_Type, TileInfo>(static_cast<Tile_Type>(i + 13), aNullTile));
	}
}

TileMapPalletTown::~TileMapPalletTown()
{
	myTileInfoMap.clear();
}

void TileMapPalletTown::AddTile(const std::string& anIndex, const Frame& aFrame)
{
	if (myArea == Area::PalletTown)
	{
		//Find the Tile Type from the index string
		Tile_Type aType = TypeSelecter.find(anIndex)->second;

		//Check to see if the TileInfo does not exists, if so make a new TileInfo
		if (myTileInfoMap.find(aType) == myTileInfoMap.end())
		{

			TileInfo myNewTile = TileInfo(aType);

			if (myNewTile.myType == Town_Flower_ || myNewTile.myType == Town_Grass_A_ || myNewTile.myType == Town_Grass_B_ || myNewTile.myType == Wild_Grass_)
			{
				myNewTile.myIsWalkable = true;
			}
			else if (myNewTile.myType == Oak_Door_ || myNewTile.myType == Player_Door_) //if the tile is a door
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
			myTileInfoMap.insert(std::pair<Tile_Type, TileInfo>(aType, myNewTile));
		}
		//if the TileInfo does exist then push back the new frame attributes into its variant vector
		else
		{
			myTileInfoMap.at(aType).myVariant.push_back(aFrame);
		}
	}
}

TileInfo TileMapPalletTown::GetTileFromPalletMap(Tile_Type aType) const
{
	return myTileInfoMap.find(aType)->second;
}

bool TileMapPalletTown::IsTileAtPlayer(Vector2Int playerColumnRow) const
{
	const int anIndex = (NUM_COLUMNS * playerColumnRow.y) + playerColumnRow.x;
	constexpr short TypeMask = 15;
	const TileInfo aTileInfo = myTileInfoMap.find(static_cast<Tile_Type>(TypeMask & GetBitMap()[anIndex]))->second;

	if (aTileInfo.myType == Oak_Door_)
	{
		Event* doorEvent = new DoorEvent(11);
		myGame->GetEventManager()->QueueEvent(doorEvent);
	}
	else if (aTileInfo.myType == Town_Null_Door_)
	{
		Event* doorEvent = new DoorEvent(12);
		myGame->GetEventManager()->QueueEvent(doorEvent);
	}

	return aTileInfo.myIsWalkable;

}

bool TileMapPalletTown::IsTileAtNPC(Vector2Int npcColumnRow) const
{
	const int anIndex = (NUM_COLUMNS * npcColumnRow.y) + npcColumnRow.x;
	constexpr short TypeMask = 15;
	const TileInfo aTileInfo = myTileInfoMap.find(static_cast<Tile_Type>(TypeMask & GetBitMap()[anIndex]))->second;

	return aTileInfo.myIsWalkable;
}

TileInfo TileMapPalletTown::GetTileAtIndex(int anIndex) const
{
	constexpr short TypeMask = 15;
	TileInfo aTileInfo = myTileInfoMap.find(static_cast<Tile_Type>(TypeMask & GetBitMap()[anIndex]))->second;

	return aTileInfo;
}

int TileMapPalletTown::GetMapWidth() const
{
	return NUM_COLUMNS;
}

int TileMapPalletTown::GetMapHeight() const
{
	return NUM_ROWS;
}

int TileMapPalletTown::GetIndexFromColumnRow(int aColumn, int aRow) const
{
	assert(aColumn >= 0 && aRow >= 0 && aColumn <= NUM_COLUMNS && aRow <= NUM_COLUMNS);
	const int anIndexOnMap = (aRow * NUM_COLUMNS) + aColumn;

	return anIndexOnMap;
}

Vector2Int TileMapPalletTown::GetColumRowFromIndex(int anIndex) const
{
	return Vector2Int(anIndex % NUM_COLUMNS, anIndex / NUM_COLUMNS);
}
