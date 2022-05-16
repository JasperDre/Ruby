#include "GamePCH.h"

#include "GameplayHelpers/TileMap.h"
#include "TileMapPalletTown.h"

#include "Game/Game.h"

TileMapPalletTown::TileMapPalletTown(GameCore* myGame, Areas anArea) : TileMap(myGame, anArea)
{
	for (int i = 0; i < 2; i++)
	{
		const Tile_Type aType = static_cast<Tile_Type>(i + 13);
		TileInfo aNullTile = TileInfo(aType);

		if (aNullTile.MyType == Town_Null_Wall_)
		{
			aNullTile.IsWalkable = false;
		}
		else
		{
			aNullTile.IsWalkable = true;
			aNullTile.IsDoor = true;
		}

		m_TileInfoMap.insert(std::pair<Tile_Type, TileInfo>(static_cast<Tile_Type>(i + 13), aNullTile));
	}
}

TileMapPalletTown::~TileMapPalletTown()
{
	m_TileInfoMap.clear();
}
void TileMapPalletTown::AddTile(const std::string& anIndex, Frame aFrame)
{
	if (m_MyArea == Areas::Area_PalletTown)
	{
		//Find the Tile Type from the index string
		Tile_Type aType = TypeSelecter.find(anIndex)->second;

		//Check to see if the TileInfo does not exists, if so make a new TileInfo
		if (m_TileInfoMap.find(aType) == m_TileInfoMap.end())
		{

			TileInfo myNewTile = TileInfo(aType);

			if (myNewTile.MyType == Town_Flower_ || myNewTile.MyType == Town_Grass_A_ || myNewTile.MyType == Town_Grass_B_ || myNewTile.MyType == Wild_Grass_)
			{
				myNewTile.IsWalkable = true;
			}
			else if (myNewTile.MyType == Oak_Door_ || myNewTile.MyType == Player_Door_) //if the tile is a door
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
			m_TileInfoMap.insert(std::pair<Tile_Type, TileInfo>(aType, myNewTile));
		}
		//if the TileInfo does exist then push back the new frame attributes into its variant vector
		else
		{
			m_TileInfoMap.at(aType).MyVariant.push_back(aFrame);
		}
	}
}

TileInfo TileMapPalletTown::GetTileFromPalletMap(Tile_Type aType) const
{
	return m_TileInfoMap.find(aType)->second;
}

bool TileMapPalletTown::GetTileAtPlayer(Vector2Int playerColumnRow) const
{
	const int anIndex = (NUM_COLUMNS * playerColumnRow.y) + playerColumnRow.x;
	constexpr short TypeMask = 15;
	const TileInfo aTileInfo = m_TileInfoMap.find(static_cast<Tile_Type>(TypeMask & PalletTownBitMap[anIndex]))->second;

	if (aTileInfo.MyType == Oak_Door_)
	{
		Event* doorEvent = new DoorEvent(11);
		m_pMyGame->GetEventManager()->QueueEvent(doorEvent);
	}
	else if (aTileInfo.MyType == Town_Null_Door_)
	{
		Event* doorEvent = new DoorEvent(12);
		m_pMyGame->GetEventManager()->QueueEvent(doorEvent);
	}

	return aTileInfo.IsWalkable;

}

bool TileMapPalletTown::GetTileAtNPC(Vector2Int npcColumnRow) const
{
	const int anIndex = (NUM_COLUMNS * npcColumnRow.y) + npcColumnRow.x;
	constexpr short TypeMask = 15;
	const TileInfo aTileInfo = m_TileInfoMap.find(static_cast<Tile_Type>(TypeMask & PalletTownBitMap[anIndex]))->second;

	return aTileInfo.IsWalkable;
}

TileInfo TileMapPalletTown::GetTileAtIndex(int anIndex) const
{
	constexpr short TypeMask = 15;
	TileInfo aTileInfo = m_TileInfoMap.find(static_cast<Tile_Type>(TypeMask & PalletTownBitMap[anIndex]))->second;

	return aTileInfo;
}

int TileMapPalletTown::GetMapWidth() const
{
	return NUM_COLUMNS;
}

int TileMapPalletTown::GetMapHeight() const
{
	return NUM_ROWS;
}

int TileMapPalletTown::GetIndexFromColumnRow(int aColumn, int aRow) const
{
	assert(aColumn >= 0 && aRow >= 0 && aColumn <= NUM_COLUMNS && aRow <= NUM_COLUMNS);
	const int anIndexOnMap = (aRow * NUM_COLUMNS) + aColumn;

	return anIndexOnMap;
}

Vector2Int TileMapPalletTown::GetColumRowFromIndex(int anIndex) const
{
	return Vector2Int(anIndex % NUM_COLUMNS, anIndex / NUM_COLUMNS);
}
