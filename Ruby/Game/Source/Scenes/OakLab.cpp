#include "GamePCH.h"
#include "OakLab.h"

#include "Controllers/AIController.h"
#include "Entities/Entity.h"
#include "Entities/Trainer.h"
#include "Entities/OakLabObjects/OakLabDeskTop.h"
#include "Entities/OakLabObjects/OakLabMachineTop.h"
#include "Entities/OakLabObjects/OakLabMap.h"
#include "Entities/OakLabObjects/OakLabPlantTop.h"
#include "Entities/OakLabObjects/OakLabTableTop.h"
#include "Entities/OakLabObjects/ProfessorOak.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"
#include "Scenes/Scene.h"

OakLab::OakLab(GameCore* myGame, Areas myArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Trainer * aPlayer, GLuint aTexture)
	: Scene(myGame, myArea, aTileMap, aResourceManager, aMesh, aPlayer, Vector2Float(7.5f * TILESIZE, 2.0f * TILESIZE), aTexture)
{
	m_ProfOakMesh = nullptr;
	m_ProfOak = nullptr;
	m_OakAIController = nullptr;
	m_OakLabMap = nullptr;
	m_OakLabWorkDesk = nullptr;
	m_OakLabMachineTop = nullptr;
	m_OakLabPlantTops = nullptr;
	m_OakLabTableTop = nullptr;
	m_OakStartPosition = Vector2Float(6.0f * TILESIZE, 11.0f * TILESIZE);
}

OakLab::~OakLab()
{
	delete m_OakAIController;
	delete m_ProfOak;
	delete m_OakLabMap;
	delete m_OakLabWorkDesk;
	delete m_OakLabMachineTop;
	delete m_OakLabPlantTops;
	delete m_OakLabTableTop;
	delete m_ProfOakMesh;
}

void OakLab::LoadContent()
{
	m_ProfOakMesh = new Mesh();
	m_ProfOakMesh->SetShader(m_pMyGame->GetShader(), m_pMyGame->GetDebugShader());

	m_OakLabMap = new OakLabMap(m_pMyResourceManager, m_MyTileMap, m_pMyGame, m_pMyMesh, m_pMyTexture);
	m_OakLabWorkDesk = new OakLabDeskTop(m_pMyResourceManager, m_MyTileMap, m_pMyGame, m_pMyMesh, m_pMyTexture);
	m_OakLabMachineTop = new OakLabMachineTop(m_pMyResourceManager, m_MyTileMap, m_pMyGame, m_pMyMesh, m_pMyTexture);
	m_OakLabPlantTops = new OakLabPlantTop(m_pMyResourceManager, m_MyTileMap, m_pMyGame, m_pMyMesh, m_pMyTexture);
	m_OakLabTableTop = new OakLabTableTop(m_pMyResourceManager, m_MyTileMap, m_pMyGame, m_pMyMesh, m_pMyTexture);
	m_ProfOak = new ProfessorOak(m_pMyResourceManager, m_MyTileMap, m_pMyGame, m_ProfOakMesh, m_pMyResourceManager->GetaTexture(TextureHandle::Player_NPCSprites));
}

void OakLab::Update(float deltatime)
{
	m_pMyTrainer->Update(deltatime);
	m_ProfOak->Update(deltatime);
}

void OakLab::Draw(Vector2Float camPos, Vector2Float camProjection)
{
	m_OakLabMap->Draw(camPos, camProjection);

	m_ProfOak->Draw(camPos, camProjection);

	m_pMyTrainer->Draw(camPos, camProjection);

	m_OakLabWorkDesk->Draw(camPos, camProjection);
	m_OakLabMachineTop->Draw(camPos, camProjection);
	m_OakLabPlantTops->Draw(camPos, camProjection);
	m_OakLabTableTop->Draw(camPos, camProjection);
}

void OakLab::OnIsActive()
{
	m_pMyTrainer->SetPosition(m_pMyPlayerStart);
	m_ProfOak->SetPosition(m_OakStartPosition);
	m_ProfOak->ResetPathFinder();
}

void OakLab::Reload()
{
}

void OakLab::Unload()
{
	m_pMyPlayerStart = Vector2Float(7.5f * TILESIZE, TILESIZE + 0.3f);
}
