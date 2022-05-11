#pragma once

#include "Entities/Entity.h"

class TileMap;
class ResourceManager;

class PokeBall : public Entity
{
public:
	PokeBall(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);

	void Update(float deltatime) override {}

	void Draw(Vector2Float camPos, Vector2Float camProjection) override;

private:
	TileMap* m_MyExtrasTileMap;
	ResourceManager* m_MyResourceManager;
	Frame m_MyFrame;
};