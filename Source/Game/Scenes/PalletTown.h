#pragma once

#include "Constants.h"
#include "Scene.h"

class Event;
class Mesh;
class TileMap;
class TileMapPalletTown;
class PalletTownLevel;
class OakHouse;
class PlayerHouse;
class RivalHouse;
class Player;
class TownGirl;
class TownBoy;

class PalletTown : public Scene
{

public:
	PalletTown(GameCore* aGameCore, Area anArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Player* aPlayer, unsigned int aTextureIdentifier);
	~PalletTown() override;

	void LoadContent() override;
	void Update(float deltatime) override;
	void Draw(Vector2Float camPos, Vector2Float camProjection) override;
	void OnIsActive() override;
	void Reload() override {}
	void Unload() override;
	void OnEvent(Event* /*anEvent*/) override {}

private:
	Vector2Float mySavedPlayerPosition;
	Vector2Float mySavedGirlPosition;
	Vector2Float mySavedBoyPosition;
	Vector2Float myGirlNPCStartPosition;
	Vector2Float myBoyNPCStartPosition;
	PalletTownLevel* myPalletTownMap;
	OakHouse* myOakHouseTop;
	PlayerHouse* myPlayerHouseTop;
	RivalHouse* myRivalHouseTop;
	Mesh* myGirlMesh;
	Mesh* myBoyMesh;
	TownGirl* myGirlNPC;
	TownBoy* myBoyNPC;
};