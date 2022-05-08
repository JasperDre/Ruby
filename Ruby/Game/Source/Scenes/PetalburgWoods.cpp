#include "GamePCH.h"
#include "PetalburgWoods.h"

#include "GameObjects/GameObject.h"
#include "GameObjects/Trainer.h"
#include "GameObjects/WoodsObjects/PetalburgWoodsMap.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

PetalburgWoods::PetalburgWoods(GameCore * myGame, Areas myArea, TileMap * aTileMap, ResourceManager * aResourceManager, Mesh * aMesh, Trainer * aPlayer, GLuint aTexture) : Scene(myGame, myArea, aTileMap, aResourceManager, aMesh, aPlayer, aTexture)
{
	m_MyTileMap = aTileMap;
	m_MyTrainer = aPlayer;
	m_MyPetalburg = 0;

	m_pMyPlayerStart = vec2(37.0f * TILESIZE, TILESIZE);

	PlayerSavedPosition = vec2(0.0f, 0.0f);
}

PetalburgWoods::~PetalburgWoods()
{
	delete m_MyPetalburg;
	m_MyPetalburg = nullptr;

	m_MyTrainer = nullptr;
	m_MyTileMap = nullptr;
}

void PetalburgWoods::LoadContent()
{
	m_MyPetalburg = new PetalburgWoodsMap(m_pMyResourceManager, m_MyTileMap, m_pMyGame, m_pMyMesh, m_pMyTexture);
}

void PetalburgWoods::Update(float deltatime)
{
	m_MyTrainer->Update(deltatime);
}

void PetalburgWoods::Draw(vec2 camPos, vec2 camProjection)
{
	m_MyPetalburg->Draw(camPos, camProjection);
	m_MyTrainer->Draw(camPos, camProjection);
}

TileMap* PetalburgWoods::GetMyTileMap()
{
	return m_MyTileMap;
}

void PetalburgWoods::OnIsActive()
{
	if (PlayerSavedPosition != vec2(0.0f, 0.0f))
	{
		m_pMyPlayerStart = PlayerSavedPosition;
	}

	m_MyTrainer->SetPosition(m_pMyPlayerStart);
}

void PetalburgWoods::Reload()
{

}

void PetalburgWoods::Unload()
{
	PlayerSavedPosition = m_MyTrainer->GetPosition();
}
