#include "GamePCH.h"

#include "GameObjects/GameObject.h"
#include "PlayerHouse.h"

#include "Mesh/Mesh.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "GameplayHelpers/TileMapPalletTown.h"

PlayerHouse::PlayerHouse(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture) : GameObject(myGame, myMesh, aTexture)
{
	m_pMesh = myMesh;
	m_pMyTexture = aTexture;
	m_MyResourceManager = myResourceManager;
	m_MyTileMap = myTileMap;

	m_PlayerHousePosition = vec2(8.0f * TILESIZE, 24.0f * TILESIZE);

	for (int i = 0; i < PlayerHouse_NumTiles; i++)
	{

		TileInfo atile = m_MyTileMap->GetTileFromPalletMap(Trainer_House_);

		Frame aframe = atile.MyVariant.at(PlayerHouseMap[i]);

		aframe.uvoffset = vec2((aframe.origin.x / m_MyResourceManager->GetTextureSize(0).x), (aframe.origin.y / m_MyResourceManager->GetTextureSize(0).y));
		aframe.uvscale = vec2((aframe.size.x / m_MyResourceManager->GetTextureSize(0).x), (aframe.size.y / m_MyResourceManager->GetTextureSize(0).y));

		aframe.worldSpace = vec2((((i % PlayerHouse_NumTiles) * TILESIZE) + m_PlayerHousePosition.x), (((i / PlayerHouse_NumTiles)* TILESIZE) + m_PlayerHousePosition.y));

		m_MyFrames.push_back(aframe);
	}
}

PlayerHouse::~PlayerHouse()
{
	m_MyFrames.clear();
}

void PlayerHouse::Update(float deltatime)
{

}

void PlayerHouse::Draw(vec2 camPos, vec2 projecScale)
{
	for (int i = 0; i < PlayerHouse_NumTiles; i++)
	{
		m_pMesh->Draw(m_MyFrames.at(i).worldSpace, m_Angle, vec2(TILESIZE, TILESIZE), camPos, projecScale, m_pMyTexture, m_MyFrames.at(i).uvscale, m_MyFrames.at(i).uvoffset);
	}
}

