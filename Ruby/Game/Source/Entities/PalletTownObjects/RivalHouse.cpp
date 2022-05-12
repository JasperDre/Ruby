#include "GamePCH.h"
#include "RivalHouse.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

RivalHouse::RivalHouse(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture) : Entity(myGame, myMesh, aTexture)
{
	myMesh = myMesh;
	myTextureIdentifier = aTexture;
	m_MyResourceManager = myResourceManager;
	m_MyTileMap = myTileMap;

	m_RivalHousePosition = Vector2Float(18.0f * TILESIZE, 24.0f * TILESIZE);

	for (int i = 0; i < RivalHouse_NumTiles; i++)
	{

		TileInfo atile = m_MyTileMap->GetTileFromPalletMap(Trainer_House_);

		Frame aframe = atile.MyVariant.at(RivalHouseMap[i]);

		aframe.myUVOffset = Vector2Float((aframe.myOrigin.myX / m_MyResourceManager->GetTextureSize(0).x), (aframe.myOrigin.myY / m_MyResourceManager->GetTextureSize(0).y));
		aframe.myUVScale = Vector2Float((aframe.mySize.myX / m_MyResourceManager->GetTextureSize(0).x), (aframe.mySize.myY / m_MyResourceManager->GetTextureSize(0).y));

		aframe.myWorldSpace = Vector2Float((((i % RivalHouse_NumTiles) * TILESIZE) + m_RivalHousePosition.myX), (((i / RivalHouse_NumTiles)* TILESIZE) + m_RivalHousePosition.myY));

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

void RivalHouse::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	for (int i = 0; i < RivalHouse_NumTiles; i++)
	{
		myMesh->Draw(m_MyFrames.at(i).myWorldSpace, myAngle, Vector2Float(TILESIZE, TILESIZE), camPos, projecScale, myTextureIdentifier, m_MyFrames.at(i).myUVScale, m_MyFrames.at(i).myUVOffset);
	}
}
