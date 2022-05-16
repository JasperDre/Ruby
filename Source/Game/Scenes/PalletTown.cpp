#include "GamePCH.h"
#include "PalletTown.h"

#include "Entities/Entity.h"
#include "Entities/Player.h"
#include "Entities/PalletTownObjects/OakHouse.h"
#include "Entities/PalletTownObjects/PalletTownLevel.h"
#include "Entities/PalletTownObjects/PlayerHouse.h"
#include "Entities/PalletTownObjects/RivalHouse.h"
#include "Entities/PalletTownObjects/TownBoy.h"
#include "Entities/PalletTownObjects/TownGirl.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"
#include "Scenes/Scene.h"

PalletTown::PalletTown(GameCore* aGameCore, Areas anArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Player* aPlayer, unsigned int aTextureIdentifier)
	: Scene(aGameCore, anArea, aTileMap, aResourceManager, aMesh, aPlayer, Vector2Float(9.0f * TILESIZE, 20.0f * TILESIZE), aTextureIdentifier)
{
	myPalletTownMap = nullptr;
	myOakHouseTop = nullptr;
	myPlayerHouseTop = nullptr;
	myRivalHouseTop = nullptr;
	myGirlNPC = nullptr;
	myBoyNPC = nullptr;
	myGirlMesh = nullptr;
	myBoyMesh = nullptr;
	myGirlNPCStartPosition = Vector2Float(16.0f * TILESIZE, 9.0f * TILESIZE);
	myBoyNPCStartPosition = Vector2Float(14.0f * TILESIZE, 19.0f * TILESIZE);
	mySavedPlayerPosition = Vector2Float(0.0f, 0.0f);
	mySavedGirlPosition = Vector2Float(0.0f, 0.0f);
	mySavedBoyPosition = Vector2Float(0.0f, 0.0f);
}

PalletTown::~PalletTown()
{
	delete myBoyMesh;
	delete myGirlMesh;
	delete myBoyNPC;
	delete myGirlNPC;
	delete myRivalHouseTop;
	delete myPlayerHouseTop;
	delete myOakHouseTop;
	delete myPalletTownMap;
}

void PalletTown::LoadContent()
{
	myGirlMesh = new Mesh();
	myGirlMesh->SetShader(myGame->GetShader(), myGame->GetDebugShader());
	myBoyMesh = new Mesh();
	myBoyMesh->SetShader(myGame->GetShader(), myGame->GetDebugShader());

	myPalletTownMap = new PalletTownLevel(myResourceManager, myTileMap, myGame, myMesh, myTextureIdentifier);
	myOakHouseTop = new OakHouse(myResourceManager, myTileMap, myGame, myMesh, myTextureIdentifier);
	myPlayerHouseTop = new PlayerHouse(myResourceManager, myTileMap, myGame, myMesh, myTextureIdentifier);
	myRivalHouseTop = new RivalHouse(myResourceManager, myTileMap, myGame, myMesh, myTextureIdentifier);
	myGirlNPC = new TownGirl(myResourceManager, myTileMap, myGame, myGirlMesh, myResourceManager->GetaTexture(TextureHandle::Player_NPCSprites));
	myBoyNPC = new TownBoy(myResourceManager, myTileMap, myGame, myBoyMesh, myResourceManager->GetaTexture(TextureHandle::Player_NPCSprites));
}

void PalletTown::Update(float deltatime)
{
	myPlayer->Update(deltatime);
	myGirlNPC->Update(deltatime);
	myBoyNPC->Update(deltatime);
}

void PalletTown::Draw(Vector2Float camPos, Vector2Float camProjection)
{
	myPalletTownMap->Draw(camPos, camProjection);

	myGirlNPC->Draw(camPos, camProjection);
	myBoyNPC->Draw(camPos, camProjection);

	myPlayer->Draw(camPos, camProjection);

	myOakHouseTop->Draw(camPos, camProjection);
	myPlayerHouseTop->Draw(camPos, camProjection);
	myRivalHouseTop->Draw(camPos, camProjection);
}

void PalletTown::OnIsActive()
{
	if (mySavedPlayerPosition != Vector2Float(0.0f))
	{
		myPlayerStartPosition = mySavedPlayerPosition;
		myGirlNPCStartPosition = mySavedGirlPosition;
		myBoyNPCStartPosition = mySavedBoyPosition;
	}

	myPlayer->SetPosition(myPlayerStartPosition);

	myGirlNPC->SetPosition(myGirlNPCStartPosition);
	myBoyNPC->SetPosition(myBoyNPCStartPosition);

	myGirlNPC->ResetPathFinder();
	myBoyNPC->ResetPathFinder();
}

void PalletTown::Unload()
{
	mySavedPlayerPosition = myPlayer->GetPosition();
	mySavedGirlPosition = myGirlNPC->GetPosition();
	mySavedBoyPosition = myBoyNPC->GetPosition();
}
