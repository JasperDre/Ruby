#include "GamePCH.h"
#include "TileMapExtras.h"

#include "GameplayHelpers/TileMap.h"

TileMapExtras::TileMapExtras(GameCore * myGame, Areas anArea) : TileMap(myGame, anArea)
{

}

TileMapExtras::~TileMapExtras()
{
	m_TileInfoMap.clear();
}

void TileMapExtras::AddTile(const std::string & anIndex, Frame aFrame)
{
	m_TileInfoMap.insert(std::pair<std::string, Frame>(anIndex, aFrame));
}

Frame TileMapExtras::GetFrameFromExtrasMap(std::string aType)
{
	return m_TileInfoMap.find(aType)->second;
}

bool TileMapExtras::GetTileAtPlayer(Vector2Int playerColumnRow)
{
	return false;
}

bool TileMapExtras::GetTileAtNPC(Vector2Int npcColumnRow)
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

Vector2Int TileMapExtras::GetColumRowFromIndex(int anIndex)
{
	return Vector2Int();
}
