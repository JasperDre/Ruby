#pragma once

#include "Entities/Sprite.h"

#include <array>

class ResourceManager;

class OakLabMachineTop : public Sprite
{
public:
	OakLabMachineTop(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier);
	~OakLabMachineTop() override;

	void Update(float deltatime) override {}
	void Draw(Vector2Float camPos, Vector2Float camProject) override;

private:
	std::array<unsigned short, 2> myOakLabMachineMap;
};
