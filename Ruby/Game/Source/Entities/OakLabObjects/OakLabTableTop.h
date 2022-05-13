#pragma once

#include "Entities/Sprite.h"

#include <array>

class OakLabTableTop : public Sprite
{
public:
	OakLabTableTop(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTexture);
	~OakLabTableTop() override;

	void Update(float deltatime) override {}
	void Draw(Vector2Float camPos, Vector2Float camProject) override;

private:
	std::array<unsigned short, 3> OakLabTableTopMap;
	Vector2Float OakLabTableTopPosition;
};