#pragma once

#include "Entities/Sprite.h"

#include <array>

class ResourceManager;

class OakLabDeskTop : public Sprite
{
public:
	OakLabDeskTop(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier);
	~OakLabDeskTop() override;

	void Update(float deltatime) override {}
	void Draw(Vector2Float camPos, Vector2Float camProject) override;

private:
	std::array<unsigned short, 6> myOakLabDeskTopMap;
};
