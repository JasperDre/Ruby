#pragma once

#include "TileMap.h"

class GameCore;

class TileMapExtras : public TileMap
{
public:
	TileMapExtras(GameCore* myGame, Areas anArea);
	~TileMapExtras();

	void AddTile(const std::string& anIndex, Frame aFrame) override;

	Frame GetFrameFromExtrasMap(std::string aType) override;

	bool GetTileAtPlayer(Vector2Int playerColumnRow) override;
	bool GetTileAtNPC(Vector2Int npcColumnRow) override;
	int GetMapWidth() override;
	int GetMapHeight() override;
	int GetIndexFromColumnRow(int aColumn, int aRow) override;
	Vector2Int GetColumRowFromIndex(int anIndex) override;

private:
	std::map<std::string, Frame> m_TileInfoMap;
};