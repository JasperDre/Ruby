#pragma once

#include "Entities/Entity.h"

class Entity;
class Mesh;
class ResourceManager;
class TileMap;

class OakLabMachineTop : public Entity
{
public:
	OakLabMachineTop(ResourceManager * myResourceManager, TileMap * myTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture);
	~OakLabMachineTop() override;

	virtual void Update(float deltatime) override;

	virtual void Draw(Vector2Float camPos, Vector2Float camProject) override;

private:

	const unsigned short OakLabMachineMap[2]{ 4, 5 };

	const unsigned short OakLabMachine_NumTiles = 2;

	ResourceManager* m_MyResourceManager;
	TileMap* m_MyTileMap;
	std::vector<Frame> m_MyFrames;

	Vector2Float m_MyTileUVOffset;
	Vector2Float m_MyTileUVScale;

	Vector2Float OaklabMachinePosition;

};