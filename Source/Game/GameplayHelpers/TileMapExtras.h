#pragma once

#include "TileMap.h"

#include <map>

class GameCore;

class TileMapExtras : public TileMap
{
public:
	TileMapExtras(GameCore* aGameCore, Area anArea);
	~TileMapExtras() override;

	void LoadTileTypeMap(const std::string& /*aFilepath*/) override {}
	void AddTile(const std::string& anIndex, const Frame& aFrame) override;

	[[nodiscard]] Frame GetFrameFromExtrasMap(const std::string& aType) const override;
	[[nodiscard]] bool IsTileAtPlayer(Vector2Int playerColumnRow) const override;
	[[nodiscard]] bool IsTileAtNPC(Vector2Int npcColumnRow) const override;
	[[nodiscard]] int GetMapWidth() const override;
	[[nodiscard]] int GetMapHeight() const override;
	[[nodiscard]] int GetIndexFromColumnRow(int aColumn, int aRow) const override;
	[[nodiscard]] Vector2Int GetColumRowFromIndex(int anIndex) const override;

private:
	std::map<std::string, Frame> myTileInfoMap;
};