#pragma once

#include <map>

class TileMap;
class GameCore;

class TileMapPalletTown : public TileMap
{
public:
	TileMapPalletTown(GameCore* myGame, Areas anArea);
	~TileMapPalletTown();
	
	virtual void AddTile(const std::string& anIndex, Frame aFrame) override;

	virtual TileInfo GetTileFromPalletMap(Tile_Type aType) override;

	virtual bool GetTileAtPlayer(ivec2 playerColumnRow) override;

	virtual bool GetTileAtNPC(ivec2 npcColumnRow) override;

	virtual TileInfo GetTileAtIndex(int anIndex) override;

	virtual int GetMapWidth() override;
	virtual int GetMapHeight() override;
	virtual int GetIndexFromColumnRow(int aColumn, int aRow) override;
	virtual ivec2 GetColumRowFromIndex(int anIndex) override;

private:
	std::map<Tile_Type, TileInfo> m_TileInfoMap;
};
