#pragma once

#include "Scene.h"

class Mesh;
class TileMap;
class TileMapPalletTown;
class PalletTownMap;
class OakHouse;
class PlayerHouse;
class RivalHouse;
class Player;
class TownGirl;
class TownBoy;

class PalletTown : public Scene
{

public:
	PalletTown(GameCore* myGame, Areas myArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Player* aPlayer, GLuint aTexture);
	~PalletTown() override;

	void LoadContent() override;
	void Update(float deltatime) override;
	void Draw(Vector2Float camPos, Vector2Float camProjection) override;
	void OnIsActive() override;
	void Reload() override;
	void Unload() override;
	void OnEvent(Event* /*anEvent*/) override {}

private:
	Vector2Float PlayerSavedPosition;
	Vector2Float GirlSavedPosition;
	Vector2Float BoySavedPosition;
	Vector2Float m_GirlNPCStart;
	Vector2Float m_BoyNPCStart;
	PalletTownMap* m_PalletTownMap;
	OakHouse* m_OakHouseTop;
	PlayerHouse* m_PlayerHouseTop;
	RivalHouse* m_RivalHouseTop;
	Mesh* m_MyGirlMesh;
	Mesh* m_MyBoyMesh;
	TownGirl* m_GirlNPC;
	TownBoy* m_BoyNPC;
};