#include "PetalburgWoods.h"

#include "Entities/Entity.h"
#include "Entities/Player.h"
#include "Entities/WoodsObjects/PetalburgWoodsLevel.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

#include <fstream>
#include <sstream>

PetalburgWoods::PetalburgWoods(GameCore* aGameCore, Area anArea, TileMap* aTileMap, ResourceManager * aResourceManager, Mesh* aMesh, Player* aPlayer, unsigned int aTextureIdentifier)
	: Scene(aGameCore, anArea, aTileMap, aResourceManager, aMesh, aPlayer, Vector2Float(37.0f * TileSize, TileSize), aTextureIdentifier)
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
	std::vector<unsigned int> bitMap;
	std::string csvLine;
	std::fstream input("Data/BitMaps/Route1BitMap.csv", std::ios::in);
	while (getline(input, csvLine))
	{
		std::istringstream csvStream(csvLine);
		std::string csvElement;
		while (getline(csvStream, csvElement, ','))
			bitMap.push_back(stoi(csvElement));
	}

	myTileMap->SetBitMap(bitMap);

	m_MyPetalburg = new PetalburgWoodsLevel(myResourceManager, myTileMap, myGame, myMesh, myTextureIdentifier);
}

void PetalburgWoods::Update(float deltatime)
{
	myPlayer->Update(deltatime);
}

void PetalburgWoods::Draw(Vector2Float camPos, Vector2Float camProjection)
{
	m_MyPetalburg->Draw(camPos, camProjection);
	myPlayer->Draw(camPos, camProjection);
}

void PetalburgWoods::OnIsActive()
{
	if (PlayerSavedPosition != Vector2Float(0.0f, 0.0f))
		myPlayerStartPosition = PlayerSavedPosition;

	myPlayer->SetPosition(myPlayerStartPosition);
}

void PetalburgWoods::Unload()
{
	PlayerSavedPosition = myPlayer->GetPosition();
}
