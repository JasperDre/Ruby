#include "GamePCH.h"

#include "GameplayHelpers/TileMap.h"
#include "TileMapWoods.h"

#include "Game/Game.h"

TileMapWoods::TileMapWoods(GameCore * myGame, Areas anArea) : TileMap(myGame, anArea)
{
	for (int i = 0; i < 2; i++)
	{
		Forest_Tile_Type aType = Forest_Tile_Type(i + 6);

		TileInfo aNullTile = TileInfo(aType);

		if (aNullTile.MyForestType == Forest_Null_Wall)
		{
			aNullTile.IsWalkable = false;
		}
		else
		{
			aNullTile.IsWalkable = true;
			aNullTile.IsDoor = true;
		}
		m_TileInfoMap.insert(std::pair<Forest_Tile_Type, TileInfo>(Forest_Tile_Type(i + 6), aNullTile));
	}
}

TileMapWoods::~TileMapWoods()
{
	m_TileInfoMap.clear();
}

void TileMapWoods::AddTile(const string & anIndex, Frame aFrame)
{
	if (m_MyArea == Area_Woods)
	{
		//Find the Tile Type from the index string
		Forest_Tile_Type aType = WoodsTypeSelecter.find(anIndex)->second;

		//Check to see if the TileInfo does not exists, if so make a new TileInfo
		if (m_TileInfoMap.find(aType) == m_TileInfoMap.end())
		{

			TileInfo myNewTile = TileInfo(aType);

			if (myNewTile.MyForestType == Forest_Grass_ || myNewTile.MyForestType == Forest_Wild_Grass_)
			{
				myNewTile.IsWalkable = true;
			}
			else if (myNewTile.MyForestType == Forest_Null_Door)		//if the tile is a door
			{
				myNewTile.IsWalkable = true;
				myNewTile.IsDoor = true;
			}
			else
			{
				myNewTile.IsWalkable = false;
			}

			//push the frame attributes into the Variant vector
			myNewTile.MyVariant.push_back(aFrame);

			//insert the new TileInfo into the TileInfo Map
			m_TileInfoMap.insert(std::pair<Forest_Tile_Type, TileInfo>(aType, myNewTile));
		}
		//if the TileInfo does exist then push back the new frame attributes into its variant vector
		else
		{
			m_TileInfoMap.at(aType).MyVariant.push_back(aFrame);
		}
	}
}

TileInfo TileMapWoods::GetTileFromWoodsMap(Forest_Tile_Type aType)
{
	return m_TileInfoMap.find(aType)->second;
}

bool TileMapWoods::GetTileAtPlayer(ivec2 playerColumnRow)
{
	int anIndex = (NUM_FOREST_COLUMNS * playerColumnRow.y) + playerColumnRow.x;

	short TypeMask = 15;

	TileInfo aTileInfo = m_TileInfoMap.find(Forest_Tile_Type(TypeMask & ForestBitMap[anIndex]))->second;

	if (aTileInfo.MyForestType == Forest_Null_Door)
	{
		Event* doorEvent = new DoorEvent(13);
		m_pMyGame->GetEventManager()->QueueEvent(doorEvent);
	}

	return aTileInfo.IsWalkable;

}

bool TileMapWoods::GetTileAtNPC(ivec2 npcColumnRow)
{
	int anIndex = (NUM_COLUMNS * npcColumnRow.y) + npcColumnRow.x;

	short TypeMask = 15;

	TileInfo aTileInfo = m_TileInfoMap.find(Forest_Tile_Type(TypeMask & ForestBitMap[anIndex]))->second;

	return aTileInfo.IsWalkable;
}

TileInfo TileMapWoods::GetTileAtIndex(int anIndex)
{
	short TypeMask = 15;

	TileInfo aTileInfo = m_TileInfoMap.find(Forest_Tile_Type(TypeMask & ForestBitMap[anIndex]))->second;

	return aTileInfo;
}

int TileMapWoods::GetMapWidth()
{
	return NUM_FOREST_COLUMNS;
}

int TileMapWoods::GetMapHeight()
{
	return NUM_FOREST_ROWS;
}

int TileMapWoods::GetIndexFromColumnRow(int aColumn, int aRow)
{
	assert(aColumn >= 0 && aRow >= 0 && aColumn <= NUM_FOREST_COLUMNS && aRow <= NUM_FOREST_ROWS);

	int anIndexOnMap = (aRow * NUM_FOREST_COLUMNS) + aColumn;
	return anIndexOnMap;
}

ivec2 TileMapWoods::GetColumRowFromIndex(int anIndex)
{
	return ivec2(anIndex % NUM_FOREST_COLUMNS, anIndex / NUM_FOREST_COLUMNS);
}

