#include "GamePCH.h"

#include "Scenes/Scene.h"
#include "PetalBergWoods.h"

#include "GameplayHelpers/TileMap.h"
#include "GameplayHelpers/ResourceManager.h"

#include "Mesh/Mesh.h"
#include "Mesh/Canvas.h"

#include "GameObjects/GameObject.h"
#include "GameObjects/Trainer.h"
#include "GameObjects/WoodsObjects/PettleburgWoodsMap.h"

PettleBurgWoods::PettleBurgWoods(GameCore * myGame, Areas myArea, TileMap * aTileMap, ResourceManager * aResourceManager, Mesh * aMesh, Trainer * aPlayer, GLuint aTexture) : Scene(myGame, myArea, aTileMap, aResourceManager, aMesh, aPlayer, aTexture)
{
	m_MyTileMap = aTileMap;
	m_MyTrainer = aPlayer;
	m_MyPettleburgWoods = 0;

	m_pMyPlayerStart = vec2(37.0f * TILESIZE, TILESIZE);

	PlayerSavedPosition = vec2(0.0f, 0.0f);
}

PettleBurgWoods::~PettleBurgWoods()
{
	delete m_MyPettleburgWoods;
	m_MyPettleburgWoods = nullptr;

	m_MyTrainer = nullptr;
	m_MyTileMap = nullptr;
}

void PettleBurgWoods::LoadContent()
{
	m_MyPettleburgWoods = new PettleburgWoodsMap(m_pMyResourceManager, m_MyTileMap, m_pMyGame, m_pMyMesh, m_pMyTexture);
}

void PettleBurgWoods::Update(float deltatime)
{
	m_MyTrainer->Update(deltatime);
}

void PettleBurgWoods::Draw(vec2 camPos, vec2 camProjection)
{
	m_MyPettleburgWoods->Draw(camPos, camProjection);
	m_MyTrainer->Draw(camPos, camProjection);
}

TileMap* PettleBurgWoods::GetMyTileMap()
{
	return m_MyTileMap;
}

void PettleBurgWoods::OnIsActive()
{
	if (PlayerSavedPosition != vec2(0.0f, 0.0f))
	{
		m_pMyPlayerStart = PlayerSavedPosition;
	}

	m_MyTrainer->SetPosition(m_pMyPlayerStart);
}

void PettleBurgWoods::Reload()
{

}

void PettleBurgWoods::Unload()
{
	PlayerSavedPosition = m_MyTrainer->GetPosition();
}
