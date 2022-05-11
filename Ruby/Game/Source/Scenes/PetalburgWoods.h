#pragma once

#include "Scenes/Scene.h"

class Mesh;
class TileMap;
class TileMapWoods;
class Trainer;
class PetalburgWoodsMap;

class PetalburgWoods : public Scene
{
public:
	PetalburgWoods(GameCore* myGame, Areas myArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Trainer* aPlayer, GLuint aTexture);
	~PetalburgWoods() override;

	void LoadContent() override;
	void Update(float deltatime) override;
	void Draw(Vector2Float camPos, Vector2Float camProjection) override;
	void OnIsActive() override;
	void Reload() override;
	void Unload() override;
	void OnEvent(Event* /*anEvent*/) override {}

private:
	Vector2Float PlayerSavedPosition;
	PetalburgWoodsMap* m_MyPetalburg;
};