#include "GamePCH.h"

#include "Scene.h"

#include "Game/Game.h"

#include "GameObjects/GameObject.h"
#include "GameObjects/Trainer.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"

#include "Mesh/Canvas.h"
#include "Mesh/Mesh.h"


Scene::Scene(GameCore * myGame, Areas myArea, TileMap* aTileMap, ResourceManager * aResourceManager, Mesh* aMesh, Trainer* aPlayer, GLuint aTexture)
{
	m_pMyGame = myGame;
	m_pMyResourceManager = aResourceManager;
	m_pMyTexture = aTexture;
	m_pMyMesh = aMesh;
	m_MyArea = myArea;
}

Scene::~Scene()
{

}

void Scene::Update(float delatime)
{
}

void Scene::Draw(vec2 camPos, vec2 camProjection)
{
}

void Scene::OnEvent(Event * anEvent)
{
}

void Scene::SetIsActive(bool setActive)
{
	m_Active = setActive;

	if (m_Active == true)
	{
		Reload();
	}
	else if (m_Active == false)
	{
		Unload();
	}
}

void Scene::SetPlayerStart(vec2 PlayerLastPos)
{
}

