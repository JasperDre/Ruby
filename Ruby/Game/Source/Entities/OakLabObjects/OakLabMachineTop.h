#pragma once

#include "Entities/Entity.h"

#include <array>

class Entity;
class Mesh;
class ResourceManager;
class TileMap;

class OakLabMachineTop : public Entity
{
public:
	OakLabMachineTop(ResourceManager* aResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~OakLabMachineTop() override;

	void Update(float deltatime) override {}
	void Draw(Vector2Float camPos, Vector2Float camProject) override;

private:
	std::vector<Frame> m_MyFrames;
	std::array<unsigned short, 2> OakLabMachineMap;
	Vector2Float m_MyTileUVOffset;
	Vector2Float m_MyTileUVScale;
	Vector2Float OaklabMachinePosition;
	TileMap* m_MyTileMap;
};