#pragma once

#include "Scene.h"

class Mesh;
class Player;
class TileMap;
class TileMapOakLab;
class OakLabLevel;
class OakLabDeskTop;
class OakLabMachineTop;
class OakLabPlantTop;
class OakLabTableTop;
class ProfessorOak;
class AIController;

class OakLab : public Scene
{
public:
	OakLab(GameCore* myGame, Areas myArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Player* aPlayer, GLuint aTexture);
	~OakLab() override;

	void LoadContent() override;
	void Update(float deltatime) override;
	void Draw(Vector2Float camPos, Vector2Float camProjection) override;
	void OnIsActive() override;
	void Reload() override;
	void Unload() override;
	void OnEvent(Event* /*anEvent*/) override {}

private:
	Vector2Float m_OakStartPosition;
	Mesh* m_ProfOakMesh;
	ProfessorOak* m_ProfOak;
	AIController* m_OakAIController;
	OakLabLevel* m_OakLabMap;
	OakLabDeskTop* m_OakLabWorkDesk;
	OakLabMachineTop* m_OakLabMachineTop;
	OakLabPlantTop* m_OakLabPlantTops;
	OakLabTableTop* m_OakLabTableTop;
};