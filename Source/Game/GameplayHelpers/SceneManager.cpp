#include "GameplayHelpers/SceneManager.h"

#include "Events/DoorEvent.h"
#include "Scenes/OakLab.h"
#include "Scenes/PalletTown.h"
#include "Scenes/PetalburgWoods.h"
#include "Scenes/Scene.h"

SceneManager::SceneManager()
	: mySavedPlayerPosition(0.0f)
{}

SceneManager::~SceneManager()
{
	delete myScenes.at(Area::PalletTown);
	delete myScenes.at(Area::OakLab);
	delete myScenes.at(Area::Woods);
}

void SceneManager::GenerateScenes(GameCore* aGameCore, Area anArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Player* aPlayer, unsigned int aTextureIdentifier)
{
	switch (anArea)
	{
		case Area::OakLab:
		{
			OakLab* oakLabScene = new OakLab(aGameCore, Area::OakLab, aTileMap, aResourceManager, aMesh, aPlayer, aTextureIdentifier);
			oakLabScene->LoadContent();
			myScenes.insert(std::pair<Area, Scene*>(Area::OakLab, oakLabScene));
			break;
		}
		case Area::PalletTown:
		{
			PalletTown* palletTownScene = new PalletTown(aGameCore, Area::PalletTown, aTileMap, aResourceManager, aMesh, aPlayer, aTextureIdentifier);
			palletTownScene->LoadContent();
			myScenes.insert(std::pair<Area, Scene*>(Area::PalletTown, palletTownScene));
			break;
		}
		case Area::Woods:
		{
			PetalburgWoods* petalburgWoodsScene = new PetalburgWoods(aGameCore, Area::Woods, aTileMap, aResourceManager, aMesh, aPlayer, aTextureIdentifier);
			petalburgWoodsScene->LoadContent();
			myScenes.insert(std::pair<Area, Scene*>(Area::Woods, petalburgWoodsScene));
			break;
		}
		case Area::RivalHouse:
		case Area::TrainerHouse:
		case Area::Null:
			break;
	}
}

void SceneManager::SetActiveScene(Area aSceneHandle) const
{
	for (const auto& scene : myScenes)
	{
		if (scene.second->IsActive())
			scene.second->SetIsActive(false);
	}

	myScenes.at(aSceneHandle)->SetIsActive(true);
	myScenes.at(aSceneHandle)->OnIsActive();
}

Scene* SceneManager::GetActiveScene() const
{
	for (const auto& scene : myScenes)
	{
		if (scene.second->IsActive())
			return scene.second;
	}

	return nullptr;
}

void SceneManager::OnEvent(Event* anEvent) const
{
	const DoorEvent* doorEvent = dynamic_cast<DoorEvent*>(anEvent);

	if (doorEvent->GetDoorType() == 11)
		SetActiveScene(Area::OakLab);

	if (doorEvent->GetDoorType() == 10)
		SetActiveScene(Area::PalletTown);

	if (doorEvent->GetDoorType() == 12)
		SetActiveScene(Area::Woods);

	if (doorEvent->GetDoorType() == 13)
		SetActiveScene(Area::PalletTown);
}
