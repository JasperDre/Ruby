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
	const bool isFileValid = FileUtility::IsFileValid("Data/TileTypes/PalletTownTileTypes.json");
	assert(isFileValid);
	if (!isFileValid)
		return;

	const char* buffer = FileUtility::ReadFileIntoBuffer("Data/TileTypes/PalletTownTileTypes.json");
	rapidjson::Document document;
	document.Parse(buffer);
	if (document.HasParseError())
	{
		DebugUtility::OutputMessage("Failed to read json");
		return;
	}

	const rapidjson::Value& oakHouse = document["OakHouse"];
	for (unsigned int i = 0; i < oakHouse.Size(); i++)
	{
		std::string tile = oakHouse[i].GetString();
		myPalletTownTypeSelecter.insert(std::pair<std::string, PalletTownTileType>(tile, PalletTownTileType::OakHouse));
	}

	const rapidjson::Value& oakDoor = document["OakDoor"];
	for (unsigned int i = 0; i < oakDoor.Size(); i++)
	{
		std::string tile = oakDoor[i].GetString();
		myPalletTownTypeSelecter.insert(std::pair<std::string, PalletTownTileType>(tile, PalletTownTileType::OakDoor));
	}

	const rapidjson::Value& townFence = document["TownFence"];
	for (unsigned int i = 0; i < townFence.Size(); i++)
	{
		std::string tile = townFence[i].GetString();
		myPalletTownTypeSelecter.insert(std::pair<std::string, PalletTownTileType>(tile, PalletTownTileType::TownFence));
	}

	const rapidjson::Value& townFlower = document["TownFlower"];
	for (unsigned int i = 0; i < townFlower.Size(); i++)
	{
		std::string tile = townFlower[i].GetString();
		myPalletTownTypeSelecter.insert(std::pair<std::string, PalletTownTileType>(tile, PalletTownTileType::TownFlower));
	}

	const rapidjson::Value& townGrassA = document["TownGrassA"];
	for (unsigned int i = 0; i < townGrassA.Size(); i++)
	{
		std::string tile = townGrassA[i].GetString();
		myPalletTownTypeSelecter.insert(std::pair<std::string, PalletTownTileType>(tile, PalletTownTileType::TownGrassA));
	}

	const rapidjson::Value& townGrassB = document["TownGrassB"];
	for (unsigned int i = 0; i < townGrassB.Size(); i++)
	{
		std::string tile = townGrassB[i].GetString();
		myPalletTownTypeSelecter.insert(std::pair<std::string, PalletTownTileType>(tile, PalletTownTileType::TownGrassB));
	}

	const rapidjson::Value& townMailBox = document["TownMailBox"];
	for (unsigned int i = 0; i < townMailBox.Size(); i++)
	{
		std::string tile = townMailBox[i].GetString();
		myPalletTownTypeSelecter.insert(std::pair<std::string, PalletTownTileType>(tile, PalletTownTileType::TownMailBox));
	}

	const rapidjson::Value& townSign = document["TownSign"];
	for (unsigned int i = 0; i < townSign.Size(); i++)
	{
		std::string tile = townSign[i].GetString();
		myPalletTownTypeSelecter.insert(std::pair<std::string, PalletTownTileType>(tile, PalletTownTileType::TownSign));
	}

	const rapidjson::Value& townTree = document["TownTree"];
	for (unsigned int i = 0; i < townTree.Size(); i++)
	{
		std::string tile = townTree[i].GetString();
		myPalletTownTypeSelecter.insert(std::pair<std::string, PalletTownTileType>(tile, PalletTownTileType::TownTree));
	}

	const rapidjson::Value& trainerHouse = document["TrainerHouse"];
	for (unsigned int i = 0; i < trainerHouse.Size(); i++)
	{
		std::string tile = trainerHouse[i].GetString();
		myPalletTownTypeSelecter.insert(std::pair<std::string, PalletTownTileType>(tile, PalletTownTileType::TrainerHouse));
	}

	const rapidjson::Value& playerDoor = document["PlayerDoor"];
	for (unsigned int i = 0; i < playerDoor.Size(); i++)
	{
		std::string tile = playerDoor[i].GetString();
		myPalletTownTypeSelecter.insert(std::pair<std::string, PalletTownTileType>(tile, PalletTownTileType::PlayerDoor));
	}

	const rapidjson::Value& waterA = document["WaterA"];
	for (unsigned int i = 0; i < waterA.Size(); i++)
	{
		std::string tile = waterA[i].GetString();
		myPalletTownTypeSelecter.insert(std::pair<std::string, PalletTownTileType>(tile, PalletTownTileType::WaterA));
	}

	const rapidjson::Value& wildGrass = document["WildGrass"];
	for (unsigned int i = 0; i < wildGrass.Size(); i++)
	{
		std::string tile = wildGrass[i].GetString();
		myPalletTownTypeSelecter.insert(std::pair<std::string, PalletTownTileType>(tile, PalletTownTileType::WildGrass));
	}

	for (int i = 0; i < 2; i++)
	{
		const PalletTownTileType aType = static_cast<PalletTownTileType>(i + 13);
		TileInfo aNullTile = TileInfo(aType);

		if (aNullTile.myType == PalletTownTileType::TownNullWall)
		{
			aNullTile.myIsWalkable = false;
		}
		else
		{
			aNullTile.myIsWalkable = true;
			aNullTile.myIsDoor = true;
		}

		myTileInfoMap.insert(std::pair<PalletTownTileType, TileInfo>(static_cast<PalletTownTileType>(i + 13), aNullTile));
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
	const int anIndex = (NUM_COLUMNS * npcColumnRow.y) + npcColumnRow.x;
	constexpr short TypeMask = 15;
	const TileInfo aTileInfo = myTileInfoMap.find(static_cast<PalletTownTileType>(TypeMask & GetBitMap()[anIndex]))->second;

	return aTileInfo.myIsWalkable;
}

TileInfo TileMapPalletTown::GetTileAtIndex(int anIndex) const
{
	constexpr short TypeMask = 15;
	TileInfo aTileInfo = myTileInfoMap.find(static_cast<PalletTownTileType>(TypeMask & GetBitMap()[anIndex]))->second;

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
