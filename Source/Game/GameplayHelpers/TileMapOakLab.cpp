#include "TileMapOakLab.h"

#include <cassert>

#include "Events/DoorEvent.h"
#include "Events/EventManager.h"
#include "Game/Game.h"
#include "GameplayHelpers/TileMap.h"

TileMapOakLab::TileMapOakLab(GameCore* aGameCore, Area anArea)
	: TileMap(aGameCore, anArea)
{
	for (int i = 0; i < 2; i++)
	{
		const OakLabTileType type = static_cast<OakLabTileType>(i + 9);
		TileInfo nullTile = TileInfo(type);

		if (nullTile.myLabType == OakLabTileType::NullWall)
		{
			nullTile.myIsWalkable = false;
		}
		else
		{
			nullTile.myIsWalkable = true;
			nullTile.myIsDoor = true;
		}

		m_TileInfoMap.insert(std::pair<OakLabTileType, TileInfo>(static_cast<OakLabTileType>(i + 9), nullTile));
	}
}

TileMapOakLab::~TileMapOakLab()
{
	m_TileInfoMap.clear();
}

void TileMapOakLab::AddTile(const std::string& anIndex, const Frame& aFrame)
{
	if (myArea == Area::OakLab)
	{
		//Check to see if the TileInfo does not exists, if so make a new TileInfo
		if (OakLabTileType type = myOakLabTypeSelecter.find(anIndex)->second; m_TileInfoMap.find(type) == m_TileInfoMap.end())
		{
			TileInfo tileInfo = TileInfo(type);

			if (tileInfo.myLabType == OakLabTileType::Floor || tileInfo.myLabType == OakLabTileType::Seat || tileInfo.myLabType == OakLabTileType::Entrance)
			{
				tileInfo.myIsWalkable = true;
			}
			else
			{
				tileInfo.myIsWalkable = false;
			}

			//push the frame attributes into the Variant vector
			tileInfo.myVariant.push_back(aFrame);

			//insert the new TileInfo into the TileInfo Map
			m_TileInfoMap.insert(std::pair<OakLabTileType, TileInfo>(type, tileInfo));
		}
		//if the TileInfo does exist then push back the new frame attributes into its variant vector
		else
		{
			m_TileInfoMap.at(type).myVariant.push_back(aFrame);
		}
	}
}

TileInfo TileMapOakLab::GetTileFromOakLabMap(OakLabTileType aType) const
{
	return m_TileInfoMap.find(aType)->second;
}

bool TileMapOakLab::IsTileAtPlayer(Vector2Int playerColumnRow) const
{
	const int index = (LabColumns * playerColumnRow.y) + playerColumnRow.x;
	constexpr short typeMask = 15;
	const TileInfo tileInfo = m_TileInfoMap.find(static_cast<OakLabTileType>(typeMask & GetBitMap()[index]))->second;

	if (tileInfo.myLabType == OakLabTileType::NullDoor)
	{
		Event* doorevent = new DoorEvent(10);
		myGame->GetEventManager()->QueueEvent(doorevent);
	}

	return tileInfo.myIsWalkable;
}

bool TileMapOakLab::IsTileAtNPC(Vector2Int npcColumnRow) const
{
	const int index = (LabColumns * npcColumnRow.y) + npcColumnRow.x;
	constexpr short typeMask = 15;
	const TileInfo tileInfo = m_TileInfoMap.find(static_cast<OakLabTileType>(typeMask & GetBitMap()[index]))->second;

	return tileInfo.myIsWalkable;
}

TileInfo TileMapOakLab::GetTileAtIndex(int anIndex) const
{
	constexpr short typeMask = 15;
	TileInfo tileInfo = m_TileInfoMap.find(static_cast<OakLabTileType>(typeMask & GetBitMap()[anIndex]))->second;

	return tileInfo;
}

int TileMapOakLab::GetMapWidth() const
{
	return LabColumns;
}

int TileMapOakLab::GetMapHeight() const
{
	return LabRows;
}

int TileMapOakLab::GetIndexFromColumnRow(int aColumn, int aRow) const
{
	assert(aColumn >= 0 && aRow >= 0 && aColumn <= LabColumns && aRow <= LabRows);
	const int indexOnMap = (aRow * LabColumns) + aColumn;

	return indexOnMap;
}

Vector2Int TileMapOakLab::GetColumRowFromIndex(int anIndex) const
{
	return Vector2Int(anIndex % LabColumns, anIndex / LabColumns);
}
