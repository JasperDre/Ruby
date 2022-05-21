#pragma once

#include <map>

#include "Constants.h"

class Event;
class Player;
class TileMap;
class GameCore;
class Mesh;
class Scene;
class ResourceManager;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void GenerateScenes(GameCore* aGameCore, Area anArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Player* aPlayer, unsigned int aTextureIdentifier);
	void OnEvent(Event* anEvent) const;

	void SetActiveScene(Area aSceneHandle) const;
	void SetSavedPlayerPosition(Vector2Float aPosition) { mySavedPlayerPosition = aPosition; }

	[[nodiscard]] Scene* GetActiveScene() const;

private:
	std::map<Area, Scene*> myScenes;
	Vector2Float mySavedPlayerPosition;
};