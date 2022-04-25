#pragma once
class GameCore;

using namespace std;

class TileMap
{
protected:

	GameCore* m_pMyGame;

	Areas m_MyArea;

	map<string, Tile_Type>TypeSelecter = {	{"Oak_House_1.png", Oak_House_},			{"Oak_House_2.png", Oak_House_},			{"Oak_House_3.png", Oak_House_},			{"Oak_House_4.png", Oak_House_},			{"Oak_House_5.png", Oak_House_},			{"Oak_House_6.png", Oak_House_}, 
											{"Oak_House_7.png", Oak_House_},			{"Oak_House_8.png", Oak_House_},			{"Oak_House_9.png", Oak_House_},			{"Oak_House_10.png", Oak_House_},			{"Oak_House_11.png", Oak_House_},			{"Oak_House_12.png", Oak_House_},
											{"Oak_House_13.png", Oak_House_},			{"Oak_House_14.png", Oak_House_},			{"Oak_House_15.png", Oak_House_},			{"Oak_House_16.png", Oak_House_},			{"Oak_House_17.png", Oak_House_},			{"Oak_House_18.png", Oak_House_},
											{"Oak_House_19.png", Oak_House_},			{"Oak_House_20.png", Oak_House_},			{"Oak_House_21.png", Oak_House_},			{"Oak_House_22.png", Oak_House_},			{"Oak_House_23.png", Oak_House_},			{"Oak_House_24.png", Oak_House_},
											{"Oak_House_25.png", Oak_House_},			{"Oak_House_26.png", Oak_House_},			{"Oak_House_27.png", Oak_House_},			{"Oak_House_28.png", Oak_House_},			{"Oak_House_29.png", Oak_House_},			{"Oak_House_30.png", Oak_House_},
											{"Oak_House_31.png", Oak_House_},			{"Oak_House_32.png", Oak_Door_},			{"Oak_House_33.png", Oak_House_},			{"Oak_House_34.png", Oak_House_},			{"Oak_House_35.png", Oak_House_},			{"Town_Fence_1.png", Town_Fence_},
											{"Town_Fence_2.png", Town_Fence_},			{"Town_Fence_3.png", Town_Fence_},			{"Town_Fence_4.png", Town_Fence_},			{"Town_Fence_5.png", Town_Fence_},			{"Town_Fence_6.png", Town_Fence_},			{"Town_Fence_7.png", Town_Fence_},
											{"Town_Flower_1.png", Town_Flower_},		{"Town_Grass_A_1.png", Town_Grass_A_},		{"Town_Grass_A_2.png", Town_Grass_A_},		{"Town_Grass_A_3.png", Town_Grass_A_},		{"Town_Grass_A_4.png", Town_Grass_A_},		{"Town_Grass_A_5.png", Town_Grass_A_},
											{"Town_Grass_A_6.png", Town_Grass_A_},		{"Town_Grass_A_7.png", Town_Grass_A_},		{"Town_Grass_A_8.png", Town_Grass_A_},		{"Town_Grass_A_9.png", Town_Grass_A_},		{"Town_Grass_A_10.png", Town_Grass_A_},		{"Town_Grass_A_11.png", Town_Grass_A_},
											{"Town_Grass_A_12.png", Town_Grass_A_},		{"Town_Grass_A_13.png", Town_Grass_A_},		{"Town_Grass_B_1.png", Town_Grass_B_},		{"Town_Grass_B_2.png", Town_Grass_B_},		{"Town_Grass_B_3.png", Town_Grass_B_},		{"Town_Mailbox_1.png", Town_MailBox_},
											{"Town_Mailbox_2.png", Town_MailBox_},		{"Town_Sign_1.png", Town_Sign_},			{"Town_Sign_2.png", Town_Sign_},			{"Town_Tree_1.png", Town_Tree_},			{"Town_Tree_2.png", Town_Tree_},			{"Town_Tree_3.png", Town_Tree_},
											{"Town_Tree_4.png", Town_Tree_},			{"Town_Tree_5.png", Town_Tree_},			{"Town_Tree_6.png", Town_Tree_},			{"Town_Tree_7.png", Town_Tree_},			{"Town_Tree_8.png", Town_Tree_},			{"Town_Tree_9.png", Town_Tree_},
											{"Town_Tree_10.png", Town_Tree_},			{"Trainer_House_1.png", Trainer_House_},	{"Trainer_House_2.png", Trainer_House_},	{"Trainer_House_3.png", Trainer_House_},	{"Trainer_House_4.png", Trainer_House_},
											{"Trainer_House_5.png", Trainer_House_},	{"Trainer_House_6.png", Trainer_House_},	{"Trainer_House_7.png", Trainer_House_},	{"Trainer_House_8.png", Trainer_House_},	{"Trainer_House_9.png", Trainer_House_},
											{"Trainer_House_10.png", Trainer_House_},	{"Trainer_House_11.png", Trainer_House_},	{"Trainer_House_12.png", Trainer_House_},	{"Trainer_House_13.png", Trainer_House_},	{"Trainer_House_14.png", Trainer_House_},
											{"Trainer_House_15.png", Trainer_House_},	{"Trainer_House_16.png", Trainer_House_},	{"Trainer_House_17.png", Trainer_House_},	{"Trainer_House_18.png", Trainer_House_},	{"Trainer_House_19.png", Trainer_House_},
											{"Trainer_House_20.png", Trainer_House_},	{"Trainer_House_21.png", Trainer_House_},	{"Trainer_House_22.png", Player_Door_},		{"Trainer_House_23.png", Trainer_House_},	{"Trainer_House_24.png", Trainer_House_},
											{"Trainer_House_25.png", Trainer_House_},	{"Water_A_1.png", Water_A_},				{"Water_A_2.png", Water_A_},				{"Water_A_3.png", Water_A_},				{"Water_A_4.png", Water_A_},
											{"Water_A_5.png", Water_A_},				{"Water_A_6.png", Water_A_},				{"Water_A_7.png", Water_A_},				{"Water_A_8.png", Water_A_},				{"Water_A_9.png", Water_A_},				{"Wild_Grass_1.png", Wild_Grass_}
	};
	map<string, OakLab_Tile_Type>LabTypeSelecter = { {"Oak_Lab_BookShelf_1.png", Oak_Lab_BookShelf_}, {"Oak_Lab_BookShelf_2.png", Oak_Lab_BookShelf_}, {"Oak_Lab_BookShelf_3.png", Oak_Lab_BookShelf_}, {"Oak_Lab_BookShelf_4.png", Oak_Lab_BookShelf_},
													{"Oak_Lab_BookShelf_5.png", Oak_Lab_BookShelf_}, {"Oak_Lab_BookShelf_6.png", Oak_Lab_BookShelf_}, {"Oak_Lab_BookShelf_7.png", Oak_Lab_BookShelf_}, {"Oak_Lab_BookShelf_8.png", Oak_Lab_BookShelf_},
													{"Oak_Lab_BookShelf_9.png", Oak_Lab_BookShelf_}, {"Oak_Lab_BookShelf_10.png", Oak_Lab_BookShelf_},{"Oak_Lab_BookShelf_11.png", Oak_Lab_BookShelf_},{"Oak_Lab_BookShelf_12.png", Oak_Lab_BookShelf_},
													{"Oak_Lab_BookShelf_13.png", Oak_Lab_BookShelf_},{"Oak_Lab_BookShelf_14.png", Oak_Lab_BookShelf_},{"Oak_Lab_BookShelf_15.png", Oak_Lab_BookShelf_},{"Oak_Lab_BookShelf_16.png", Oak_Lab_BookShelf_},
													{"Oak_Lab_BookShelf_17.png", Oak_Lab_BookShelf_},{"Oak_Lab_BookShelf_18.png", Oak_Lab_BookShelf_},{"Oak_Lab_BookShelf_19.png", Oak_Lab_BookShelf_},{"Oak_Lab_BookShelf_20.png", Oak_Lab_BookShelf_},
													{"Oak_Lab_BookShelf_21.png", Oak_Lab_BookShelf_},{"Oak_Lab_BookShelf_22.png", Oak_Lab_BookShelf_},{"Oak_Lab_BookShelf_23.png", Oak_Lab_BookShelf_},{"Oak_Lab_BookShelf_24.png", Oak_Lab_BookShelf_},
													{"Oak_Lab_BookShelf_25.png", Oak_Lab_BookShelf_},{"Oak_Lab_BookShelf_26.png", Oak_Lab_BookShelf_},{"Oak_Lab_BookShelf_27.png", Oak_Lab_BookShelf_},{"Oak_Lab_BookShelf_28.png", Oak_Lab_BookShelf_},
													{"Oak_Lab_Entrance_1.png", Oak_Lab_Entrance_},   {"Oak_Lab_Entrance_2.png", Oak_Lab_Entrance_},   {"Oak_Lab_Entrance_3.png", Oak_Lab_Entrance_},   {"Oak_Lab_Entrance_4.png", Oak_Lab_Entrance_},
													{"Oak_Lab_Floor_1.png", Oak_Lab_Floor_},		 {"Oak_Lab_Floor_2.png", Oak_Lab_Floor_},		  {"Oak_Lab_Floor_3.png", Oak_Lab_Floor_},         {"Oak_Lab_Floor_4.png", Oak_Lab_Floor_},
													{"Oak_Lab_Floor_5.png", Oak_Lab_Floor_},		 {"Oak_Lab_Floor_6.png", Oak_Lab_Floor_},		  {"Oak_Lab_Floor_7.png", Oak_Lab_Floor_},		   {"Oak_Lab_Floor_8.png", Oak_Lab_Floor_},
													{"Oak_Lab_Floor_9.png", Oak_Lab_Floor_},		 {"Oak_Lab_Floor_10.png", Oak_Lab_Floor_},		  {"Oak_Lab_Floor_11.png", Oak_Lab_Floor_},        {"Oak_Lab_Floor_12.png", Oak_Lab_Floor_},
													{"Oak_Lab_Floor_9.png", Oak_Lab_Floor_},		 {"Oak_Lab_Floor_10.png", Oak_Lab_Floor_},		  {"Oak_Lab_Floor_1.png", Oak_Lab_Floor_},         {"Oak_Lab_Floor_1.png", Oak_Lab_Floor_},
													{"Oak_Lab_Floor_13.png", Oak_Lab_Floor_},		 {"Oak_Lab_Floor_14.png", Oak_Lab_Floor_},		  {"Oak_Lab_Floor_15.png", Oak_Lab_Floor_},        {"Oak_Lab_Floor_16.png", Oak_Lab_Floor_},
													{"Oak_Lab_Floor_17.png", Oak_Lab_Floor_},		 {"Oak_Lab_Floor_18.png", Oak_Lab_Floor_},		  {"Oak_Lab_Floor_19.png", Oak_Lab_Floor_},        {"Oak_Lab_Floor_20.png", Oak_Lab_Floor_},
													{"Oak_Lab_Floor_21.png", Oak_Lab_Floor_},        {"Oak_Lab_Floor_22.png", Oak_Lab_Floor_},		  {"Oak_Lab_Machine_1.png", Oak_Lab_Machine_},     {"Oak_Lab_Machine_2.png", Oak_Lab_Machine_},
													{"Oak_Lab_Machine_3.png", Oak_Lab_Machine_},	 {"Oak_Lab_Machine_4.png", Oak_Lab_Machine_},     {"Oak_Lab_Machine_5.png", Oak_Lab_Machine_},     {"Oak_Lab_Machine_6.png", Oak_Lab_Machine_},     
													{"Oak_Lab_Plant_1.png", Oak_Lab_Plant_},		 {"Oak_Lab_Plant_2.png", Oak_Lab_Plant_},         {"Oak_Lab_Plant_3.png", Oak_Lab_Plant_},         {"Oak_Lab_Plant_4.png", Oak_Lab_Plant_},
													{"Oak_Lab_Seat_1.png", Oak_Lab_Seat_},			 {"Oak_Lab_Table_1.png", Oak_Lab_Table_},		  {"Oak_Lab_Table_2.png", Oak_Lab_Table_},         {"Oak_Lab_Table_3.png", Oak_Lab_Table_},   
													{"Oak_Lab_Table_4.png", Oak_Lab_Table_},		 {"Oak_Lab_Table_5.png", Oak_Lab_Table_},         {"Oak_Lab_Table_6.png", Oak_Lab_Table_},         {"Oak_Lab_Wall_1.png", Oak_Lab_Wall_},
													{"Oak_Lab_Wall_2.png", Oak_Lab_Wall_},			 {"Oak_Lab_Wall_3.png", Oak_Lab_Wall_},           {"Oak_Lab_Wall_4.png", Oak_Lab_Wall_},           {"Oak_Lab_Wall_5.png", Oak_Lab_Wall_},           
													{"Oak_Lab_Wall_6.png", Oak_Lab_Wall_},			 {"Oak_Lab_Wall_7.png", Oak_Lab_Wall_},           {"Oak_Lab_Wall_8.png", Oak_Lab_Wall_},           {"Oak_Lab_Wall_9.png", Oak_Lab_Wall_},           
													{"Oak_Lab_Wall_10.png", Oak_Lab_Wall_},			 {"Oak_Lab_WorkDesk_1.png", Oak_Lab_WorkDesk_},	  {"Oak_Lab_WorkDesk_2.png", Oak_Lab_WorkDesk_},   {"Oak_Lab_WorkDesk_3.png", Oak_Lab_WorkDesk_},   
													{"Oak_Lab_WorkDesk_4.png", Oak_Lab_WorkDesk_},	 {"Oak_Lab_WorkDesk_5.png", Oak_Lab_WorkDesk_},	  {"Oak_Lab_WorkDesk_6.png", Oak_Lab_WorkDesk_},   {"Oak_Lab_WorkDesk_7.png", Oak_Lab_WorkDesk_},   
													{"Oak_Lab_WorkDesk_8.png", Oak_Lab_WorkDesk_},	 {"Oak_Lab_WorkDesk_9.png", Oak_Lab_WorkDesk_},	  {"Oak_Lab_WorkDesk_10.png", Oak_Lab_WorkDesk_},  {"Oak_Lab_WorkDesk_11.png", Oak_Lab_WorkDesk_},
													{"Oak_Lab_WorkDesk_12.png", Oak_Lab_WorkDesk_}
	};
	map<string, Forest_Tile_Type>WoodsTypeSelecter = { {"Forest_Fence_1.png", Forest_Fence_}, {"Forest_Grass_1.png", Forest_Grass_}, {"Forest_Grass_2.png", Forest_Grass_}, {"Forest_Ridge_1.png", Forest_Ridge_},    {"Forest_Ridge_2.png", Forest_Ridge_}, {"Forest_Ridge_3.png", Forest_Ridge_}, 
													   {"Forest_Sign_1.png", Forest_Sign_},   {"Forest_Tree_1.png", Forest_Tree_},   {"Forest_Tree_2.png", Forest_Tree_},   {"Forest_Tree_3.png", Forest_Tree_},      {"Forest_Tree_4.png", Forest_Tree_},   {"Forest_Tree_5.png", Forest_Tree_},
													   {"Forest_Tree_6.png", Forest_Tree_},   {"Forest_Tree_7.png", Forest_Tree_},   {"Forest_Tree_8.png", Forest_Tree_},   {"Forest_Wild_Grass_1.png", Forest_Wild_Grass_}, {"Forest_Wild_Grass_2.png", Forest_Wild_Grass_} };


public:
	TileMap(GameCore* myGame, Areas aArea);
	virtual ~TileMap();

	virtual void AddTile(const string& anIndex, Frame aFrame) = 0;

	virtual bool GetTileAtPlayer(ivec2 playerColumnRow) = 0;
	
	virtual bool GetTileAtNPC(ivec2 npcColumnRow) = 0;

	virtual TileInfo GetTileFromPalletMap(Tile_Type aType);

	virtual TileInfo GetTileFromOakLabMap(OakLab_Tile_Type aType);

	virtual TileInfo GetTileFromWoodsMap(Forest_Tile_Type aType);

	virtual TileInfo GetTileAtIndex(int anIndex) { return aNullTileInfo; }
	virtual Frame GetFrameFromExtrasMap(string anIndex) { return aNullFrame; }
	virtual int GetMapWidth() = 0;
	virtual int GetMapHeight() = 0;
	virtual int GetIndexFromColumnRow(int aColumn, int aRow) = 0;
	virtual ivec2 GetColumRowFromIndex(int anIndex) = 0;
private:
	Frame aNullFrame;
	TileInfo aNullTileInfo;
};
