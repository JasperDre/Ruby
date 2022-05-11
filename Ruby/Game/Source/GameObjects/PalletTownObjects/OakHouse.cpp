#include "GamePCH.h"
#include "OakHouse.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

OakHouse::OakHouse(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture)
	: Entity(myGame, myMesh, aTexture)
{
	m_pMesh = myMesh;
	myTextureIdentifier = aTexture;
	m_MyResourceManager = myResourceManager;
	m_MyTileMap = myTileMap;
	OakHousePosition = Vector2Float(17.0f * TILESIZE, 18.0f * TILESIZE);

	for (int i = 0; i < OakHouse_NumTiles; i++)
	{
		TileInfo atile = m_MyTileMap->GetTileFromPalletMap(Oak_House_);

		Frame aframe = atile.MyVariant.at(OakHouseMap[i]);

		aframe.myUVOffset = Vector2Float((aframe.myOrigin.myX / m_MyResourceManager->GetTextureSize(0).x), (aframe.myOrigin.myY / m_MyResourceManager->GetTextureSize(0).y));
		aframe.myUVScale = Vector2Float((aframe.mySize.myX / m_MyResourceManager->GetTextureSize(0).x), (aframe.mySize.myY / m_MyResourceManager->GetTextureSize(0).y));

		aframe.myWorldSpace = Vector2Float((((i % OakHouse_NumTiles) * TILESIZE) + OakHousePosition.myX), (((i / OakHouse_NumTiles)* TILESIZE) + OakHousePosition.myY));

		m_MyFrames.push_back(aframe);
	}
}

OakHouse::~OakHouse()
{
	m_MyFrames.clear();
}

void OakHouse::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	for (int i = 0; i < OakHouse_NumTiles; i++)
	{
		m_pMesh->Draw(m_MyFrames.at(i).myWorldSpace, m_Angle, Vector2Float(TILESIZE, TILESIZE), camPos, projecScale, myTextureIdentifier, m_MyFrames.at(i).myUVScale, m_MyFrames.at(i).myUVOffset);
	}
}

