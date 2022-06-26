#pragma once

#include <map>
#include <string>

#include "Frame.h"
#include "TileInfo.h"
#include "TileMap.h"
#include "Math/Vector2Int.h"

class TileMap;
class GameCore;

class TileMapPalletTown : public TileMap
{
public:
	TileMapPalletTown(GameCore* aGameCore, Area anArea);
	~TileMapPalletTown() override;
	
	void AddTile(const std::string& anIndex, const Frame& aFrame) override;

	[[nodiscard]] TileInfo GetTileFromPalletTownMap(PalletTownTileType aType) const override;
	[[nodiscard]] bool IsTileAtPlayer(Vector2Int playerColumnRow) const override;
	[[nodiscard]] bool IsTileAtNPC(Vector2Int npcColumnRow) const override;
	[[nodiscard]] TileInfo GetTileAtIndex(int anIndex) const override;
	[[nodiscard]] int GetMapWidth() const override;
	[[nodiscard]] int GetMapHeight() const override;
	[[nodiscard]] int GetIndexFromColumnRow(int aColumn, int aRow) const override;
	[[nodiscard]] Vector2Int GetColumRowFromIndex(int anIndex) const override;

private:
	std::map<std::string, PalletTownTileType> myPalletTownTypeSelecter;
	std::map<PalletTownTileType, TileInfo> myTileInfoMap;
};
