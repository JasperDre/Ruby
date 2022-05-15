#include "GamePCH.h"
#include "PetalburgWoods.h"

#include "Entities/Entity.h"
#include "Entities/Player.h"
#include "Entities/WoodsObjects/PetalburgWoodsLevel.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

PetalburgWoods::PetalburgWoods(GameCore* myGame, Areas myArea, TileMap* aTileMap, ResourceManager * aResourceManager, Mesh* aMesh, Player* aPlayer, GLuint aTexture)
	: Scene(myGame, myArea, aTileMap, aResourceManager, aMesh, aPlayer, Vector2Float(37.0f * TILESIZE, TILESIZE), aTexture)
	, m_MyPetalburg(nullptr)
{
	PlayerSavedPosition = Vector2Float(0.0f, 0.0f);
}

PetalburgWoods::~PetalburgWoods()
{
	delete m_MyPetalburg;
}

void PetalburgWoods::LoadContent()
{
	m_MyPetalburg = new PetalburgWoodsLevel(m_pMyResourceManager, m_MyTileMap, m_pMyGame, m_pMyMesh, m_pMyTexture);
}

void PetalburgWoods::Update(float deltatime)
{
	m_pMyTrainer->Update(deltatime);
}

void PetalburgWoods::Draw(Vector2Float camPos, Vector2Float camProjection)
{
	m_MyPetalburg->Draw(camPos, camProjection);
	m_pMyTrainer->Draw(camPos, camProjection);
}

void PetalburgWoods::OnIsActive()
{
	if (PlayerSavedPosition != Vector2Float(0.0f, 0.0f))
	{
		m_pMyPlayerStart = PlayerSavedPosition;
	}

	m_pMyTrainer->SetPosition(m_pMyPlayerStart);
}

void PetalburgWoods::Reload()
{

}

void PetalburgWoods::Unload()
{
	PlayerSavedPosition = m_pMyTrainer->GetPosition();
}
