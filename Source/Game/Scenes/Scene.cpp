#include "GamePCH.h"
#include "Scene.h"

#include "Game/Game.h"
#include "Entities/Player.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

Scene::Scene(GameCore* myGame, Areas myArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Player* aPlayer, Vector2Float aPlayerStartPosition, GLuint aTexture)
	: m_MyArea(myArea)
	, m_pMyPlayerStart(aPlayerStartPosition)
	, m_MyTileMap(aTileMap)
	, m_pMyGame(myGame)
	, m_pMyResourceManager(aResourceManager)
	, m_pMyMesh(aMesh)
	, m_pMyTrainer(aPlayer)
	, m_pMyTexture(aTexture)
	, m_Active(false)
{}

void Scene::SetIsActive(bool setActive)
{
	m_Active = setActive;

	if (m_Active)
	{
		Reload();
	}
	else if (!m_Active)
	{
		Unload();
	}
}