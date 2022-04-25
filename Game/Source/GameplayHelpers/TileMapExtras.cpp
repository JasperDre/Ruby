#include "GamePCH.h"

#include "GameplayHelpers/TileMap.h"
#include "TileMapExtras.h"

#include "Game/Game.h"

TileMapExtras::TileMapExtras(GameCore * myGame, Areas anArea) : TileMap(myGame, anArea)
{

}

TileMapExtras::~TileMapExtras()
{
	m_TileInfoMap.clear();
}

void TileMapExtras::AddTile(const string & anIndex, Frame aFrame)
{
	m_TileInfoMap.insert(std::pair<string, Frame>(anIndex, aFrame));
}

Frame TileMapExtras::GetFrameFromExtrasMap(string aType)
{
	return m_TileInfoMap.find(aType)->second;
}

bool TileMapExtras::GetTileAtPlayer(ivec2 playerColumnRow)
{
	return false;
}

bool TileMapExtras::GetTileAtNPC(ivec2 npcColumnRow)
{
	return false;
}

int TileMapExtras::GetMapWidth()
{
	return 0;
}

int TileMapExtras::GetMapHeight()
{
	return 0;
}

int TileMapExtras::GetIndexFromColumnRow(int aColumn, int aRow)
{
	return 0;
}

ivec2 TileMapExtras::GetColumRowFromIndex(int anIndex)
{
	return ivec2();
}
