#include "GamePCH.h"
#include "PlayerHouse.h"

#include "GameObjects/GameObject.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

PlayerHouse::PlayerHouse(ResourceManager* aResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture)
	: GameObject(myGame, myMesh, aTexture)
{
	m_pMesh = myMesh;
	m_pMyTexture = aTexture;
	m_MyResourceManager = aResourceManager;
	m_MyTileMap = myTileMap;

	m_PlayerHousePosition = vec2(8.0f * TILESIZE, 24.0f * TILESIZE);

	for (int i = 0; i < PlayerHouse_NumTiles; i++)
	{

		TileInfo atile = m_MyTileMap->GetTileFromPalletMap(Trainer_House_);

		Frame aframe = atile.MyVariant.at(PlayerHouseMap[i]);

		aframe.myUVOffset = vec2((aframe.myOrigin.x / m_MyResourceManager->GetTextureSize(0).x), (aframe.myOrigin.y / m_MyResourceManager->GetTextureSize(0).y));
		aframe.myUVScale = vec2((aframe.mySize.x / m_MyResourceManager->GetTextureSize(0).x), (aframe.mySize.y / m_MyResourceManager->GetTextureSize(0).y));

		aframe.myWorldSpace = vec2((((i % PlayerHouse_NumTiles) * TILESIZE) + m_PlayerHousePosition.x), (((i / PlayerHouse_NumTiles)* TILESIZE) + m_PlayerHousePosition.y));

		m_MyFrames.push_back(aframe);
	}
}

PlayerHouse::~PlayerHouse()
{
	m_MyFrames.clear();
}

void PlayerHouse::Draw(vec2 camPos, vec2 projecScale)
{
	for (int i = 0; i < PlayerHouse_NumTiles; i++)
	{
		m_pMesh->Draw(m_MyFrames.at(i).myWorldSpace, m_Angle, vec2(TILESIZE, TILESIZE), camPos, projecScale, m_pMyTexture, m_MyFrames.at(i).myUVScale, m_MyFrames.at(i).myUVOffset);
	}
}

