#pragma once

#include "TileMap.h"

class GameCore;

class TileMapExtras : public TileMap
{
public:
	TileMapExtras(GameCore* myGame, Areas anArea);
	~TileMapExtras() override;

	void AddTile(const std::string& anIndex, Frame aFrame) override;

	[[nodiscard]] Frame GetFrameFromExtrasMap(const std::string& aType) const override;
	[[nodiscard]] bool GetTileAtPlayer(Vector2Int playerColumnRow) const override;
	[[nodiscard]] bool GetTileAtNPC(Vector2Int npcColumnRow) const override;
	[[nodiscard]] int GetMapWidth() const override;
	[[nodiscard]] int GetMapHeight() const override;
	[[nodiscard]] int GetIndexFromColumnRow(int aColumn, int aRow) const override;
	[[nodiscard]] Vector2Int GetColumRowFromIndex(int anIndex) const override;

private:
	std::map<std::string, Frame> m_TileInfoMap;
};