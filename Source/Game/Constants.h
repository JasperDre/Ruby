#pragma once

#include "Math/Vector2Float.h"

// Area names used to call the conrtuctors of initial areas through the Scene Manager as well as switching the active scene & loading/unloading inactive scenes
enum class Area
{
	PalletTown,
	TrainerHouse,
	RivalHouse,
	OakLab,
	Woods,
	Null
};

constexpr const char* AreaToString(Area anArea)
{
	switch (anArea)
	{
		case Area::PalletTown: return "PalletTown";
		case Area::TrainerHouse: return "TrainerHouse";
		case Area::RivalHouse: return "RivalHouse";
		case Area::OakLab: return "OakLab";
		case Area::Woods: return "Woods";
		case Area::Null: return "Null";
	}

	return "";
}

// Names of Textures used to call texture charactistics from ResourceManager
enum class TextureHandle
{
	TileSet,
	OakLabTileSet,
	Player_NPCSprites,
	ForestTileSet,
	BattleScene,
	Extras
};

// Base Tile Types per Area, mask is base 0 - 15
enum Tile_Type
{
	Trainer_House_ = 0,	 //(0000 0000 0000 0000)
	Oak_House_ = 1,		 //(0000 0000 0000 0001)
	Town_Sign_ = 2,		 //(0000 0000 0000 0010)
	Town_MailBox_ = 3,	 //(0000 0000 0000 0011)
	Town_Fence_ = 4,	 //(0000 0000 0000 0100)
	Town_Grass_A_ = 5,	 //(0000 0000 0000 0101)
	Town_Flower_ = 6,	 //(0000 0000 0000 0110)
	Town_Grass_B_ = 7,	 //(0000 0000 0000 0111)
	Wild_Grass_ = 8,	 //(0000 0000 0000 1000)
	Water_A_ = 9,		 //(0000 0000 0000 1001)
	Town_Tree_ = 10,	 //(0000 0000 0000 1010)
	Oak_Door_ = 11,		 //(0000 0000 0000 1011)
	Player_Door_ = 12,	 //(0000 0000 0000 1100)
	Town_Null_Door_ = 13,//(0000 0000 0000 1101)
	Town_Null_Wall_ = 14 //(0000 0000 0000 1110)
};

enum OakLab_Tile_Type
{
	Oak_Lab_Floor_ = 0,		//(0000 0000 0000 0000)
	Oak_Lab_Entrance_ = 1,	//(0000 0000 0000 0001)
	Oak_Lab_BookShelf_ = 2,	//(0000 0000 0000 0010)
	Oak_Lab_Machine_ = 3,	//(0000 0000 0000 0011)
	Oak_Lab_Plant_ = 4,		//(0000 0000 0000 0100)
	Oak_Lab_Seat_ = 5,		//(0000 0000 0000 0101)
	Oak_Lab_Table_ = 6,		//(0000 0000 0000 0110)
	Oak_Lab_Wall_ = 7,		//(0000 0000 0000 0111)
	Oak_Lab_WorkDesk_ = 8, //(0000 0000 0000 1000)
	Oak_Lab_NullWall_ = 9, //(0000 0000 0000 1001)
	Oak_Lab_NullDoor_ = 10 //(0000 0000 0000 1010)
};

enum Forest_Tile_Type
{
	Forest_Grass_ = 0,
	Forest_Ridge_ = 1,
	Forest_Tree_ = 2,
	Forest_Wild_Grass_ = 3,
	Forest_Sign_ = 4,
	Forest_Fence_ = 5,
	Forest_Null_Wall = 6,
	Forest_Null_Door = 7
};

