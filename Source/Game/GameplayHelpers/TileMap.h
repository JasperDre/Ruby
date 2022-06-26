#pragma once

#include <string>

#include "Constants.h"
#include "Frame.h"
#include "TileInfo.h"
#include "Math/Vector2Int.h"

class GameCore;

class TileMap
{
public:
	TileMap(GameCore* aGameCore, Area aArea);
	virtual ~TileMap() = default;

	virtual void AddTile(const std::string& anIndex, const Frame& aFrame) = 0;

	[[nodiscard]] virtual bool IsTileAtPlayer(Vector2Int playerColumnRow) const = 0;
	[[nodiscard]] virtual bool IsTileAtNPC(Vector2Int npcColumnRow) const = 0;
	[[nodiscard]] virtual TileInfo GetTileFromPalletTownMap(PalletTownTileType aType) const;
	[[nodiscard]] virtual TileInfo GetTileFromOakLabMap(OakLabTileType aType) const;
	[[nodiscard]] virtual TileInfo GetTileFromWoodsMap(ForestTileType aType) const;
	[[nodiscard]] virtual TileInfo GetTileAtIndex(int anIndex) const { return myNullTileInfo; }
	[[nodiscard]] virtual Frame GetFrameFromExtrasMap(const std::string& anIndex) const { return myNullFrame; }
	[[nodiscard]] virtual int GetMapWidth() const = 0;
	[[nodiscard]] virtual int GetMapHeight() const = 0;
	[[nodiscard]] virtual int GetIndexFromColumnRow(int aColumn, int aRow) const = 0;
	[[nodiscard]] virtual Vector2Int GetColumRowFromIndex(int anIndex) const = 0;

	void SetBitMap(const std::vector<unsigned int>& aBitMap) { myBitMap = aBitMap; }

	[[nodiscard]] const std::vector<unsigned int>& GetBitMap() const { return myBitMap; }

protected:
	Area myArea;
	Frame myNullFrame;
	GameCore* myGame;

private:
	std::vector<unsigned int> myBitMap;
	TileInfo myNullTileInfo;
};
