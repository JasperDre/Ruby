#include "GamePCH.h"
#include "OakHouse.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

OakHouse::OakHouse(ResourceManager* aResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture)
	: Entity(myGame, myMesh, aTexture)
{
	OakHouseMap = { 0, 1, 2, 3, 4, 5, 6 };
	myTextureIdentifier = aTexture;
	m_MyTileMap = myTileMap;
	OakHousePosition = Vector2Float(17.0f * TILESIZE, 18.0f * TILESIZE);

	for (unsigned int i = 0; i < OakHouseMap.size(); i++)
	{
		TileInfo atile = m_MyTileMap->GetTileFromPalletMap(Oak_House_);
		Frame aframe = atile.MyVariant.at(OakHouseMap[i]);
		aframe.myUVOffset = Vector2Float((aframe.myOrigin.myX / aResourceManager->GetTextureSize(0).x), (aframe.myOrigin.myY / aResourceManager->GetTextureSize(0).y));
		aframe.myUVScale = Vector2Float((aframe.mySize.myX / aResourceManager->GetTextureSize(0).x), (aframe.mySize.myY / aResourceManager->GetTextureSize(0).y));
		aframe.myWorldSpace = Vector2Float((((i % OakHouseMap.size()) * TILESIZE) + OakHousePosition.myX), (((i / OakHouseMap.size())* TILESIZE) + OakHousePosition.myY));

		m_MyFrames.push_back(aframe);
	}
}

OakHouse::~OakHouse()
{
	m_MyFrames.clear();
}

void OakHouse::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	for (unsigned int i = 0; i < OakHouseMap.size(); i++)
		myMesh->Draw(m_MyFrames.at(i).myWorldSpace, myAngle, Vector2Float(TILESIZE, TILESIZE), camPos, projecScale, myTextureIdentifier, m_MyFrames.at(i).myUVScale, m_MyFrames.at(i).myUVOffset);
}

