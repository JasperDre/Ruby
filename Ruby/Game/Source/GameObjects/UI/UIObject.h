#pragma once

#include "GameObjects/GameObject.h"

class TileMap;
class PokeBall;
class ScoreNumber;

class UIObject : public GameObject
{
public:
	UIObject(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~UIObject() override;

	void Update(float deltatime) override;
	void Draw(vec2 camPos, vec2 camProjection) override;

	void SetScore(int aScore) const;
private:
	PokeBall* m_PokeBall;
	ScoreNumber* m_ScoreNumber;
};