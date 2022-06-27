#pragma once

#include "TileMap.h"

#include <map>

class GameCore;

class TileMapOakLab : public TileMap
{
public:
	TileMapOakLab(GameCore* aGameCore, Area anArea);
	~TileMapOakLab() override;

	void LoadTileTypeMap(const std::string& /*aFilepath*/) override {}
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
		{ "Oak_Lab_BookShelf_1.png", OakLabTileType::BookShelf }, { "Oak_Lab_BookShelf_2.png", OakLabTileType::BookShelf },
		{ "Oak_Lab_BookShelf_3.png", OakLabTileType::BookShelf }, { "Oak_Lab_BookShelf_4.png", OakLabTileType::BookShelf },
		{ "Oak_Lab_BookShelf_5.png", OakLabTileType::BookShelf }, { "Oak_Lab_BookShelf_6.png", OakLabTileType::BookShelf },
		{ "Oak_Lab_BookShelf_7.png", OakLabTileType::BookShelf }, { "Oak_Lab_BookShelf_8.png", OakLabTileType::BookShelf },
		{ "Oak_Lab_BookShelf_9.png", OakLabTileType::BookShelf }, { "Oak_Lab_BookShelf_10.png", OakLabTileType::BookShelf },
		{ "Oak_Lab_BookShelf_11.png", OakLabTileType::BookShelf }, { "Oak_Lab_BookShelf_12.png", OakLabTileType::BookShelf },
		{ "Oak_Lab_BookShelf_13.png", OakLabTileType::BookShelf }, { "Oak_Lab_BookShelf_14.png", OakLabTileType::BookShelf },
		{ "Oak_Lab_BookShelf_15.png", OakLabTileType::BookShelf }, { "Oak_Lab_BookShelf_16.png", OakLabTileType::BookShelf },
		{ "Oak_Lab_BookShelf_17.png", OakLabTileType::BookShelf }, { "Oak_Lab_BookShelf_18.png", OakLabTileType::BookShelf },
		{ "Oak_Lab_BookShelf_19.png", OakLabTileType::BookShelf }, { "Oak_Lab_BookShelf_20.png", OakLabTileType::BookShelf },
		{ "Oak_Lab_BookShelf_21.png", OakLabTileType::BookShelf }, { "Oak_Lab_BookShelf_22.png", OakLabTileType::BookShelf },
		{ "Oak_Lab_BookShelf_23.png", OakLabTileType::BookShelf }, { "Oak_Lab_BookShelf_24.png", OakLabTileType::BookShelf },
		{ "Oak_Lab_BookShelf_25.png", OakLabTileType::BookShelf }, { "Oak_Lab_BookShelf_26.png", OakLabTileType::BookShelf },
		{ "Oak_Lab_BookShelf_27.png", OakLabTileType::BookShelf }, { "Oak_Lab_BookShelf_28.png", OakLabTileType::BookShelf },
		{ "Oak_Lab_Entrance_1.png", OakLabTileType::Entrance }, { "Oak_Lab_Entrance_2.png", OakLabTileType::Entrance },
		{ "Oak_Lab_Entrance_3.png", OakLabTileType::Entrance }, { "Oak_Lab_Entrance_4.png", OakLabTileType::Entrance },
		{ "Oak_Lab_Floor_1.png", OakLabTileType::Floor }, { "Oak_Lab_Floor_2.png", OakLabTileType::Floor },
		{ "Oak_Lab_Floor_3.png", OakLabTileType::Floor }, { "Oak_Lab_Floor_4.png", OakLabTileType::Floor },
		{ "Oak_Lab_Floor_5.png", OakLabTileType::Floor }, { "Oak_Lab_Floor_6.png", OakLabTileType::Floor },
		{ "Oak_Lab_Floor_7.png", OakLabTileType::Floor }, { "Oak_Lab_Floor_8.png", OakLabTileType::Floor },
		{ "Oak_Lab_Floor_9.png", OakLabTileType::Floor }, { "Oak_Lab_Floor_10.png", OakLabTileType::Floor },
		{ "Oak_Lab_Floor_11.png", OakLabTileType::Floor }, { "Oak_Lab_Floor_12.png", OakLabTileType::Floor },
		{ "Oak_Lab_Floor_9.png", OakLabTileType::Floor }, { "Oak_Lab_Floor_10.png", OakLabTileType::Floor },
		{ "Oak_Lab_Floor_1.png", OakLabTileType::Floor }, { "Oak_Lab_Floor_1.png", OakLabTileType::Floor },
		{ "Oak_Lab_Floor_13.png", OakLabTileType::Floor }, { "Oak_Lab_Floor_14.png", OakLabTileType::Floor },
		{ "Oak_Lab_Floor_15.png", OakLabTileType::Floor }, { "Oak_Lab_Floor_16.png", OakLabTileType::Floor },
		{ "Oak_Lab_Floor_17.png", OakLabTileType::Floor }, { "Oak_Lab_Floor_18.png", OakLabTileType::Floor },
		{ "Oak_Lab_Floor_19.png", OakLabTileType::Floor }, { "Oak_Lab_Floor_20.png", OakLabTileType::Floor },
		{ "Oak_Lab_Floor_21.png", OakLabTileType::Floor }, { "Oak_Lab_Floor_22.png", OakLabTileType::Floor },
		{ "Oak_Lab_Machine_1.png", OakLabTileType::Machine }, { "Oak_Lab_Machine_2.png", OakLabTileType::Machine },
		{ "Oak_Lab_Machine_3.png", OakLabTileType::Machine }, { "Oak_Lab_Machine_4.png", OakLabTileType::Machine },
		{ "Oak_Lab_Machine_5.png", OakLabTileType::Machine }, { "Oak_Lab_Machine_6.png", OakLabTileType::Machine },
		{ "Oak_Lab_Plant_1.png", OakLabTileType::Plant }, { "Oak_Lab_Plant_2.png", OakLabTileType::Plant },
		{ "Oak_Lab_Plant_3.png", OakLabTileType::Plant }, { "Oak_Lab_Plant_4.png", OakLabTileType::Plant },
		{ "Oak_Lab_Seat_1.png", OakLabTileType::Seat }, { "Oak_Lab_Table_1.png", OakLabTileType::Table },
		{ "Oak_Lab_Table_2.png", OakLabTileType::Table }, { "Oak_Lab_Table_3.png", OakLabTileType::Table },
		{ "Oak_Lab_Table_4.png", OakLabTileType::Table }, { "Oak_Lab_Table_5.png", OakLabTileType::Table },
		{ "Oak_Lab_Table_6.png", OakLabTileType::Table }, { "Oak_Lab_Wall_1.png", OakLabTileType::Wall },
		{ "Oak_Lab_Wall_2.png", OakLabTileType::Wall }, { "Oak_Lab_Wall_3.png", OakLabTileType::Wall },
		{ "Oak_Lab_Wall_4.png", OakLabTileType::Wall }, { "Oak_Lab_Wall_5.png", OakLabTileType::Wall },
		{ "Oak_Lab_Wall_6.png", OakLabTileType::Wall }, { "Oak_Lab_Wall_7.png", OakLabTileType::Wall },
		{ "Oak_Lab_Wall_8.png", OakLabTileType::Wall }, { "Oak_Lab_Wall_9.png", OakLabTileType::Wall },
		{ "Oak_Lab_Wall_10.png", OakLabTileType::Wall }, { "Oak_Lab_WorkDesk_1.png", OakLabTileType::WorkDesk },
		{ "Oak_Lab_WorkDesk_2.png", OakLabTileType::WorkDesk }, { "Oak_Lab_WorkDesk_3.png", OakLabTileType::WorkDesk },
		{ "Oak_Lab_WorkDesk_4.png", OakLabTileType::WorkDesk }, { "Oak_Lab_WorkDesk_5.png", OakLabTileType::WorkDesk },
		{ "Oak_Lab_WorkDesk_6.png", OakLabTileType::WorkDesk }, { "Oak_Lab_WorkDesk_7.png", OakLabTileType::WorkDesk },
		{ "Oak_Lab_WorkDesk_8.png", OakLabTileType::WorkDesk }, { "Oak_Lab_WorkDesk_9.png", OakLabTileType::WorkDesk },
		{ "Oak_Lab_WorkDesk_10.png", OakLabTileType::WorkDesk }, { "Oak_Lab_WorkDesk_11.png", OakLabTileType::WorkDesk },
		{ "Oak_Lab_WorkDesk_12.png", OakLabTileType::WorkDesk }
	};

	std::map<OakLabTileType, TileInfo> m_TileInfoMap;
};
