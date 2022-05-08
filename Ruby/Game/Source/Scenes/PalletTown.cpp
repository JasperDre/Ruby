#include "GamePCH.h"

#include "Scenes/Scene.h"
#include "PalletTown.h"

#include "GameplayHelpers/TileMap.h"
#include "GameplayHelpers/TileMapPalletTown.h"
#include "GameplayHelpers/ResourceManager.h"

#include "Mesh/Mesh.h"
#include "Mesh/Canvas.h"

#include "GameObjects/GameObject.h"
#include "GameObjects/PalletTownObjects/PalletTownMap.h"
#include "GameObjects/PalletTownObjects/OakHouse.h"
#include "GameObjects/PalletTownObjects/PlayerHouse.h"
#include "GameObjects/PalletTownObjects/RivalHouse.h"
#include "GameObjects/Trainer.h"
#include "GameObjects/PalletTownObjects/TownBoy.h"
#include "GameObjects/PalletTownObjects/TownGirl.h"


PalletTown::PalletTown(GameCore * myGame, Areas myArea, TileMap* aTileMap, ResourceManager * aResourceManager, Mesh* aMesh, Trainer* aPlayer, GLuint aTexture) : Scene(myGame, myArea, aTileMap, aResourceManager, aMesh, aPlayer, aTexture)
{
	m_MyTileMap = aTileMap;
	m_MyTrainer = aPlayer;
	m_PalletTownMap = 0;
	m_OakHouseTop = 0;
	m_PlayerHouseTop = 0;
	m_RivalHouseTop = 0;
	m_GirlNPC = 0;
	m_BoyNPC = 0;
	m_MyGirlMesh = 0;
	m_MyBoyMesh = 0;
	m_pMyPlayerStart = vec2(9.0f * TILESIZE, 20.0f * TILESIZE);

	m_GirlNPCStart = vec2(16.0f * TILESIZE, 9.0f * TILESIZE);
	m_BoyNPCStart = vec2(14.0f * TILESIZE, 19.0f * TILESIZE);


	PlayerSavedPosition = vec2(0.0f, 0.0f);
	GirlSavedPosition = vec2(0.0f, 0.0f);
	BoySavedPosition = vec2(0.0f, 0.0f);

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

	m_MyTrainer = nullptr;
}

void PalletTown::LoadContent()
{
	//Create our Meshes
	m_MyGirlMesh = new Mesh();
	m_MyGirlMesh->SetShader(m_pMyGame->GetShader(), m_pMyGame->GetDebugShader());
	m_MyBoyMesh = new Mesh();
	m_MyBoyMesh->SetShader(m_pMyGame->GetShader(), m_pMyGame->GetDebugShader());

	//Create our game objects
	m_PalletTownMap = new PalletTownMap(m_pMyResourceManager, m_MyTileMap, m_pMyGame, m_pMyMesh, m_pMyTexture);
	m_OakHouseTop = new OakHouse(m_pMyResourceManager, m_MyTileMap, m_pMyGame, m_pMyMesh, m_pMyTexture);
	m_PlayerHouseTop = new PlayerHouse(m_pMyResourceManager, m_MyTileMap, m_pMyGame, m_pMyMesh, m_pMyTexture);
	m_RivalHouseTop = new RivalHouse(m_pMyResourceManager, m_MyTileMap, m_pMyGame, m_pMyMesh, m_pMyTexture);

	m_GirlNPC = new TownGirl(m_pMyResourceManager, m_MyTileMap, m_pMyGame, m_MyGirlMesh, m_pMyResourceManager->GetaTexture(Player_NPCSprites));
	m_BoyNPC = new TownBoy(m_pMyResourceManager, m_MyTileMap, m_pMyGame, m_MyBoyMesh, m_pMyResourceManager->GetaTexture(Player_NPCSprites));
}

void PalletTown::Update(float deltatime)
{
	m_MyTrainer->Update(deltatime);
	m_GirlNPC->Update(deltatime);
	m_BoyNPC->Update(deltatime);
}

void PalletTown::Draw(vec2 camPos, vec2 camProjection)
{
	//Draw our GameObjects
	m_PalletTownMap->Draw(camPos, camProjection);

	m_GirlNPC->Draw(camPos, camProjection);
	m_BoyNPC->Draw(camPos, camProjection);

	m_MyTrainer->Draw(camPos, camProjection);

	m_OakHouseTop->Draw(camPos, camProjection);
	m_PlayerHouseTop->Draw(camPos, camProjection);
	m_RivalHouseTop->Draw(camPos, camProjection);
}

TileMap* PalletTown::GetMyTileMap()
{
	return m_MyTileMap;
}

void PalletTown::OnIsActive()
{
	if (PlayerSavedPosition != vec2(0.0f, 0.0f))
	{
		m_pMyPlayerStart = PlayerSavedPosition;
		m_GirlNPCStart = GirlSavedPosition;
		m_BoyNPCStart = BoySavedPosition;
	}
	m_MyTrainer->SetPosition(m_pMyPlayerStart);

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
	PlayerSavedPosition = m_MyTrainer->GetPosition();
	GirlSavedPosition = m_GirlNPC->GetPosition();
	BoySavedPosition = m_BoyNPC->GetPosition();
}
