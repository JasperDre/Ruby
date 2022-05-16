#pragma once

#include <map>

class TileMap;
class GameCore;

class TileMapPalletTown : public TileMap
{
public:
	TileMapPalletTown(GameCore* myGame, Areas anArea);
	~TileMapPalletTown() override;
	
	void AddTile(const std::string& anIndex, Frame aFrame) override;

	[[nodiscard]] TileInfo GetTileFromPalletMap(Tile_Type aType) const override;
	[[nodiscard]] bool IsTileAtPlayer(Vector2Int playerColumnRow) const override;
	[[nodiscard]] bool IsTileAtNPC(Vector2Int npcColumnRow) const override;
	[[nodiscard]] TileInfo GetTileAtIndex(int anIndex) const override;
	[[nodiscard]] int GetMapWidth() const override;
	[[nodiscard]] int GetMapHeight() const override;
	[[nodiscard]] int GetIndexFromColumnRow(int aColumn, int aRow) const override;
	[[nodiscard]] Vector2Int GetColumRowFromIndex(int anIndex) const override;

private:
	std::map<Tile_Type, TileInfo> myTileInfoMap;
};
