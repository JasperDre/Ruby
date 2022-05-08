#include "GamePCH.h"
#include "RivalHouse.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

RivalHouse::RivalHouse(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture) : GameObject(myGame, myMesh, aTexture)
{
	m_pMesh = myMesh;
	m_pMyTexture = aTexture;
	m_MyResourceManager = myResourceManager;
	m_MyTileMap = myTileMap;

	m_RivalHousePosition = vec2(18.0f * TILESIZE, 24.0f * TILESIZE);

	for (int i = 0; i < RivalHouse_NumTiles; i++)
	{

		TileInfo atile = m_MyTileMap->GetTileFromPalletMap(Trainer_House_);

		Frame aframe = atile.MyVariant.at(RivalHouseMap[i]);

		aframe.myUVOffset = vec2((aframe.myOrigin.x / m_MyResourceManager->GetTextureSize(0).x), (aframe.myOrigin.y / m_MyResourceManager->GetTextureSize(0).y));
		aframe.myUVScale = vec2((aframe.mySize.x / m_MyResourceManager->GetTextureSize(0).x), (aframe.mySize.y / m_MyResourceManager->GetTextureSize(0).y));

		aframe.myWorldSpace = vec2((((i % RivalHouse_NumTiles) * TILESIZE) + m_RivalHousePosition.x), (((i / RivalHouse_NumTiles)* TILESIZE) + m_RivalHousePosition.y));

		m_MyFrames.push_back(aframe);
	}
}

RivalHouse::~RivalHouse()
{
	m_MyFrames.clear();
}

void RivalHouse::Update(float deltatime)
{

}

void RivalHouse::Draw(vec2 camPos, vec2 projecScale)
{
	for (int i = 0; i < RivalHouse_NumTiles; i++)
	{
		m_pMesh->Draw(m_MyFrames.at(i).myWorldSpace, m_Angle, vec2(TILESIZE, TILESIZE), camPos, projecScale, m_pMyTexture, m_MyFrames.at(i).myUVScale, m_MyFrames.at(i).myUVOffset);
	}
}
