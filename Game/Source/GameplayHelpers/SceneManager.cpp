#include "GamePCH.h"
#include "GameplayHelpers/SceneManager.h"
#include "SceneManager.h"

#include "Scenes/Scene.h"
#include "Scenes/PalletTown.h"
#include "Scenes/OakLab.h"
#include "Scenes/PetalBergWoods.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
	delete m_MyScenes.at(Area_PalletTown);
	delete m_MyScenes.at(Area_OakLab);
	delete m_MyScenes.at(Area_Woods);
}

void SceneManager::GenerateScenes(GameCore * myGame, Areas myArea, TileMap* aTileMap, ResourceManager * aResourceManager, Mesh* aMesh, Trainer* aPlayer, GLuint aTexture)
{
	if(myArea == Area_PalletTown)
	{
		PalletTown* MyNewScene = new PalletTown(myGame, Area_PalletTown, aTileMap, aResourceManager, aMesh, aPlayer, aTexture);
		MyNewScene->LoadContent();
		m_MyScenes.insert(std::pair<Areas, Scene*>(Area_PalletTown, MyNewScene));
	}
	if (myArea == Area_OakLab)
	{
		OakLab* myNewScene = new OakLab(myGame, Area_OakLab, aTileMap, aResourceManager, aMesh, aPlayer, aTexture);
		myNewScene->LoadContent();
		m_MyScenes.insert(std::pair<Areas, Scene*>(Area_OakLab, myNewScene));
	}
	if (myArea == Area_Woods)
	{
		PettleBurgWoods* myNewScene = new PettleBurgWoods(myGame, Area_Woods, aTileMap, aResourceManager, aMesh, aPlayer, aTexture);
		myNewScene->LoadContent();
		m_MyScenes.insert(std::pair<Areas, Scene*>(Area_Woods, myNewScene));
	}
}

void SceneManager::SetActiveScene(Areas aSceneHandle)
{
	for (map<Areas, Scene*>::iterator it = m_MyScenes.begin(); it != m_MyScenes.end(); it++)
	{
		if (it->second->GetIsActive() == true)
		{
			it->second->SetIsActive(false);
		}
	}
	
	m_MyScenes.at(aSceneHandle)->SetIsActive(true);
	m_MyScenes.at(aSceneHandle)->OnIsActive();
}

Scene* SceneManager::GetActiveScene()
{
	for (map<Areas, Scene*>::iterator it = m_MyScenes.begin(); it != m_MyScenes.end(); it++)
	{
		if (it->second->GetIsActive() == true)
		{
			return it->second;
		}
	}
	return nullptr;
}

void SceneManager::OnEvent(Event * anEvent)
{
	DoorEvent* e = (DoorEvent*)anEvent;

	if (e->GetDoorType() == 11)
	{
		SetActiveScene(Area_OakLab);
	}
	if (e->GetDoorType() == 10)
	{
		SetActiveScene(Area_PalletTown);
	}
	if (e->GetDoorType() == 12)
	{
		SetActiveScene(Area_Woods);
	}
	if (e->GetDoorType() == 13)
	{
		SetActiveScene(Area_PalletTown);
	}
}
