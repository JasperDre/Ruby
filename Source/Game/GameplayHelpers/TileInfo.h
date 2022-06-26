#pragma once

#include <vector>

#include "Constants.h"
#include "Frame.h"

struct TileInfo
{
	TileInfo(PalletTownTileType aType)
		: myLabType(OakLabTileType::OakLabBookShelf)
		, myForestType(ForestTileType::ForestFence)
		, myType(aType)
		, myIndex(0)
		, myIsDoor(false)
		, myIsWalkable(true)
	{}

	TileInfo(OakLabTileType aType)
		: myLabType(aType)
		, myForestType(ForestTileType::ForestFence)
		, myType(PalletTownTileType::OakDoor)
		, myIndex(0)
		, myIsDoor(false)
		, myIsWalkable(true)
	{}

	TileInfo(ForestTileType aType)
		: myLabType(OakLabTileType::OakLabBookShelf)
		, myForestType(aType)
		, myType(PalletTownTileType::OakDoor)
		, myIndex(0)
		, myIsDoor(false)
		, myIsWalkable(true)
	{}

	TileInfo()
		: myLabType(OakLabTileType::OakLabBookShelf)
		, myForestType(ForestTileType::ForestFence)
		, myType(PalletTownTileType::OakDoor)
		, myIndex(0)
		, myIsDoor(false)
		, myIsWalkable(true)
	{}

	std::vector<Frame> myVariant;
	OakLabTileType myLabType;
	ForestTileType myForestType;
	PalletTownTileType myType;
	int myIndex;
	bool myIsDoor;
	bool myIsWalkable;
};
