#include "GamePCH.h"

#include "GameObjects/GameObject.h"
#include "OakHouse.h"

#include "Mesh/Mesh.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "GameplayHelpers/TileMapPalletTown.h"


OakHouse::OakHouse(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture) : GameObject(myGame, myMesh, aTexture)
{
	m_pMesh = myMesh;
	m_pMyTexture = aTexture;
	m_MyResourceManager = myResourceManager;
	m_MyTileMap = myTileMap;
	OakHousePosition = vec2(17.0f * TILESIZE, 18.0f * TILESIZE);

	for (int i = 0; i < OakHouse_NumTiles; i++)
	{

		TileInfo atile = m_MyTileMap->GetTileFromPalletMap(Oak_House_);

		Frame aframe = atile.MyVariant.at(OakHouseMap[i]);

		aframe.uvoffset = vec2((aframe.origin.x / m_MyResourceManager->GetTextureSize(0).x), (aframe.origin.y / m_MyResourceManager->GetTextureSize(0).y));
		aframe.uvscale = vec2((aframe.size.x / m_MyResourceManager->GetTextureSize(0).x), (aframe.size.y / m_MyResourceManager->GetTextureSize(0).y));

		aframe.worldSpace = vec2((((i % OakHouse_NumTiles) * TILESIZE) + OakHousePosition.x), (((i / OakHouse_NumTiles)* TILESIZE) + OakHousePosition.y));

		m_MyFrames.push_back(aframe);
	}
}

OakHouse::~OakHouse()
{
	m_MyFrames.clear();
}

void OakHouse::Update(float deltatime)
{

}

void OakHouse::Draw(vec2 camPos, vec2 projecScale)
{
	for (int i = 0; i < OakHouse_NumTiles; i++)
	{
		m_pMesh->Draw(m_MyFrames.at(i).worldSpace, m_Angle, vec2(TILESIZE, TILESIZE), camPos, projecScale, m_pMyTexture, m_MyFrames.at(i).uvscale, m_MyFrames.at(i).uvoffset);
	}
}

