#pragma once

#include <map>

class TileMap;
class GameCore;

class TileMapWoods : public TileMap
{
public:
	TileMapWoods(GameCore* aGameCore, Areas anArea);
	~TileMapWoods() override;

	void AddTile(const std::string& anIndex, Frame aFrame) override;

	[[nodiscard]] TileInfo GetTileFromWoodsMap(Forest_Tile_Type aType) const override;
	[[nodiscard]] bool IsTileAtPlayer(Vector2Int playerColumnRow) const override;
	[[nodiscard]] bool IsTileAtNPC(Vector2Int npcColumnRow) const override;
	[[nodiscard]] TileInfo GetTileAtIndex(int anIndex) const override;
	[[nodiscard]] int GetMapWidth() const override;
	[[nodiscard]] int GetMapHeight() const override;
	[[nodiscard]] int GetIndexFromColumnRow(int aColumn, int aRow) const override;
	[[nodiscard]] Vector2Int GetColumRowFromIndex(int anIndex) const override;

private:
	std::map<Forest_Tile_Type, TileInfo> myTileInfoMap;
};
