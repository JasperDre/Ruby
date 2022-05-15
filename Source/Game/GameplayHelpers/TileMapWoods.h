#pragma once

#include <map>

class TileMap;
class GameCore;

class TileMapWoods : public TileMap
{
public:
	TileMapWoods(GameCore* myGame, Areas anArea);
	~TileMapWoods();

	virtual void AddTile(const std::string& anIndex, Frame aFrame) override;

	virtual TileInfo GetTileFromWoodsMap(Forest_Tile_Type aType) override;

	virtual bool GetTileAtPlayer(Vector2Int playerColumnRow) override;

	virtual bool GetTileAtNPC(Vector2Int npcColumnRow) override;

	virtual TileInfo GetTileAtIndex(int anIndex) override;

	virtual int GetMapWidth() override;
	virtual int GetMapHeight() override;
	virtual int GetIndexFromColumnRow(int aColumn, int aRow) override;
	virtual Vector2Int GetColumRowFromIndex(int anIndex) override;

private:
	std::map<Forest_Tile_Type, TileInfo> m_TileInfoMap;
};
