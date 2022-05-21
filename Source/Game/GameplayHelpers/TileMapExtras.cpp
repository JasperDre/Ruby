#include "TileMapExtras.h"

#include "GameplayHelpers/TileMap.h"

TileMapExtras::TileMapExtras(GameCore* aGameCore, Area anArea)
	: TileMap(aGameCore, anArea)
{}

TileMapExtras::~TileMapExtras()
{
	m_TileInfoMap.clear();
}

void TileMapExtras::AddTile(const std::string& anIndex, const Frame& aFrame)
{
	m_TileInfoMap.insert(std::pair<std::string, Frame>(anIndex, aFrame));
}

Frame TileMapExtras::GetFrameFromExtrasMap(const std::string& aType) const
{
	return m_TileInfoMap.find(aType)->second;
}

bool TileMapExtras::IsTileAtPlayer(Vector2Int playerColumnRow) const
{
	return false;
}

bool TileMapExtras::IsTileAtNPC(Vector2Int npcColumnRow) const
{
	return false;
}

int TileMapExtras::GetMapWidth() const
{
	return 0;
}

int TileMapExtras::GetMapHeight() const
{
	return 0;
}

int TileMapExtras::GetIndexFromColumnRow(int aColumn, int aRow) const
{
	return 0;
}

Vector2Int TileMapExtras::GetColumRowFromIndex(int anIndex) const
{
	return Vector2Int();
}
