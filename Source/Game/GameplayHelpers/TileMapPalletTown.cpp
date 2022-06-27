#include "TileMapPalletTown.h"

#include <cassert>
#include <rapidjson/document.h>
#include <rapidjson/rapidjson.h>

#include "Events/DoorEvent.h"
#include "Events/EventManager.h"
#include "Game/Game.h"
#include "GameplayHelpers/TileMap.h"
#include "Utility/DebugUtility.h"
#include "Utility/FileUtility.h"

TileMapPalletTown::TileMapPalletTown(GameCore* aGameCore, Area anArea) : TileMap(aGameCore, anArea)
{
	for (int i = 0; i < 2; i++)
	{
		const PalletTownTileType type = static_cast<PalletTownTileType>(i + 13);
		TileInfo nullTile = TileInfo(type);

		if (nullTile.myType == PalletTownTileType::TownNullWall)
		{
			nullTile.myIsWalkable = false;
		}
		else
		{
			nullTile.myIsWalkable = true;
			nullTile.myIsDoor = true;
		}

		myTileInfoMap.insert(std::pair<PalletTownTileType, TileInfo>(static_cast<PalletTownTileType>(i + 13), nullTile));
	}
}

TileMapPalletTown::~TileMapPalletTown()
{
	myTileInfoMap.clear();
}

void TileMapPalletTown::LoadTileTypeMap(const std::string& aFilepath)
{
	const bool isFileValid = FileUtility::IsFileValid(aFilepath);
	assert(isFileValid);
	if (!isFileValid)
		return;

	const char* buffer = FileUtility::ReadFileIntoBuffer(aFilepath);
	rapidjson::Document document;
	document.Parse(buffer);
	if (document.HasParseError())
	{
		DebugUtility::OutputMessage("Failed to read json");
		return;
	}

	auto loadType = [&document](const char* aValueName, PalletTownTileType aType, std::map<std::string, PalletTownTileType>& aSelector)
	{
		const rapidjson::Value& oakHouse = document[aValueName];
		for (unsigned int i = 0; i < oakHouse.Size(); i++)
		{
			std::string tile = oakHouse[i].GetString();
			aSelector.insert(std::pair<std::string, PalletTownTileType>(tile, aType));
		}
	};

	loadType("OakHouse", PalletTownTileType::OakHouse, myPalletTownTypeSelecter);
	loadType("OakDoor", PalletTownTileType::OakDoor, myPalletTownTypeSelecter);
	loadType("TownFence", PalletTownTileType::TownFence, myPalletTownTypeSelecter);
	loadType("TownFlower", PalletTownTileType::TownFlower, myPalletTownTypeSelecter);
	loadType("TownGrassA", PalletTownTileType::TownGrassA, myPalletTownTypeSelecter);
	loadType("TownGrassB", PalletTownTileType::TownGrassB, myPalletTownTypeSelecter);
	loadType("TownMailBox", PalletTownTileType::TownMailBox, myPalletTownTypeSelecter);
	loadType("TownSign", PalletTownTileType::TownSign, myPalletTownTypeSelecter);
	loadType("TownTree", PalletTownTileType::TownTree, myPalletTownTypeSelecter);
	loadType("TrainerHouse", PalletTownTileType::TrainerHouse, myPalletTownTypeSelecter);
	loadType("PlayerDoor", PalletTownTileType::PlayerDoor, myPalletTownTypeSelecter);
	loadType("WaterA", PalletTownTileType::WaterA, myPalletTownTypeSelecter);
	loadType("WildGrass", PalletTownTileType::WildGrass, myPalletTownTypeSelecter);
}

void TileMapPalletTown::AddTile(const std::string& anIndex, const Frame& aFrame)
{
	if (myArea == Area::PalletTown)
	{
		//Find the Tile Type from the index string
		if (myPalletTownTypeSelecter.find(anIndex) == myPalletTownTypeSelecter.end())
			DebugUtility::OutputMessage("%s doesn't exist\n", anIndex.c_str());

		PalletTownTileType tileType = myPalletTownTypeSelecter.find(anIndex)->second;

		//Check to see if the TileInfo does not exists, if so make a new TileInfo
		if (myTileInfoMap.find(tileType) == myTileInfoMap.end())
		{
			TileInfo tile = TileInfo(tileType);
			if (tile.myType == PalletTownTileType::TownFlower || tile.myType == PalletTownTileType::TownGrassA || tile.myType == PalletTownTileType::TownGrassB || tile.myType == PalletTownTileType::WildGrass)
			{
				tile.myIsWalkable = true;
			}
			else if (tile.myType == PalletTownTileType::OakDoor || tile.myType == PalletTownTileType::PlayerDoor) //if the tile is a door
			{
				tile.myIsWalkable = true;
				tile.myIsDoor = true;
			}
			else
			{
				tile.myIsWalkable = false;
			}

			//push the frame attributes into the Variant vector
			tile.myVariant.push_back(aFrame);

			//insert the new TileInfo into the TileInfo Map
			myTileInfoMap.insert(std::pair<PalletTownTileType, TileInfo>(tileType, tile));
		}
		//if the TileInfo does exist then push back the new frame attributes into its variant vector
		else
		{
			myTileInfoMap.at(tileType).myVariant.push_back(aFrame);
		}
	}
}

TileInfo TileMapPalletTown::GetTileFromPalletTownMap(PalletTownTileType aType) const
{
	return myTileInfoMap.find(aType)->second;
}

bool TileMapPalletTown::IsTileAtPlayer(Vector2Int playerColumnRow) const
{
	const int anIndex = (NUM_COLUMNS * playerColumnRow.y) + playerColumnRow.x;
	constexpr short TypeMask = 15;
	const TileInfo aTileInfo = myTileInfoMap.find(static_cast<PalletTownTileType>(TypeMask & GetBitMap()[anIndex]))->second;

	if (aTileInfo.myType == PalletTownTileType::OakDoor)
	{
		Event* doorEvent = new DoorEvent(11);
		myGame->GetEventManager()->QueueEvent(doorEvent);
	}
	else if (aTileInfo.myType == PalletTownTileType::TownNullDoor)
	{
		Event* doorEvent = new DoorEvent(12);
		myGame->GetEventManager()->QueueEvent(doorEvent);
	}

	return aTileInfo.myIsWalkable;

}

bool TileMapPalletTown::IsTileAtNPC(Vector2Int npcColumnRow) const
{
	const int index = (NUM_COLUMNS * npcColumnRow.y) + npcColumnRow.x;
	constexpr short typeMask = 15;
	const TileInfo tileInfo = myTileInfoMap.find(static_cast<PalletTownTileType>(typeMask & GetBitMap()[index]))->second;

	return tileInfo.myIsWalkable;
}

TileInfo TileMapPalletTown::GetTileAtIndex(int anIndex) const
{
	constexpr short typeMask = 15;
	TileInfo tileInfo = myTileInfoMap.find(static_cast<PalletTownTileType>(typeMask & GetBitMap()[anIndex]))->second;

	return tileInfo;
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
	const int indexOnMap = (aRow * NUM_COLUMNS) + aColumn;

	return indexOnMap;
}

Vector2Int TileMapPalletTown::GetColumRowFromIndex(int anIndex) const
{
	return Vector2Int(anIndex % NUM_COLUMNS, anIndex / NUM_COLUMNS);
}
