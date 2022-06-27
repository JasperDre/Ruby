#pragma once

#include "Constants.h"
#include "Scenes/Scene.h"

class Event;
class Mesh;
class TileMap;
class TileMapRoute1;
class Player;
class PetalburgWoodsLevel;

class PetalburgWoods : public Scene
{
public:
	PetalburgWoods(GameCore* aGameCore, Area anArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Player* aPlayer, unsigned int aTextureIdentifier);
	~PetalburgWoods() override;

	void LoadContent() override;
	void Update(float deltatime) override;
	void Draw(Vector2Float camPos, Vector2Float camProjection) override;
	void OnIsActive() override;
	void Reload() override {}
	void Unload() override;
	void OnEvent(Event* /*anEvent*/) override {}

private:
	Vector2Float PlayerSavedPosition;
	PetalburgWoodsLevel* m_MyPetalburg;
};