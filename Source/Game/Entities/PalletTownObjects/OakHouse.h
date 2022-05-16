#pragma once

#include "Entities/Sprite.h"

#include <array>

class ResourceManager;

class OakHouse : public Sprite
{
public:
	OakHouse(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier);
	~OakHouse() override;

	void Update(float deltatime) override {}
	void Draw(Vector2Float camPos, Vector2Float projecScale) override;

private:
	std::array<unsigned short, 7> myOakHouseMap;
};
