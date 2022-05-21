#include "Scene.h"

#include "Game/Game.h"
#include "Entities/Player.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

Scene::Scene(GameCore* aGame, Area anArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Player* aPlayer, Vector2Float aPlayerStartPosition, unsigned int aTextureIdentifier)
	: myArea(anArea)
	, myPlayerStartPosition(aPlayerStartPosition)
	, myTileMap(aTileMap)
	, myGame(aGame)
	, myResourceManager(aResourceManager)
	, myMesh(aMesh)
	, myPlayer(aPlayer)
	, myTextureIdentifier(aTextureIdentifier)
	, myIsActive(false)
{}

void Scene::SetIsActive(bool setActive)
{
	myIsActive = setActive;

	if (myIsActive)
	{
		Reload();
	}
	else if (!myIsActive)
	{
		Unload();
	}
}