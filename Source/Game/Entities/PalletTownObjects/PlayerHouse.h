#pragma once

#include "Entities/Sprite.h"

#include <array>

class ResourceManager;

class PlayerHouse : public Sprite
{
public:
	PlayerHouse(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier);
	~PlayerHouse() override;

	void Update(float deltatime) override {}
	void Draw(Vector2Float camPos, Vector2Float projecScale) override;

private:
	std::array<unsigned short, 5> myPlayerHouseMap;
};
