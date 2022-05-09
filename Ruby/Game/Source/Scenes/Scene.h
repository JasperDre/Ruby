#pragma once

#include <vector>

class GameCore;
class Mesh;
class ResourceManager;
class TileMap;
class GameObject;
class Trainer;

class Scene
{
public:
	Scene(GameCore* myGame, Areas myArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Trainer* aPlayer, GLuint aTexture);
	virtual ~Scene();

	virtual void LoadContent() = 0;

	virtual void Update(float delatime);

	virtual void Draw(vec2 camPos, vec2 camProjection);

	virtual void OnEvent(Event* anEvent);

	virtual void SetIsActive(bool setActive);
	virtual bool GetIsActive() { return m_Active; }

	virtual void OnIsActive() = 0;

	virtual Areas GetMyArea() { return m_MyArea; }

	virtual Trainer* GetMyPlayer() { return m_pMyTrainer; }

	virtual TileMap* GetMyTileMap() = 0;

	virtual void SetPlayerStart(vec2 PlayerLastPos);
	virtual vec2 GetPlayerStart() { return m_pMyPlayerStart; }

	virtual void Reload() = 0;
	virtual void Unload() = 0;

protected:
	std::vector<GameObject*> m_MyGameObjects;
	Areas m_MyArea;
	vec2 m_pMyPlayerStart;
	GameCore* m_pMyGame;
	ResourceManager* m_pMyResourceManager;
	Mesh* m_pMyMesh;
	Trainer* m_pMyTrainer;
	GLuint m_pMyTexture;
	bool m_Active;
};