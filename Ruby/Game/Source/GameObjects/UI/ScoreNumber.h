#pragma once

#include "GameObjects/Entity.h"

class TileMap;
class ResourceManager;

class ScoreNumber : public Entity
{
public:
	ScoreNumber(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~ScoreNumber() override;

	void Update(float deltatime) override {}
	void Draw(Vector2Float camPos, Vector2Float camProjection) override;

	void SetScore(int aScore);

private:
	std::vector<Frame>MyScoreFrames;
	TileMap* m_MyExtrasTileMap;
	ResourceManager* m_MyResourceManager;
};