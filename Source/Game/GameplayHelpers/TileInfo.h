#pragma once

#include <vector>

#include "Constants.h"
#include "Frame.h"

struct TileInfo
{
	TileInfo(PalletTownTileType aType)
		: myLabType(OakLabTileType::OakLabBookShelf)
		, myRoute1Type(Route1TileType::Fence)
		, myType(aType)
		, myIndex(0)
		, myIsDoor(false)
		, myIsWalkable(true)
	{}

	TileInfo(OakLabTileType aType)
		: myLabType(aType)
		, myRoute1Type(Route1TileType::Fence)
		, myType(PalletTownTileType::OakDoor)
		, myIndex(0)
		, myIsDoor(false)
		, myIsWalkable(true)
	{}

	TileInfo(Route1TileType aType)
		: myLabType(OakLabTileType::OakLabBookShelf)
		, myRoute1Type(aType)
		, myType(PalletTownTileType::OakDoor)
		, myIndex(0)
		, myIsDoor(false)
		, myIsWalkable(true)
	{}

	TileInfo()
		: myLabType(OakLabTileType::OakLabBookShelf)
		, myRoute1Type(Route1TileType::Fence)
		, myType(PalletTownTileType::OakDoor)
		, myIndex(0)
		, myIsDoor(false)
		, myIsWalkable(true)
	{}

	std::vector<Frame> myVariant;
	OakLabTileType myLabType;
	Route1TileType myRoute1Type;
	PalletTownTileType myType;
	int myIndex;
	bool myIsDoor;
	bool myIsWalkable;
};
