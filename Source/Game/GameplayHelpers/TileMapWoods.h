#pragma once

#include <map>
#include <string>

#include "Constants.h"
#include "Frame.h"
#include "TileInfo.h"
#include "TileMap.h"
#include "Math/Vector2Int.h"

class TileMap;
class GameCore;

class TileMapWoods : public TileMap
{
public:
	TileMapWoods(GameCore* aGameCore, Area anArea);
	~TileMapWoods() override;

	void LoadTileTypeMap(const std::string& /*aFilepath*/) override {}
	void AddTile(const std::string& anIndex, const Frame& aFrame) override;

	[[nodiscard]] TileInfo GetTileFromWoodsMap(ForestTileType aType) const override;
	[[nodiscard]] bool IsTileAtPlayer(Vector2Int playerColumnRow) const override;
	[[nodiscard]] bool IsTileAtNPC(Vector2Int npcColumnRow) const override;
	[[nodiscard]] TileInfo GetTileAtIndex(int anIndex) const override;
	[[nodiscard]] int GetMapWidth() const override;
	[[nodiscard]] int GetMapHeight() const override;
	[[nodiscard]] int GetIndexFromColumnRow(int aColumn, int aRow) const override;
	[[nodiscard]] Vector2Int GetColumRowFromIndex(int anIndex) const override;

private:
	std::map<std::string, ForestTileType> myWoodsTypeSelecter = {
		{ "Forest_Fence_1.png", ForestFence }, { "Forest_Grass_1.png", ForestGrass },
		{ "Forest_Grass_2.png", ForestGrass }, { "Forest_Ridge_1.png", ForestRidge },
		{ "Forest_Ridge_2.png", ForestRidge }, { "Forest_Ridge_3.png", ForestRidge },
		{ "Forest_Sign_1.png", ForestSign }, { "Forest_Tree_1.png", ForestTree }, { "Forest_Tree_2.png", ForestTree },
		{ "Forest_Tree_3.png", ForestTree }, { "Forest_Tree_4.png", ForestTree }, { "Forest_Tree_5.png", ForestTree },
		{ "Forest_Tree_6.png", ForestTree }, { "Forest_Tree_7.png", ForestTree }, { "Forest_Tree_8.png", ForestTree },
		{ "Forest_Wild_Grass_1.png", ForestWildGrass }, { "Forest_Wild_Grass_2.png", ForestWildGrass }
	};

	std::map<ForestTileType, TileInfo> myTileInfoMap;
};
