#include "GamePCH.h"
#include "GameplayHelpers/SceneManager.h"

#include "Scenes/OakLab.h"
#include "Scenes/PalletTown.h"
#include "Scenes/PetalburgWoods.h"
#include "Scenes/Scene.h"

SceneManager::SceneManager()
	: m_PlayerSavedPosition(0.0f)
{}

SceneManager::~SceneManager()
{
	delete m_MyScenes.at(Areas::Area_PalletTown);
	delete m_MyScenes.at(Areas::Area_OakLab);
	delete m_MyScenes.at(Areas::Area_Woods);
}

void SceneManager::GenerateScenes(GameCore* myGame, Areas myArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Player* aPlayer, GLuint aTexture)
{
	switch (myArea)
	{
		case Areas::Area_OakLab:
		{
			OakLab* myNewScene = new OakLab(myGame, Areas::Area_OakLab, aTileMap, aResourceManager, aMesh, aPlayer, aTexture);
			myNewScene->LoadContent();
			m_MyScenes.insert(std::pair<Areas, Scene*>(Areas::Area_OakLab, myNewScene));
			break;
		}
		case Areas::Area_PalletTown:
		{
			PalletTown* MyNewScene = new PalletTown(myGame, Areas::Area_PalletTown, aTileMap, aResourceManager, aMesh, aPlayer, aTexture);
			MyNewScene->LoadContent();
			m_MyScenes.insert(std::pair<Areas, Scene*>(Areas::Area_PalletTown, MyNewScene));
			break;
		}
		case Areas::Area_Woods:
		{
			PetalburgWoods* myNewScene = new PetalburgWoods(myGame, Areas::Area_Woods, aTileMap, aResourceManager, aMesh, aPlayer, aTexture);
			myNewScene->LoadContent();
			m_MyScenes.insert(std::pair<Areas, Scene*>(Areas::Area_Woods, myNewScene));
			break;
		}
		case Areas::Area_RivalHouse:
		case Areas::Area_TrainerHouse:
		case Areas::Area_Null:
			break;
	}
}

void SceneManager::SetActiveScene(Areas aSceneHandle)
{
	for (std::map<Areas, Scene*>::iterator it = m_MyScenes.begin(); it != m_MyScenes.end(); ++it)
	{
		if (it->second->GetIsActive())
		{
			it->second->SetIsActive(false);
		}
	}

	m_MyScenes.at(aSceneHandle)->SetIsActive(true);
	m_MyScenes.at(aSceneHandle)->OnIsActive();
}

Scene* SceneManager::GetActiveScene()
{
	for (std::map<Areas, Scene*>::iterator it = m_MyScenes.begin(); it != m_MyScenes.end(); ++it)
	{
		if (it->second->GetIsActive())
			return it->second;
	}

	return nullptr;
}

void SceneManager::OnEvent(Event* anEvent)
{
	const DoorEvent* doorEvent = dynamic_cast<DoorEvent*>(anEvent);

	if (doorEvent->GetDoorType() == 11)
	{
		SetActiveScene(Areas::Area_OakLab);
	}
	if (doorEvent->GetDoorType() == 10)
	{
		SetActiveScene(Areas::Area_PalletTown);
	}
	if (doorEvent->GetDoorType() == 12)
	{
		SetActiveScene(Areas::Area_Woods);
	}
	if (doorEvent->GetDoorType() == 13)
	{
		SetActiveScene(Areas::Area_PalletTown);
	}
}