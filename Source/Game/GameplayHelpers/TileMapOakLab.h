#pragma once

#include "TileMap.h"

#include <map>

class GameCore;

class TileMapOakLab : public TileMap
{
public:
	TileMapOakLab(GameCore* aGameCore, Area anArea);
	~TileMapOakLab() override;

	void AddTile(const std::string& anIndex, const Frame& aFrame) override;

	[[nodiscard]] TileInfo GetTileFromOakLabMap(OakLabTileType aType) const override;
	[[nodiscard]] bool IsTileAtPlayer(Vector2Int playerColumnRow) const override;
	[[nodiscard]] bool IsTileAtNPC(Vector2Int npcColumnRow) const override;
	[[nodiscard]] TileInfo GetTileAtIndex(int anIndex) const override;
	[[nodiscard]] int GetMapWidth() const override;
	[[nodiscard]] int GetMapHeight() const override;
	[[nodiscard]] int GetIndexFromColumnRow(int aColumn, int aRow) const override;
	[[nodiscard]] Vector2Int GetColumRowFromIndex(int anIndex) const override;

private:
	std::map<std::string, OakLabTileType> myOakLabTypeSelecter = {
		{ "Oak_Lab_BookShelf_1.png", OakLabBookShelf }, { "Oak_Lab_BookShelf_2.png", OakLabBookShelf },
		{ "Oak_Lab_BookShelf_3.png", OakLabBookShelf }, { "Oak_Lab_BookShelf_4.png", OakLabBookShelf },
		{ "Oak_Lab_BookShelf_5.png", OakLabBookShelf }, { "Oak_Lab_BookShelf_6.png", OakLabBookShelf },
		{ "Oak_Lab_BookShelf_7.png", OakLabBookShelf }, { "Oak_Lab_BookShelf_8.png", OakLabBookShelf },
		{ "Oak_Lab_BookShelf_9.png", OakLabBookShelf }, { "Oak_Lab_BookShelf_10.png", OakLabBookShelf },
		{ "Oak_Lab_BookShelf_11.png", OakLabBookShelf }, { "Oak_Lab_BookShelf_12.png", OakLabBookShelf },
		{ "Oak_Lab_BookShelf_13.png", OakLabBookShelf }, { "Oak_Lab_BookShelf_14.png", OakLabBookShelf },
		{ "Oak_Lab_BookShelf_15.png", OakLabBookShelf }, { "Oak_Lab_BookShelf_16.png", OakLabBookShelf },
		{ "Oak_Lab_BookShelf_17.png", OakLabBookShelf }, { "Oak_Lab_BookShelf_18.png", OakLabBookShelf },
		{ "Oak_Lab_BookShelf_19.png", OakLabBookShelf }, { "Oak_Lab_BookShelf_20.png", OakLabBookShelf },
		{ "Oak_Lab_BookShelf_21.png", OakLabBookShelf }, { "Oak_Lab_BookShelf_22.png", OakLabBookShelf },
		{ "Oak_Lab_BookShelf_23.png", OakLabBookShelf }, { "Oak_Lab_BookShelf_24.png", OakLabBookShelf },
		{ "Oak_Lab_BookShelf_25.png", OakLabBookShelf }, { "Oak_Lab_BookShelf_26.png", OakLabBookShelf },
		{ "Oak_Lab_BookShelf_27.png", OakLabBookShelf }, { "Oak_Lab_BookShelf_28.png", OakLabBookShelf },
		{ "Oak_Lab_Entrance_1.png", OakLabEntrance }, { "Oak_Lab_Entrance_2.png", OakLabEntrance },
		{ "Oak_Lab_Entrance_3.png", OakLabEntrance }, { "Oak_Lab_Entrance_4.png", OakLabEntrance },
		{ "Oak_Lab_Floor_1.png", OakLabFloor }, { "Oak_Lab_Floor_2.png", OakLabFloor },
		{ "Oak_Lab_Floor_3.png", OakLabFloor }, { "Oak_Lab_Floor_4.png", OakLabFloor },
		{ "Oak_Lab_Floor_5.png", OakLabFloor }, { "Oak_Lab_Floor_6.png", OakLabFloor },
		{ "Oak_Lab_Floor_7.png", OakLabFloor }, { "Oak_Lab_Floor_8.png", OakLabFloor },
		{ "Oak_Lab_Floor_9.png", OakLabFloor }, { "Oak_Lab_Floor_10.png", OakLabFloor },
		{ "Oak_Lab_Floor_11.png", OakLabFloor }, { "Oak_Lab_Floor_12.png", OakLabFloor },
		{ "Oak_Lab_Floor_9.png", OakLabFloor }, { "Oak_Lab_Floor_10.png", OakLabFloor },
		{ "Oak_Lab_Floor_1.png", OakLabFloor }, { "Oak_Lab_Floor_1.png", OakLabFloor },
		{ "Oak_Lab_Floor_13.png", OakLabFloor }, { "Oak_Lab_Floor_14.png", OakLabFloor },
		{ "Oak_Lab_Floor_15.png", OakLabFloor }, { "Oak_Lab_Floor_16.png", OakLabFloor },
		{ "Oak_Lab_Floor_17.png", OakLabFloor }, { "Oak_Lab_Floor_18.png", OakLabFloor },
		{ "Oak_Lab_Floor_19.png", OakLabFloor }, { "Oak_Lab_Floor_20.png", OakLabFloor },
		{ "Oak_Lab_Floor_21.png", OakLabFloor }, { "Oak_Lab_Floor_22.png", OakLabFloor },
		{ "Oak_Lab_Machine_1.png", OakLabMachine }, { "Oak_Lab_Machine_2.png", OakLabMachine },
		{ "Oak_Lab_Machine_3.png", OakLabMachine }, { "Oak_Lab_Machine_4.png", OakLabMachine },
		{ "Oak_Lab_Machine_5.png", OakLabMachine }, { "Oak_Lab_Machine_6.png", OakLabMachine },
		{ "Oak_Lab_Plant_1.png", OakLabPlant }, { "Oak_Lab_Plant_2.png", OakLabPlant },
		{ "Oak_Lab_Plant_3.png", OakLabPlant }, { "Oak_Lab_Plant_4.png", OakLabPlant },
		{ "Oak_Lab_Seat_1.png", OakLabSeat }, { "Oak_Lab_Table_1.png", OakLabTable },
		{ "Oak_Lab_Table_2.png", OakLabTable }, { "Oak_Lab_Table_3.png", OakLabTable },
		{ "Oak_Lab_Table_4.png", OakLabTable }, { "Oak_Lab_Table_5.png", OakLabTable },
		{ "Oak_Lab_Table_6.png", OakLabTable }, { "Oak_Lab_Wall_1.png", OakLabWall },
		{ "Oak_Lab_Wall_2.png", OakLabWall }, { "Oak_Lab_Wall_3.png", OakLabWall },
		{ "Oak_Lab_Wall_4.png", OakLabWall }, { "Oak_Lab_Wall_5.png", OakLabWall },
		{ "Oak_Lab_Wall_6.png", OakLabWall }, { "Oak_Lab_Wall_7.png", OakLabWall },
		{ "Oak_Lab_Wall_8.png", OakLabWall }, { "Oak_Lab_Wall_9.png", OakLabWall },
		{ "Oak_Lab_Wall_10.png", OakLabWall }, { "Oak_Lab_WorkDesk_1.png", OakLabWorkDesk },
		{ "Oak_Lab_WorkDesk_2.png", OakLabWorkDesk }, { "Oak_Lab_WorkDesk_3.png", OakLabWorkDesk },
		{ "Oak_Lab_WorkDesk_4.png", OakLabWorkDesk }, { "Oak_Lab_WorkDesk_5.png", OakLabWorkDesk },
		{ "Oak_Lab_WorkDesk_6.png", OakLabWorkDesk }, { "Oak_Lab_WorkDesk_7.png", OakLabWorkDesk },
		{ "Oak_Lab_WorkDesk_8.png", OakLabWorkDesk }, { "Oak_Lab_WorkDesk_9.png", OakLabWorkDesk },
		{ "Oak_Lab_WorkDesk_10.png", OakLabWorkDesk }, { "Oak_Lab_WorkDesk_11.png", OakLabWorkDesk },
		{ "Oak_Lab_WorkDesk_12.png", OakLabWorkDesk }
	};

	std::map<OakLabTileType, TileInfo> m_TileInfoMap;
};
