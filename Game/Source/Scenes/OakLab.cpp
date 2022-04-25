#include "GamePCH.h"

#include "Scenes/Scene.h"
#include "OakLab.h"

#include "GameplayHelpers/TileMap.h"
#include "GameplayHelpers/TileMapOakLab.h"
#include "GameplayHelpers/ResourceManager.h"

#include "Mesh/Mesh.h"
#include "Mesh/Canvas.h"

#include "GameObjects/GameObject.h"
#include "GameObjects/Trainer.h"
#include "GameObjects/OakLabObjects/ProfessorOak.h"
#include "GameObjects/OakLabObjects/OakLabMap.h"
#include "GameObjects/OakLabObjects/OakLabDeskTop.h"
#include "GameObjects/OakLabObjects/OakLabMachineTop.h"
#include "GameObjects/OakLabObjects/OakLabPlantTop.h"
#include "GameObjects/OakLabObjects/OakLabTableTop.h"

#include "Controllers/AIController.h"


OakLab::OakLab(GameCore * myGame, Areas myArea, TileMap * aTileMap, ResourceManager * aResourceManager, Mesh * aMesh, Trainer * aPlayer, GLuint aTexture): Scene(myGame, myArea, aTileMap, aResourceManager, aMesh, aPlayer, aTexture)
{
	m_ProfOakMesh = 0;

	m_MyTileMap = aTileMap;
	m_MyTrainer = aPlayer;

	m_ProfOak = 0;
	m_OakAIController = 0;

	m_OakLabMap = 0;
	m_OakLabWorkDesk = 0;
	m_OakLabMachineTop = 0;
	m_OakLabPlantTops = 0;
	m_OakLabTableTop = 0;

	m_pMyPlayerStart = vec2(7.5f * TILESIZE, 2.0f * TILESIZE);
	m_OakStartPosition = vec2(6.0f * TILESIZE, 11.0f * TILESIZE);
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

	m_ProfOak = new ProfessorOak(m_pMyResourceManager, m_MyTileMap, m_pMyGame, m_ProfOakMesh, m_pMyResourceManager->GetaTexture(Player_NPCSprites));

}

void OakLab::Update(float deltatime)
{
	m_MyTrainer->Update(deltatime);
	m_ProfOak->Update(deltatime);
}

void OakLab::Draw(vec2 camPos, vec2 camProjection)
{
	m_OakLabMap->Draw(camPos, camProjection);

	m_ProfOak->Draw(camPos, camProjection);

	m_MyTrainer->Draw(camPos, camProjection);

	m_OakLabWorkDesk->Draw(camPos, camProjection);
	m_OakLabMachineTop->Draw(camPos, camProjection);
	m_OakLabPlantTops->Draw(camPos, camProjection);
	m_OakLabTableTop->Draw(camPos, camProjection);
}

TileMap* OakLab::GetMyTileMap()
{
	return m_MyTileMap;
}

void OakLab::OnIsActive()
{
	m_MyTrainer->SetPosition(m_pMyPlayerStart);
	m_ProfOak->SetPosition(m_OakStartPosition);
	m_ProfOak->ResetPathFinder();
}

void OakLab::Reload()
{
}

void OakLab::Unload()
{
	m_pMyPlayerStart = vec2(7.5f * TILESIZE, TILESIZE + 0.3f);
}
