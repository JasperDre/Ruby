#pragma once

#include "GameObjects/GameObject.h"

class TileMap;
class ResourceManager;

class PokeBall : public GameObject
{
public:
	PokeBall(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);

	void Update(float deltatime) override {}

	void Draw(vec2 camPos, vec2 camProjection) override;

private:
	TileMap* m_MyExtrasTileMap;
	ResourceManager* m_MyResourceManager;
	Frame m_MyFrame;
};