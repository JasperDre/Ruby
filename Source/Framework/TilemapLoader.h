#pragma once

#include <filesystem>

#include "Math/Rectangle.h"
#include "Math/Vector2Float.h"

class TilemapLoader
{
public:
	struct Tile
	{
		Tile() : myIdentifier(0), myIsCollidable(false) {}

		Rectangle myRectangle;
		Vector2Float myPosition;
		std::filesystem::path myTilesetPath;
		unsigned int myIdentifier;
		bool myIsCollidable;
	};

	static std::vector<Tile> Load(const std::filesystem::path& aTilemapPath);
};
