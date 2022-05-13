#pragma once

#include "Entities/Sprite.h"

#include <array>

class PlayerHouse : public Sprite
{
public:
	PlayerHouse(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTexture);
	~PlayerHouse() override;

	void Update(float deltatime) override {}
	void Draw(Vector2Float camPos, Vector2Float projecScale) override;

private:
	std::array<unsigned short, 5> PlayerHouseMap;
	Vector2Float m_PlayerHousePosition;
};