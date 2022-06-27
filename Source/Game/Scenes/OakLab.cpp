#include "OakLab.h"

#include "Controllers/AIController.h"
#include "Entities/Entity.h"
#include "Entities/Player.h"
#include "Entities/OakLabObjects/OakLabDeskTop.h"
#include "Entities/OakLabObjects/OakLabLevel.h"
#include "Entities/OakLabObjects/OakLabMachineTop.h"
#include "Entities/OakLabObjects/OakLabPlantTop.h"
#include "Entities/OakLabObjects/OakLabTableTop.h"
#include "Entities/OakLabObjects/ProfessorOak.h"
#include "GameCore/GameCore.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"
#include "Scenes/Scene.h"

#include <fstream>
#include <sstream>

OakLab::OakLab(GameCore* aGameCore, Area anArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Player * aPlayer, unsigned int aTextureIdentifier)
	: Scene(aGameCore, anArea, aTileMap, aResourceManager, aMesh, aPlayer, Vector2Float(7.5f * TileSize, 2.0f * TileSize), aTextureIdentifier)
{
	myOak = nullptr;
	myOakAIController = nullptr;
	myOakLabMap = nullptr;
	myOakLabWorkDesk = nullptr;
	myOakLabMachineTop = nullptr;
	myOakLabPlantTops = nullptr;
	myOakLabTableTop = nullptr;
	myOakStartPosition = Vector2Float(6.0f * TileSize, 11.0f * TileSize);
	myOakMesh = new Mesh();
}

OakLab::~OakLab()
{
	delete myOakLabTableTop;
	delete myOakLabPlantTops;
	delete myOakLabMachineTop;
	delete myOakLabWorkDesk;
	delete myOakLabMap;
	delete myOakAIController;
	delete myOak;
	delete myOakMesh;
}

void OakLab::LoadContent()
{
	std::vector<unsigned int> bitMap;
	std::string csvLine;
	std::fstream input("Data/BitMaps/OakLabBitMap.csv", std::ios::in);
	while (getline(input, csvLine))
	{
		std::istringstream csvStream(csvLine);
		std::string csvElement;
		while (getline(csvStream, csvElement, ','))
			bitMap.push_back(stoi(csvElement));
	}

	myTileMap->SetBitMap(bitMap);

	myOakMesh->SetShaders(myGame->GetShader(), myGame->GetDebugShader());

	myOakLabMap = new OakLabLevel(myResourceManager, myTileMap, myGame, myMesh, myTextureIdentifier);
	myOakLabWorkDesk = new OakLabDeskTop(myResourceManager, myTileMap, myGame, myMesh, myTextureIdentifier);
	myOakLabMachineTop = new OakLabMachineTop(myResourceManager, myTileMap, myGame, myMesh, myTextureIdentifier);
	myOakLabPlantTops = new OakLabPlantTop(myResourceManager, myTileMap, myGame, myMesh, myTextureIdentifier);
	myOakLabTableTop = new OakLabTableTop(myResourceManager, myTileMap, myGame, myMesh, myTextureIdentifier);
	myOak = new ProfessorOak(myResourceManager, myTileMap, myGame, myOakMesh, myResourceManager->GetTexture(TextureHandle::PlayerNPCSprites));
}

void OakLab::Update(float deltatime)
{
	myPlayer->Update(deltatime);
	myOak->Update(deltatime);
}

void OakLab::Draw(Vector2Float camPos, Vector2Float camProjection)
{
	myOakLabMap->Draw(camPos, camProjection);

	myOak->Draw(camPos, camProjection);

	myPlayer->Draw(camPos, camProjection);

	myOakLabWorkDesk->Draw(camPos, camProjection);
	myOakLabMachineTop->Draw(camPos, camProjection);
	myOakLabPlantTops->Draw(camPos, camProjection);
	myOakLabTableTop->Draw(camPos, camProjection);
}

void OakLab::OnIsActive()
{
	myPlayer->SetPosition(myPlayerStartPosition);
	myOak->SetPosition(myOakStartPosition);
	myOak->ResetPathFinder();
}

void OakLab::Reload()
{
}

void OakLab::Unload()
{
	myPlayerStartPosition = Vector2Float(7.5f * TileSize, TileSize + 0.3f);
}
