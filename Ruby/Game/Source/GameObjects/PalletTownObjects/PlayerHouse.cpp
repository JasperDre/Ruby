#include "GamePCH.h"
#include "PlayerHouse.h"

#include "GameObjects/Entity.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

PlayerHouse::PlayerHouse(ResourceManager* aResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture)
	: Entity(myGame, myMesh, aTexture)
{
	m_pMesh = myMesh;
	myTextureIdentifier = aTexture;
	m_MyResourceManager = aResourceManager;
	m_MyTileMap = myTileMap;

	m_PlayerHousePosition = Vector2Float(8.0f * TILESIZE, 24.0f * TILESIZE);

	for (int i = 0; i < PlayerHouse_NumTiles; i++)
	{

		TileInfo atile = m_MyTileMap->GetTileFromPalletMap(Trainer_House_);

		Frame aframe = atile.MyVariant.at(PlayerHouseMap[i]);

		aframe.myUVOffset = Vector2Float((aframe.myOrigin.myX / m_MyResourceManager->GetTextureSize(0).x), (aframe.myOrigin.myY / m_MyResourceManager->GetTextureSize(0).y));
		aframe.myUVScale = Vector2Float((aframe.mySize.myX / m_MyResourceManager->GetTextureSize(0).x), (aframe.mySize.myY / m_MyResourceManager->GetTextureSize(0).y));

		aframe.myWorldSpace = Vector2Float((((i % PlayerHouse_NumTiles) * TILESIZE) + m_PlayerHousePosition.myX), (((i / PlayerHouse_NumTiles)* TILESIZE) + m_PlayerHousePosition.myY));

		m_MyFrames.push_back(aframe);
	}
}

PlayerHouse::~PlayerHouse()
{
	m_MyFrames.clear();
}

void PlayerHouse::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	for (int i = 0; i < PlayerHouse_NumTiles; i++)
	{
		m_pMesh->Draw(m_MyFrames.at(i).myWorldSpace, m_Angle, Vector2Float(TILESIZE, TILESIZE), camPos, projecScale, myTextureIdentifier, m_MyFrames.at(i).myUVScale, m_MyFrames.at(i).myUVOffset);
	}
}