// Enum for max number of Tile Variants, the mask for Variants is base 16 - 32,767 - Note: Variant 0 is used when NULL tiles or NULL doors are required for the Area
enum Tile_Variants
{
	TileVariant_0 = 0,		//(0000 0000 0000 0000)
	TileVariant_1 = 16,		//(0000 0000 0001 0000)
	TileVariant_2 = 32,		//(0000 0000 0010 0000)
	TileVariant_3 = 48,		//(0000 0000 0011 0000)
	TileVariant_4 = 64,		//(0000 0000 0100 0000)
	TileVariant_5 = 80,		//(0000 0000 0101 0000)
	TileVariant_6 = 96,		//(0000 0000 0110 0000)
	TileVariant_7 = 112,	//(0000 0000 0111 0000)
	TileVariant_8 = 128,	//(0000 0000 1000 0000)
	TileVariant_9 = 144,	//(0000 0000 1001 0000)
	TileVariant_10 = 160,	//(0000 0000 1010 0000)
	TileVariant_11 = 176,	//(0000 0000 1011 0000)
	TileVariant_12 = 192,	//(0000 0000 1100 0000)
	TileVarient_13 = 208,	//(0000 0000 1101 0000)
	TileVariant_14 = 224,	//(0000 0000 1111 0000)
	TileVariant_15 = 240,	//(0000 0001 0000 0000)
	TileVariant_16 = 256,	//(0000 0001 0001 0000)
	TileVariant_17 = 272,	//(0000 0001 0010 0000)
	TileVariant_18 = 288,	//(0000 0001 0011 0000)
	TileVariant_19 = 304,	//(0000 0001 0100 0000)
	TileVariant_20 = 320,	//(0000 0001 0101 0000)
	TileVariant_21 = 336,	//(0000 0001 0110 0000)
	TileVariant_22 = 352,	//(0000 0001 0111 0000)
	TileVariant_23 = 368,	//(0000 0001 1000 0000)
	TileVariant_24 = 384,	//(0000 0001 1001 0000)
	TileVariant_25 = 400,	//(0000 0001 1010 0000)
	TileVariant_26 = 416,	//(0000 0001 1011 0000)
	TileVariant_27 = 432,	//(0000 0001 1100 0000)
	TileVariant_28 = 448,	//(0000 0001 1101 0000)
	TileVariant_29 = 464,	//(0000 0001 0110 0000)
	TileVariant_30 = 480,	//(0000 0001 1111 0000)
	TileVariant_31 = 496,	//(0000 0010 0000 0000)
	TileVariant_32 = 512,	//(0000 0010 0001 0000)
	TileVariant_33 = 528,	//(0000 0010 0010 0000)
	TileVariant_34 = 544,	//(0000 0010 0011 0000)
	TileVariant_35 = 560,	//(0000 0010 0100 0000)
};

enum class SpriteDirection
{
	SpriteWalkDown,
	SpriteWalkRight,
	SpriteWalkLeft,
	SpriteWalkUp,
	SpriteDirectionStop
};

const Vector2Float DIRECTIONVECTOR[] = { Vector2Float(0.0f, -1.0f), Vector2Float(1.0f, 0.0f), Vector2Float(-1.0f, 0.0f), Vector2Float(0.0f, 1.0f) };

enum class AI_States
{
	IdleState,
	WalkingState,
	PathingState,
	TrackToPlayerState
};

constexpr float PLAYER_SPEED = 4.4f;
constexpr float NPC_SPEED = 3.6f;
constexpr float TILESIZE = 2.0f;
constexpr unsigned int WORLDWIDTH = 50;
constexpr unsigned int WORLDHEIGHT = 50;
constexpr unsigned int NUM_DIRECTIONS = 4;
constexpr int NUM_TILETYPES = 13;
constexpr int NUM_TILEVARIANTS = 34;
constexpr int NUM_ROWS = 33;
constexpr int NUM_COLUMNS = 32;
constexpr int NUM_LAB_ROWS = 15;
constexpr int NUM_LAB_COLUMNS = 16;
constexpr int OAKMAXPATHSIZE = 20;
constexpr int MAXPATHSIZE_TOWN_NPC = 50;
constexpr int NUM_FOREST_ROWS = 44;
constexpr int NUM_FOREST_COLUMNS = 48;
const Vector2Float PLAYER_START = Vector2Float(9.0f * TILESIZE, 20.0f * TILESIZE);