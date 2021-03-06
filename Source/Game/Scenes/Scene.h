#pragma once

#include <vector>

#include "Constants.h"

class Event;
class GameCore;
class Mesh;
class ResourceManager;
class TileMap;
class Entity;
class Player;

class Scene
{
public:
	Scene(GameCore* aGame, Area anArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Player* aPlayer, Vector2Float aPlayerStartPosition, unsigned int aTextureIdentifier);
	virtual ~Scene() = default;

	virtual void LoadContent() = 0;
	virtual void Update(float delatime) = 0;
	virtual void Draw(Vector2Float camPos, Vector2Float camProjection) = 0;
	virtual void OnEvent(Event* anEvent) = 0;
	virtual void OnIsActive() = 0;
	virtual void Unload() = 0;
	virtual void Reload() = 0;

	virtual void SetIsActive(bool setActive);
	virtual void SetPlayerStart(Vector2Float PlayerLastPos) { myPlayerStartPosition = PlayerLastPos; }

	[[nodiscard]] virtual bool IsActive() const { return myIsActive; }
	[[nodiscard]] virtual Area GetArea() const { return myArea; }
	[[nodiscard]] virtual Player* GetPlayer() const { return myPlayer; }
	[[nodiscard]] virtual TileMap* GetTilemap() const { return myTileMap;}
	[[nodiscard]] virtual Vector2Float GetPlayerStart() const { return myPlayerStartPosition; }

protected:
	std::vector<Entity*> myEntities;
	Area myArea;
	Vector2Float myPlayerStartPosition;
	TileMap* myTileMap;
	GameCore* myGame;
	ResourceManager* myResourceManager;
	Mesh* myMesh;
	Player* myPlayer;
	unsigned int myTextureIdentifier;
	bool myIsActive;
};