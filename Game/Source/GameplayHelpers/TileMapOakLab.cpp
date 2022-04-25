#include "GamePCH.h"

#include "GameplayHelpers/TileMap.h"
#include "TileMapOakLab.h"

#include "Game/Game.h"


TileMapOakLab::TileMapOakLab(GameCore* myGame, Areas anArea) : TileMap(myGame, anArea)
{
	for (int i = 0; i < 2; i++)
	{
		OakLab_Tile_Type aType = OakLab_Tile_Type(i + 9);

		TileInfo aNullTile = TileInfo(aType);

		if (aNullTile.MyLabType == Oak_Lab_NullWall_)
		{
			aNullTile.IsWalkable = false;
		}
		else
		{
			aNullTile.IsWalkable = true;
			aNullTile.IsDoor = true;
		}
		m_TileInfoMap.insert(std::pair<OakLab_Tile_Type, TileInfo>(OakLab_Tile_Type(i + 9), aNullTile));
	}
}

TileMapOakLab::~TileMapOakLab()
{

}

void TileMapOakLab::AddTile(const string& anIndex, Frame aFrame)
{
	if (m_MyArea == Area_OakLab)
	{
		//Find the Tile Type from the index string
		OakLab_Tile_Type aType = LabTypeSelecter.find(anIndex)->second;

		//Check to see if the TileInfo does not exists, if so make a new TileInfo
		if (m_TileInfoMap.find(aType) == m_TileInfoMap.end())
		{

			TileInfo myNewTile = TileInfo(aType);

			if (myNewTile.MyLabType == Oak_Lab_Floor_|| myNewTile.MyLabType == Oak_Lab_Seat_ || myNewTile.MyLabType == Oak_Lab_Entrance_)
			{
				myNewTile.IsWalkable = true;
			}
			else
			{
				myNewTile.IsWalkable = false;
			}

			//push the frame attributes into the Variant vector
			myNewTile.MyVariant.push_back(aFrame);

			//insert the new TileInfo into the TileInfo Map
			m_TileInfoMap.insert(std::pair<OakLab_Tile_Type, TileInfo>(aType, myNewTile));
		}
		//if the TileInfo does exist then push back the new frame attributes into its variant vector
		else
		{
			m_TileInfoMap.at(aType).MyVariant.push_back(aFrame);
		}
	}
}

TileInfo TileMapOakLab::GetTileFromOakLabMap(OakLab_Tile_Type aType)
{
	return m_TileInfoMap.find(aType)->second;
}

bool TileMapOakLab::GetTileAtPlayer(ivec2 playerColumnRow)
{
	int anIndex = (NUM_LAB_COLUMNS * playerColumnRow.y) + playerColumnRow.x;

	short TypeMask = 15;

	TileInfo aTileInfo = m_TileInfoMap.find(OakLab_Tile_Type(TypeMask & OakLabBitMap[anIndex]))->second;

	if (aTileInfo.MyLabType == Oak_Lab_NullDoor_)
	{
		Event* doorevent = new DoorEvent(10);
		m_pMyGame->GetEventManager()->QueueEvent(doorevent);
	}

	return aTileInfo.IsWalkable;
}

bool TileMapOakLab::GetTileAtNPC(ivec2 npcColumnRow)
{
	int anIndex = (NUM_LAB_COLUMNS * npcColumnRow.y) + npcColumnRow.x;

	short TypeMask = 15;

	TileInfo aTileInfo = m_TileInfoMap.find(OakLab_Tile_Type(TypeMask & OakLabBitMap[anIndex]))->second;

	return aTileInfo.IsWalkable;
}

TileInfo TileMapOakLab::GetTileAtIndex(int anIndex)
{
	short TypeMask = 15;

	TileInfo aTileInfo = m_TileInfoMap.find(OakLab_Tile_Type(TypeMask & OakLabBitMap[anIndex]))->second;

	return aTileInfo;
}

int TileMapOakLab::GetMapWidth()
{
	return NUM_LAB_COLUMNS;
}

int TileMapOakLab::GetMapHeight()
{
	return NUM_LAB_ROWS;
}

int TileMapOakLab::GetIndexFromColumnRow(int aColumn, int aRow)
{
	assert(aColumn >= 0 && aRow >= 0 && aColumn <= NUM_LAB_COLUMNS && aRow <= NUM_LAB_ROWS);

	int anIndexOnMap = (aRow * NUM_LAB_COLUMNS) + aColumn;
	return anIndexOnMap;
}

ivec2 TileMapOakLab::GetColumRowFromIndex(int anIndex)
{
	return ivec2(anIndex % NUM_LAB_COLUMNS, anIndex / NUM_LAB_COLUMNS);
}

