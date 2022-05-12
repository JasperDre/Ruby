#pragma once

#include "Entities/Entity.h"

class TileMap;
class PokeBall;
class ScoreNumber;

class UIObject : public Entity
{
public:
	UIObject(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~UIObject() override;

	void Update(float deltatime) override {}
	void Draw(Vector2Float camPos, Vector2Float camProjection) override;

	void SetScore(int aScore) const;
private:
	PokeBall* m_PokeBall;
	ScoreNumber* m_ScoreNumber;
};