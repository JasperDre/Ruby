#pragma once

#include <vector>

#include "Constants.h"
#include "Frame.h"

struct TileInfo
{
	TileInfo(Tile_Type aType)
		: myLabType(OakLab_Tile_Type::Oak_Lab_BookShelf_)
		, myForestType(Forest_Tile_Type::Forest_Fence_)
		, myType(aType)
		, myIndex(0)
		, myIsDoor(false)
		, myIsWalkable(true)
	{}

	TileInfo(OakLab_Tile_Type aType)
		: myLabType(aType)
		, myForestType(Forest_Tile_Type::Forest_Fence_)
		, myType(Tile_Type::Oak_Door_)
		, myIndex(0)
		, myIsDoor(false)
		, myIsWalkable(true)
	{}

	TileInfo(Forest_Tile_Type aType)
		: myLabType(OakLab_Tile_Type::Oak_Lab_BookShelf_)
		, myForestType(aType)
		, myType(Tile_Type::Oak_Door_)
		, myIndex(0)
		, myIsDoor(false)
		, myIsWalkable(true)
	{}

	TileInfo()
		: myLabType(OakLab_Tile_Type::Oak_Lab_BookShelf_)
		, myForestType(Forest_Tile_Type::Forest_Fence_)
		, myType(Tile_Type::Oak_Door_)
		, myIndex(0)
		, myIsDoor(false)
		, myIsWalkable(true)
	{}

	std::vector<Frame> myVariant;
	OakLab_Tile_Type myLabType;
	Forest_Tile_Type myForestType;
	Tile_Type myType;
	int myIndex;
	bool myIsDoor;
	bool myIsWalkable;
};
