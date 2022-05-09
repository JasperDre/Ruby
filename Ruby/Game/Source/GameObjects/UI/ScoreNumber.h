#pragma once

#include "GameObjects/GameObject.h"

class TileMap;
class ResourceManager;

class ScoreNumber : public GameObject
{
public:
	ScoreNumber(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~ScoreNumber() override;

	void Update(float deltatime) override {}
	void Draw(vec2 camPos, vec2 camProjection) override;

	void SetScore(int aScore);

private:
	std::vector<Frame>MyScoreFrames;
	int DigitsOnScore[6];
	TileMap* m_MyExtrasTileMap;
	ResourceManager* m_MyResourceManager;
};