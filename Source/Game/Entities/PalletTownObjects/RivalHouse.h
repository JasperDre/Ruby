#pragma once

#include "Entities/Sprite.h"

#include <array>

class ResourceManager;

class RivalHouse : public Sprite
{
public:
	RivalHouse(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTexture);
	~RivalHouse() override;

	void Update(float deltatime) override {}
	void Draw(Vector2Float camPos, Vector2Float projecScale) override;

private:
	std::array<unsigned short, 5> RivalHouseMap;
};
