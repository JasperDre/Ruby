#pragma once
class TileMap;
class GameCore;

using namespace std;

class TileMapOakLab : public TileMap
{
public:
	TileMapOakLab(GameCore* myGame, Areas anArea);
	~TileMapOakLab();

	virtual void AddTile(const string& anIndex, Frame aFrame) override;

	virtual TileInfo GetTileFromOakLabMap(OakLab_Tile_Type aType) override;

	virtual bool GetTileAtPlayer(ivec2 playerColumnRow) override;

	virtual bool GetTileAtNPC(ivec2 npcColumnRow) override;

	virtual TileInfo GetTileAtIndex(int anIndex) override;

	virtual int GetMapWidth() override;
	virtual int GetMapHeight() override;
	virtual int GetIndexFromColumnRow(int aColumn, int aRow)override;
	virtual ivec2 GetColumRowFromIndex(int anIndex) override;

private:
	map<OakLab_Tile_Type, TileInfo> m_TileInfoMap;

};