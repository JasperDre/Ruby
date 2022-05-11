#include "GamePCH.h"
#include "PalletTown.h"

#include "Entities/Entity.h"
#include "Entities/Trainer.h"
#include "Entities/PalletTownObjects/OakHouse.h"
#include "Entities/PalletTownObjects/PalletTownMap.h"
#include "Entities/PalletTownObjects/PlayerHouse.h"
#include "Entities/PalletTownObjects/RivalHouse.h"
#include "Entities/PalletTownObjects/TownBoy.h"
#include "Entities/PalletTownObjects/TownGirl.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"
#include "Scenes/Scene.h"

PalletTown::PalletTown(GameCore* myGame, Areas myArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Trainer* aPlayer, GLuint aTexture)
	: Scene(myGame, myArea, aTileMap, aResourceManager, aMesh, aPlayer, Vector2Float(9.0f * TILESIZE, 20.0f * TILESIZE), aTexture)
{
	m_PalletTownMap = nullptr;
	m_OakHouseTop = nullptr;
	m_PlayerHouseTop = nullptr;
	m_RivalHouseTop = nullptr;
	m_GirlNPC = nullptr;
	m_BoyNPC = nullptr;
	m_MyGirlMesh = nullptr;
	m_MyBoyMesh = nullptr;
	m_GirlNPCStart = Vector2Float(16.0f * TILESIZE, 9.0f * TILESIZE);
	m_BoyNPCStart = Vector2Float(14.0f * TILESIZE, 19.0f * TILESIZE);
	PlayerSavedPosition = Vector2Float(0.0f, 0.0f);
	GirlSavedPosition = Vector2Float(0.0f, 0.0f);
	BoySavedPosition = Vector2Float(0.0f, 0.0f);
}

PalletTown::~PalletTown()
{
	delete m_RivalHouseTop;
	m_RivalHouseTop = nullptr;
	delete m_OakHouseTop;
	m_OakHouseTop = nullptr;
	delete m_PlayerHouseTop;
	m_PlayerHouseTop = nullptr;
	delete m_PalletTownMap;
	m_PalletTownMap = nullptr;
	delete m_GirlNPC;
	m_GirlNPC = nullptr;
	delete m_BoyNPC;
	m_BoyNPC = nullptr;
	delete m_MyGirlMesh;
	m_MyGirlMesh = nullptr;
	delete m_MyBoyMesh;
	m_MyBoyMesh = nullptr;
	m_pMyTrainer = nullptr;
}

void PalletTown::LoadContent()
{
	m_MyGirlMesh = new Mesh();
	m_MyGirlMesh->SetShader(m_pMyGame->GetShader(), m_pMyGame->GetDebugShader());
	m_MyBoyMesh = new Mesh();
	m_MyBoyMesh->SetShader(m_pMyGame->GetShader(), m_pMyGame->GetDebugShader());

	m_PalletTownMap = new PalletTownMap(m_pMyResourceManager, m_MyTileMap, m_pMyGame, m_pMyMesh, m_pMyTexture);
	m_OakHouseTop = new OakHouse(m_pMyResourceManager, m_MyTileMap, m_pMyGame, m_pMyMesh, m_pMyTexture);
	m_PlayerHouseTop = new PlayerHouse(m_pMyResourceManager, m_MyTileMap, m_pMyGame, m_pMyMesh, m_pMyTexture);
	m_RivalHouseTop = new RivalHouse(m_pMyResourceManager, m_MyTileMap, m_pMyGame, m_pMyMesh, m_pMyTexture);
	m_GirlNPC = new TownGirl(m_pMyResourceManager, m_MyTileMap, m_pMyGame, m_MyGirlMesh, m_pMyResourceManager->GetaTexture(TextureHandle::Player_NPCSprites));
	m_BoyNPC = new TownBoy(m_pMyResourceManager, m_MyTileMap, m_pMyGame, m_MyBoyMesh, m_pMyResourceManager->GetaTexture(TextureHandle::Player_NPCSprites));
}

void PalletTown::Update(float deltatime)
{
	m_pMyTrainer->Update(deltatime);
	m_GirlNPC->Update(deltatime);
	m_BoyNPC->Update(deltatime);
}

void PalletTown::Draw(Vector2Float camPos, Vector2Float camProjection)
{
	m_PalletTownMap->Draw(camPos, camProjection);

	m_GirlNPC->Draw(camPos, camProjection);
	m_BoyNPC->Draw(camPos, camProjection);

	m_pMyTrainer->Draw(camPos, camProjection);

	m_OakHouseTop->Draw(camPos, camProjection);
	m_PlayerHouseTop->Draw(camPos, camProjection);
	m_RivalHouseTop->Draw(camPos, camProjection);
}

void PalletTown::OnIsActive()
{
	if (PlayerSavedPosition != Vector2Float(0.0f, 0.0f))
	{
		m_pMyPlayerStart = PlayerSavedPosition;
		m_GirlNPCStart = GirlSavedPosition;
		m_BoyNPCStart = BoySavedPosition;
	}

	m_pMyTrainer->SetPosition(m_pMyPlayerStart);

	m_GirlNPC->SetPosition(m_GirlNPCStart);
	m_BoyNPC->SetPosition(m_BoyNPCStart);

	m_GirlNPC->ResetPathFinder();
	m_BoyNPC->ResetPathFinder();
}

void PalletTown::Reload()
{

}

void PalletTown::Unload()
{
	PlayerSavedPosition = m_pMyTrainer->GetPosition();
	GirlSavedPosition = m_GirlNPC->GetPosition();
	BoySavedPosition = m_BoyNPC->GetPosition();
}
