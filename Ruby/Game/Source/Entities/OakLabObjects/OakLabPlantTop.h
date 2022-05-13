#pragma once

#include "Entities/Sprite.h"

#include <array>

class OakLabPlantTop : public Sprite
{
public:
	OakLabPlantTop(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier);
	~OakLabPlantTop() override;

	void Update(float deltatime) override {}
	void Draw(Vector2Float camPos, Vector2Float camProject) override;

private:
	std::array<unsigned short, 2> OakLabPlantMap;
	Vector2Float OaklabPlantPosition;
};