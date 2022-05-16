#pragma once

#include <vector>

#include "Constants.h"
#include "Frame.h"

struct TileInfo
{
	TileInfo(Tile_Type aType)
		: MyLabType(OakLab_Tile_Type::Oak_Lab_BookShelf_)
		, MyForestType(Forest_Tile_Type::Forest_Fence_)
		, MyType(aType)
		, MyIndex(0)
		, IsDoor(false)
		, IsWalkable(true)
	{}

	TileInfo(OakLab_Tile_Type aType)
		: MyLabType(aType)
		, MyForestType(Forest_Tile_Type::Forest_Fence_)
		, MyType(Tile_Type::Oak_Door_)
		, MyIndex(0)
		, IsDoor(false)
		, IsWalkable(true)
	{}

	TileInfo(Forest_Tile_Type aType)
		: MyLabType(OakLab_Tile_Type::Oak_Lab_BookShelf_)
		, MyForestType(aType)
		, MyType(Tile_Type::Oak_Door_)
		, MyIndex(0)
		, IsDoor(false)
		, IsWalkable(true)
	{}

	TileInfo()
		: MyLabType(OakLab_Tile_Type::Oak_Lab_BookShelf_)
		, MyForestType(Forest_Tile_Type::Forest_Fence_)
		, MyType(Tile_Type::Oak_Door_)
		, MyIndex(0)
		, IsDoor(false)
		, IsWalkable(true)
	{}

	std::vector<Frame> MyVariant;
	OakLab_Tile_Type MyLabType;
	Forest_Tile_Type MyForestType;
	Tile_Type MyType;
	int MyIndex;
	bool IsDoor;
	bool IsWalkable;
};
