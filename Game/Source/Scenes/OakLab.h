#pragma once
class Scene;
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
	~OakLab();

	void LoadContent();

	void Update(float deltatime);

	void Draw(vec2 camPos, vec2 camProjection) override;

	virtual TileMap* GetMyTileMap() override;

	virtual void OnIsActive() override;

	virtual void Reload() override;

	virtual void Unload() override;

private:

	Mesh* m_ProfOakMesh;

	TileMap* m_MyTileMap;

	Trainer* m_MyTrainer;

	ProfessorOak* m_ProfOak;
	AIController* m_OakAIController;

	OakLabMap* m_OakLabMap;
	OakLabDeskTop* m_OakLabWorkDesk;
	OakLabMachineTop* m_OakLabMachineTop;
	OakLabPlantTop* m_OakLabPlantTops;
	OakLabTableTop* m_OakLabTableTop;

	vec2 m_OakStartPosition;

};