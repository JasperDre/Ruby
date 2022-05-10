#pragma once

#include "Scene.h"

class Mesh;
class TileMap;
class TileMapPalletTown;
class PalletTownMap;
class OakHouse;
class PlayerHouse;
class RivalHouse;
class Trainer;
class TownGirl;
class TownBoy;

class PalletTown : public Scene
{

public:
	PalletTown(GameCore* myGame, Areas myArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Trainer* aPlayer, GLuint aTexture);
	~PalletTown() override;

	void LoadContent() override;
	void Update(float deltatime) override;
	void Draw(vec2 camPos, vec2 camProjection) override;
	void OnIsActive() override;
	void Reload() override;
	void Unload() override;
	void OnEvent(Event* /*anEvent*/) override {}

private:
	vec2 PlayerSavedPosition;
	vec2 GirlSavedPosition;
	vec2 BoySavedPosition;
	vec2 m_GirlNPCStart;
	vec2 m_BoyNPCStart;
	PalletTownMap* m_PalletTownMap;
	OakHouse* m_OakHouseTop;
	PlayerHouse* m_PlayerHouseTop;
	RivalHouse* m_RivalHouseTop;
	Mesh* m_MyGirlMesh;
	Mesh* m_MyBoyMesh;
	TownGirl* m_GirlNPC;
	TownBoy* m_BoyNPC;
};