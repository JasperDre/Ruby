#pragma once

#include <vector>

#include "Entity.h"
#include "GameplayHelpers/Frame.h"

class Mesh;
class TileMap;
class GameCore;

class Sprite : public Entity
{
public:
	Sprite(TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier);
	~Sprite() override = default;

	void Update(float deltatime) override {}
	void Draw(Vector2Float camPos, Vector2Float camProject) override {}

protected:
	std::vector<Frame> myFrames;
	Vector2Float myTileUVOffset;
	Vector2Float myTileUVScale;
	TileMap* myTileMap;
};