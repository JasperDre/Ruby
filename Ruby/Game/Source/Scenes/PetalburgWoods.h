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
	~PetalburgWoods();

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
	PetalburgWoodsMap* m_MyPetalburg;
	vec2 PlayerSavedPosition;

};