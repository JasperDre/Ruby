#pragma once

#include "Entities/Entity.h"

class TileMap;
class ResourceManager;

class PokeBall : public Entity
{
public:
	PokeBall(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier);

	void Update(float deltatime) override {}
	void Draw(Vector2Float camPos, Vector2Float camProjection) override;

private:
	Frame myFrame;
	TileMap* myExtrasTileMap;
};