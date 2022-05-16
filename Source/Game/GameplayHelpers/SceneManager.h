#pragma once

#include <map>

class Mesh;
class Scene;
class ResourceManager;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void GenerateScenes(GameCore* aGameCore, Areas anArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Player* aPlayer, unsigned int aTextureIdentifier);
	void OnEvent(Event* anEvent) const;

	void SetActiveScene(Areas aSceneHandle) const;
	void SetSavedPlayerPosition(Vector2Float aPosition) { mySavedPlayerPosition = aPosition; }

	[[nodiscard]] Scene* GetActiveScene() const;

private:
	std::map<Areas, Scene*> myScenes;
	Vector2Float mySavedPlayerPosition;
};