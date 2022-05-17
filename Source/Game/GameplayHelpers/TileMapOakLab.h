#pragma once

#include "TileMap.h"

class GameCore;

class TileMapOakLab : public TileMap
{
public:
	TileMapOakLab(GameCore* aGameCore, Areas anArea);
	~TileMapOakLab() override;

	void AddTile(const std::string& anIndex, const Frame& aFrame) override;

	[[nodiscard]] TileInfo GetTileFromOakLabMap(OakLab_Tile_Type aType) const override;
	[[nodiscard]] bool IsTileAtPlayer(Vector2Int playerColumnRow) const override;
	[[nodiscard]] bool IsTileAtNPC(Vector2Int npcColumnRow) const override;
	[[nodiscard]] TileInfo GetTileAtIndex(int anIndex) const override;
	[[nodiscard]] int GetMapWidth() const override;
	[[nodiscard]] int GetMapHeight() const override;
	[[nodiscard]] int GetIndexFromColumnRow(int aColumn, int aRow) const override;
	[[nodiscard]] Vector2Int GetColumRowFromIndex(int anIndex) const override;

private:
	std::map<OakLab_Tile_Type, TileInfo> m_TileInfoMap;
};