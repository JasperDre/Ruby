#pragma once

#include "Constants.h"
#include "Scene.h"

class Event;
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
	OakLab(GameCore* aGameCore, Areas anArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Player* aPlayer, unsigned int aTextureIdentifier);
	~OakLab() override;

	void LoadContent() override;
	void Update(float deltatime) override;
	void Draw(Vector2Float camPos, Vector2Float camProjection) override;
	void OnIsActive() override;
	void Reload() override;
	void Unload() override;
	void OnEvent(Event* /*anEvent*/) override {}

private:
	Vector2Float myOakStartPosition;
	Mesh* myOakMesh;
	ProfessorOak* myOak;
	AIController* myOakAIController;
	OakLabLevel* myOakLabMap;
	OakLabDeskTop* myOakLabWorkDesk;
	OakLabMachineTop* myOakLabMachineTop;
	OakLabPlantTop* myOakLabPlantTops;
	OakLabTableTop* myOakLabTableTop;
};