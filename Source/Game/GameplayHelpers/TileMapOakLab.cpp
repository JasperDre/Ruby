#include "GamePCH.h"
#include "TileMapOakLab.h"

#include "Game/Game.h"
#include "GameplayHelpers/TileMap.h"

TileMapOakLab::TileMapOakLab(GameCore* myGame, Areas anArea)
	: TileMap(myGame, anArea)
{
	for (int i = 0; i < 2; i++)
	{
		const OakLab_Tile_Type aType = static_cast<OakLab_Tile_Type>(i + 9);
		TileInfo aNullTile = TileInfo(aType);

		if (aNullTile.myLabType == Oak_Lab_NullWall_)
		{
			aNullTile.myIsWalkable = false;
		}
		else
		{
			aNullTile.myIsWalkable = true;
			aNullTile.myIsDoor = true;
		}

		m_TileInfoMap.insert(std::pair<OakLab_Tile_Type, TileInfo>(static_cast<OakLab_Tile_Type>(i + 9), aNullTile));
	}
}

TileMapOakLab::~TileMapOakLab()
{
	m_TileInfoMap.clear();
}

void TileMapOakLab::AddTile(const std::string& anIndex, Frame aFrame)
{
	if (myArea == Areas::Area_OakLab)
	{
		//Check to see if the TileInfo does not exists, if so make a new TileInfo
		if (OakLab_Tile_Type aType = LabTypeSelecter.find(anIndex)->second; m_TileInfoMap.find(aType) == m_TileInfoMap.end())
		{
			TileInfo myNewTile = TileInfo(aType);

			if (myNewTile.myLabType == Oak_Lab_Floor_ || myNewTile.myLabType == Oak_Lab_Seat_ || myNewTile.myLabType == Oak_Lab_Entrance_)
			{
				myNewTile.myIsWalkable = true;
			}
			else
			{
				myNewTile.myIsWalkable = false;
			}

			//push the frame attributes into the Variant vector
			myNewTile.myVariant.push_back(aFrame);

			//insert the new TileInfo into the TileInfo Map
			m_TileInfoMap.insert(std::pair<OakLab_Tile_Type, TileInfo>(aType, myNewTile));
		}
		//if the TileInfo does exist then push back the new frame attributes into its variant vector
		else
		{
			m_TileInfoMap.at(aType).myVariant.push_back(aFrame);
		}
	}
}

TileInfo TileMapOakLab::GetTileFromOakLabMap(OakLab_Tile_Type aType) const
{
	return m_TileInfoMap.find(aType)->second;
}

bool TileMapOakLab::IsTileAtPlayer(Vector2Int playerColumnRow) const
{
	const int anIndex = (NUM_LAB_COLUMNS * playerColumnRow.y) + playerColumnRow.x;
	constexpr short TypeMask = 15;
	const TileInfo aTileInfo = m_TileInfoMap.find(static_cast<OakLab_Tile_Type>(TypeMask & OakLabBitMap[anIndex]))->second;

	if (aTileInfo.myLabType == Oak_Lab_NullDoor_)
	{
		Event* doorevent = new DoorEvent(10);
		myGame->GetEventManager()->QueueEvent(doorevent);
	}

	return aTileInfo.myIsWalkable;
}

bool TileMapOakLab::IsTileAtNPC(Vector2Int npcColumnRow) const
{
	const int anIndex = (NUM_LAB_COLUMNS * npcColumnRow.y) + npcColumnRow.x;
	constexpr short TypeMask = 15;
	const TileInfo aTileInfo = m_TileInfoMap.find(static_cast<OakLab_Tile_Type>(TypeMask & OakLabBitMap[anIndex]))->second;

	return aTileInfo.myIsWalkable;
}

TileInfo TileMapOakLab::GetTileAtIndex(int anIndex) const
{
	constexpr short TypeMask = 15;
	TileInfo aTileInfo = m_TileInfoMap.find(static_cast<OakLab_Tile_Type>(TypeMask & OakLabBitMap[anIndex]))->second;

	return aTileInfo;
}

int TileMapOakLab::GetMapWidth() const
{
	return NUM_LAB_COLUMNS;
}

int TileMapOakLab::GetMapHeight() const
{
	return NUM_LAB_ROWS;
}

int TileMapOakLab::GetIndexFromColumnRow(int aColumn, int aRow) const
{
	assert(aColumn >= 0 && aRow >= 0 && aColumn <= NUM_LAB_COLUMNS && aRow <= NUM_LAB_ROWS);
	const int anIndexOnMap = (aRow * NUM_LAB_COLUMNS) + aColumn;

	return anIndexOnMap;
}

Vector2Int TileMapOakLab::GetColumRowFromIndex(int anIndex) const
{
	return Vector2Int(anIndex % NUM_LAB_COLUMNS, anIndex / NUM_LAB_COLUMNS);
}

