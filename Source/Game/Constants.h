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
	PlayerNPCSprites,
	ForestTileSet,
	BattleScene,
	Extras
};

enum class PalletTownTileType
{
	TrainerHouse = 0,	//(0000 0000 0000 0000)
	OakHouse = 1,		//(0000 0000 0000 0001)
	TownSign = 2,		//(0000 0000 0000 0010)
	TownMailBox = 3,	//(0000 0000 0000 0011)
	TownFence = 4,		//(0000 0000 0000 0100)
	TownGrassA = 5,		//(0000 0000 0000 0101)
	TownFlower = 6,		//(0000 0000 0000 0110)
	TownGrassB = 7,		//(0000 0000 0000 0111)
	WildGrass = 8,		//(0000 0000 0000 1000)
	WaterA = 9,			//(0000 0000 0000 1001)
	TownTree = 10,		//(0000 0000 0000 1010)
	OakDoor = 11,		//(0000 0000 0000 1011)
	PlayerDoor = 12,	//(0000 0000 0000 1100)
	TownNullDoor = 13,	//(0000 0000 0000 1101)
	TownNullWall = 14,	//(0000 0000 0000 1110)
};

enum class OakLabTileType
{
	OakLabFloor = 0,		//(0000 0000 0000 0000)
	OakLabEntrance = 1,		//(0000 0000 0000 0001)
	OakLabBookShelf = 2,	//(0000 0000 0000 0010)
	OakLabMachine = 3,		//(0000 0000 0000 0011)
	OakLabPlant = 4,		//(0000 0000 0000 0100)
	OakLabSeat = 5,			//(0000 0000 0000 0101)
	OakLabTable = 6,		//(0000 0000 0000 0110)
	OakLabWall = 7,			//(0000 0000 0000 0111)
	OakLabWorkDesk = 8,		//(0000 0000 0000 1000)
	OakLabNullWall = 9,		//(0000 0000 0000 1001)
	OakLabNullDoor = 10,	//(0000 0000 0000 1010)
};

enum class ForestTileType
{
	ForestGrass = 0,
	ForestRidge = 1,
	ForestTree = 2,
	ForestWildGrass = 3,
	ForestSign = 4,
	ForestFence = 5,
	ForestNullWall = 6,
	ForestNullDoor = 7
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

enum class AIStates
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