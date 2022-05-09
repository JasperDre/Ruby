#pragma once

#include "TileMap.h"

class GameCore;

class TileMapOakLab : public TileMap
{
public:
	TileMapOakLab(GameCore* myGame, Areas anArea);
	~TileMapOakLab();

	void AddTile(const std::string& anIndex, Frame aFrame) override;

	TileInfo GetTileFromOakLabMap(OakLab_Tile_Type aType) override;

	bool GetTileAtPlayer(ivec2 playerColumnRow) override;

	bool GetTileAtNPC(ivec2 npcColumnRow) override;

	TileInfo GetTileAtIndex(int anIndex) override;

	int GetMapWidth() override;
	int GetMapHeight() override;
	int GetIndexFromColumnRow(int aColumn, int aRow) override;
	ivec2 GetColumRowFromIndex(int anIndex) override;

private:
	std::map<OakLab_Tile_Type, TileInfo> m_TileInfoMap;
};