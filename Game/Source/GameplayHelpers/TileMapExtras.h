#pragma once
class TileMap;
class GameCore;
using namespace std;

class TileMapExtras : public TileMap
{
public:
	TileMapExtras(GameCore* myGame, Areas anArea);
	~TileMapExtras();

	virtual void AddTile(const string& anIndex, Frame aFrame) override;

	virtual Frame GetFrameFromExtrasMap(string aType) override;

	// Inherited via TileMap
	virtual bool GetTileAtPlayer(ivec2 playerColumnRow) override;
	virtual bool GetTileAtNPC(ivec2 npcColumnRow) override;
	virtual int GetMapWidth() override;
	virtual int GetMapHeight() override;
	virtual int GetIndexFromColumnRow(int aColumn, int aRow) override;
	virtual ivec2 GetColumRowFromIndex(int anIndex) override;

private:

	map<string, Frame> m_TileInfoMap;

};