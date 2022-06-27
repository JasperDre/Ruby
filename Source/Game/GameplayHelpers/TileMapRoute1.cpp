#include "TileMapRoute1.h"

#include <cassert>
#include <rapidjson/document.h>

#include "Events/DoorEvent.h"
#include "Events/EventManager.h"
#include "Game/Game.h"
#include "GameplayHelpers/TileMap.h"
#include "Utility/DebugUtility.h"
#include "Utility/FileUtility.h"

TileMapRoute1::TileMapRoute1(GameCore* aGameCore, Area anArea)
	: TileMap(aGameCore, anArea)
{
	for (int i = 0; i < 2; i++)
	{
		const Route1TileType type = static_cast<Route1TileType>(i + 6);
		TileInfo nullTile = TileInfo(type);

		if (nullTile.myRoute1Type == Route1TileType::NullWall)
		{
			nullTile.myIsWalkable = false;
		}
		else
		{
			nullTile.myIsWalkable = true;
			nullTile.myIsDoor = true;
		}

		myTileInfoMap.insert(std::pair<Route1TileType, TileInfo>(static_cast<Route1TileType>(i + 6), nullTile));
	}
}

TileMapRoute1::~TileMapRoute1()
{
	myTileInfoMap.clear();
}

void TileMapRoute1::LoadTileTypeMap(const std::string& aFilepath)
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

	auto loadType = [&document](const char* aValueName, Route1TileType aType, std::map<std::string, Route1TileType>& aSelector)
	{
		const rapidjson::Value& oakHouse = document[aValueName];
		for (unsigned int i = 0; i < oakHouse.Size(); i++)
		{
			std::string tile = oakHouse[i].GetString();
			aSelector.insert(std::pair<std::string, Route1TileType>(tile, aType));
		}
	};

	loadType("ForestFence", Route1TileType::Fence, myWoodsTypeSelecter);
	loadType("ForestGrass", Route1TileType::Grass, myWoodsTypeSelecter);
	loadType("ForestRidge", Route1TileType::Ridge, myWoodsTypeSelecter);
	loadType("ForestSign", Route1TileType::Sign, myWoodsTypeSelecter);
	loadType("ForestTree", Route1TileType::Tree, myWoodsTypeSelecter);
	loadType("ForestWildGrass", Route1TileType::WildGrass, myWoodsTypeSelecter);
}

void TileMapRoute1::AddTile(const std::string& anIndex, const Frame& aFrame)
{
	if (myArea == Area::Woods)
	{
		//Find the Tile Type from the index string
		Route1TileType type = myWoodsTypeSelecter.find(anIndex)->second;

		if (myTileInfoMap.find(type) == myTileInfoMap.end())
		{
			TileInfo tileInfo = TileInfo(type);

			if (tileInfo.myRoute1Type == Route1TileType::Grass || tileInfo.myRoute1Type == Route1TileType::WildGrass)
			{
				tileInfo.myIsWalkable = true;
			}
			else if (tileInfo.myRoute1Type == Route1TileType::NullDoor) //if the tile is a door
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
			myTileInfoMap.insert(std::pair<Route1TileType, TileInfo>(type, tileInfo));
		}
		//if the TileInfo does exist then push back the new frame attributes into its variant vector
		else
		{
			myTileInfoMap.at(type).myVariant.push_back(aFrame);
		}
	}
}

TileInfo TileMapRoute1::GetTileFromWoodsMap(Route1TileType aType) const
{
	return myTileInfoMap.find(aType)->second;
}

bool TileMapRoute1::IsTileAtPlayer(Vector2Int playerColumnRow) const
{
	const int index = (Route1Columns * playerColumnRow.y) + playerColumnRow.x;
	constexpr short typeMask = 15;
	const TileInfo tileInfo = myTileInfoMap.find(static_cast<Route1TileType>(typeMask & GetBitMap()[index]))->second;

	if (tileInfo.myRoute1Type == Route1TileType::NullDoor)
	{
		Event* doorEvent = new DoorEvent(13);
		myGame->GetEventManager()->QueueEvent(doorEvent);
	}

	return tileInfo.myIsWalkable;
}

bool TileMapRoute1::IsTileAtNPC(Vector2Int npcColumnRow) const
{
	const int index = (Columns * npcColumnRow.y) + npcColumnRow.x;
	constexpr short typeMask = 15;
	const TileInfo tileInfo = myTileInfoMap.find(static_cast<Route1TileType>(typeMask & GetBitMap()[index]))->second;

	return tileInfo.myIsWalkable;
}

TileInfo TileMapRoute1::GetTileAtIndex(int anIndex) const
{
	constexpr short typeMask = 15;
	TileInfo tileInfo = myTileInfoMap.find(static_cast<Route1TileType>(typeMask & GetBitMap()[anIndex]))->second;

	return tileInfo;
}

int TileMapRoute1::GetMapWidth() const
{
	return Route1Columns;
}

int TileMapRoute1::GetMapHeight() const
{
	return Route1Rows;
}

int TileMapRoute1::GetIndexFromColumnRow(int aColumn, int aRow) const
{
	assert(aColumn >= 0 && aRow >= 0 && aColumn <= Route1Columns && aRow <= Route1Rows);
	const int indexOnMap = (aRow * Route1Columns) + aColumn;

	return indexOnMap;
}

Vector2Int TileMapRoute1::GetColumRowFromIndex(int anIndex) const
{
	return Vector2Int(anIndex % Route1Columns, anIndex / Route1Columns);
}
