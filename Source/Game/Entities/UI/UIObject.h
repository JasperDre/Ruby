#pragma once

#include "Entities/Entity.h"

class TileMap;
class PokeBall;
class ScoreNumber;
class ResourceManager;
class Mesh;

class UIObject : public Entity
{
public:
	UIObject(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier);
	~UIObject() override;

	void Update(float deltatime) override {}
	void Draw(Vector2Float camPos, Vector2Float camProjection) override;

	void SetScore(int aScore) const;

private:
	PokeBall* myPokeBall;
	ScoreNumber* myScoreNumber;
};