#pragma once

#include <map>

class Scene;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void GenerateScenes(GameCore* myGame, Areas myArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Trainer* aPlayer, GLuint aTexture);

	void SetActiveScene(Areas aSceneHandle);

	Scene* GetActiveScene();

	void OnEvent(Event* anEvent);

	void SetPlayerSavedPosition(vec2 aPosition) { m_PlayerSavedPosition = aPosition; }

private:
	std::map<Areas, Scene*> m_MyScenes;
	vec2 m_PlayerSavedPosition;
};