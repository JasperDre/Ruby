#pragma once

#include "Entities/Entity.h"

class TileMap;
class ResourceManager;

class ScoreNumber : public Entity
{
public:
	ScoreNumber(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* myGame, Mesh* aMesh, unsigned int aTextureIdentifier);
	~ScoreNumber() override;

	void Update(float deltatime) override {}
	void Draw(Vector2Float camPos, Vector2Float camProjection) override;

	void SetScore(int aScore);

private:
	std::vector<Frame> myScoreFrames;
	TileMap* myExtrasTileMap;
	ResourceManager* myResourceManager;
};