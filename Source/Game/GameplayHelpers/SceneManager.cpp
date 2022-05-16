#include "GamePCH.h"
#include "GameplayHelpers/SceneManager.h"

#include "Scenes/OakLab.h"
#include "Scenes/PalletTown.h"
#include "Scenes/PetalburgWoods.h"
#include "Scenes/Scene.h"

SceneManager::SceneManager()
	: mySavedPlayerPosition(0.0f)
{}

SceneManager::~SceneManager()
{
	delete myScenes.at(Areas::Area_PalletTown);
	delete myScenes.at(Areas::Area_OakLab);
	delete myScenes.at(Areas::Area_Woods);
}

void SceneManager::GenerateScenes(GameCore* aGameCore, Areas anArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Player* aPlayer, unsigned int aTextureIdentifier)
{
	switch (anArea)
	{
		case Areas::Area_OakLab:
		{
			OakLab* myNewScene = new OakLab(aGameCore, Areas::Area_OakLab, aTileMap, aResourceManager, aMesh, aPlayer, aTextureIdentifier);
			myNewScene->LoadContent();
			myScenes.insert(std::pair<Areas, Scene*>(Areas::Area_OakLab, myNewScene));
			break;
		}
		case Areas::Area_PalletTown:
		{
			PalletTown* MyNewScene = new PalletTown(aGameCore, Areas::Area_PalletTown, aTileMap, aResourceManager, aMesh, aPlayer, aTextureIdentifier);
			MyNewScene->LoadContent();
			myScenes.insert(std::pair<Areas, Scene*>(Areas::Area_PalletTown, MyNewScene));
			break;
		}
		case Areas::Area_Woods:
		{
			PetalburgWoods* myNewScene = new PetalburgWoods(aGameCore, Areas::Area_Woods, aTileMap, aResourceManager, aMesh, aPlayer, aTextureIdentifier);
			myNewScene->LoadContent();
			myScenes.insert(std::pair<Areas, Scene*>(Areas::Area_Woods, myNewScene));
			break;
		}
		case Areas::Area_RivalHouse:
		case Areas::Area_TrainerHouse:
		case Areas::Area_Null:
			break;
	}
}

void SceneManager::SetActiveScene(Areas aSceneHandle) const
{
	for (const auto& m_MyScene : myScenes)
	{
		if (m_MyScene.second->IsActive())
			m_MyScene.second->SetIsActive(false);
	}

	myScenes.at(aSceneHandle)->SetIsActive(true);
	myScenes.at(aSceneHandle)->OnIsActive();
}

Scene* SceneManager::GetActiveScene() const
{
	for (const auto& m_MyScene : myScenes)
	{
		if (m_MyScene.second->IsActive())
			return m_MyScene.second;
	}

	return nullptr;
}

void SceneManager::OnEvent(Event* anEvent) const
{
	const DoorEvent* doorEvent = dynamic_cast<DoorEvent*>(anEvent);

	if (doorEvent->GetDoorType() == 11)
		SetActiveScene(Areas::Area_OakLab);

	if (doorEvent->GetDoorType() == 10)
		SetActiveScene(Areas::Area_PalletTown);

	if (doorEvent->GetDoorType() == 12)
		SetActiveScene(Areas::Area_Woods);

	if (doorEvent->GetDoorType() == 13)
		SetActiveScene(Areas::Area_PalletTown);
}
