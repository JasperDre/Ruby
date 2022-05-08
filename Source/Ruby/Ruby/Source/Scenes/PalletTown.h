#pragma once

class Scene;
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
	~PalletTown();

	void LoadContent();

	void Update(float deltatime);

	void Draw(vec2 camPos, vec2 camProjection) override;

	virtual TileMap* GetMyTileMap() override;

	virtual void OnIsActive() override;

	virtual void Reload() override;

	virtual void Unload() override;

private:

	TileMap* m_MyTileMap;

	Trainer* m_MyTrainer;
	PalletTownMap* m_PalletTownMap;
	OakHouse* m_OakHouseTop;
	PlayerHouse* m_PlayerHouseTop;
	RivalHouse* m_RivalHouseTop;

	Mesh* m_MyGirlMesh;
	Mesh* m_MyBoyMesh;

	TownGirl* m_GirlNPC;
	TownBoy* m_BoyNPC;

	vec2 PlayerSavedPosition;
	vec2 GirlSavedPosition;
	vec2 BoySavedPosition;
	vec2 m_GirlNPCStart;
	vec2 m_BoyNPCStart;
};