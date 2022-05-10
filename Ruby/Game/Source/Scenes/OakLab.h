#pragma once

#include "Scene.h"

class Mesh;
class Trainer;
class TileMap;
class TileMapOakLab;
class OakLabMap;
class OakLabDeskTop;
class OakLabMachineTop;
class OakLabPlantTop;
class OakLabTableTop;
class ProfessorOak;
class AIController;

class OakLab : public Scene
{
public:
	OakLab(GameCore* myGame, Areas myArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Trainer* aPlayer, GLuint aTexture);
	~OakLab() override;

	void LoadContent() override;
	void Update(float deltatime) override;
	void Draw(vec2 camPos, vec2 camProjection) override;
	void OnIsActive() override;
	void Reload() override;
	void Unload() override;
	void OnEvent(Event* /*anEvent*/) override {}

private:
	vec2 m_OakStartPosition;
	Mesh* m_ProfOakMesh;
	ProfessorOak* m_ProfOak;
	AIController* m_OakAIController;
	OakLabMap* m_OakLabMap;
	OakLabDeskTop* m_OakLabWorkDesk;
	OakLabMachineTop* m_OakLabMachineTop;
	OakLabPlantTop* m_OakLabPlantTops;
	OakLabTableTop* m_OakLabTableTop;
};