#include "GamePCH.h"
#include "RivalHouse.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

RivalHouse::RivalHouse(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTexture)
	: Sprite(aTileMap, aGameCore, aMesh, aTexture)
{
	RivalHouseMap = { 0, 1, 2, 3, 4 };

	m_RivalHousePosition = Vector2Float(18.0f * TILESIZE, 24.0f * TILESIZE);

	for (unsigned int i = 0; i < RivalHouseMap.size(); i++)
	{
		TileInfo atile = aTileMap->GetTileFromPalletMap(Trainer_House_);
		Frame aframe = atile.MyVariant.at(RivalHouseMap[i]);
		aframe.myUVOffset = Vector2Float((aframe.myOrigin.myX / aResourceManager->GetTextureSize(0).x), (aframe.myOrigin.myY / aResourceManager->GetTextureSize(0).y));
		aframe.myUVScale = Vector2Float((aframe.mySize.myX / aResourceManager->GetTextureSize(0).x), (aframe.mySize.myY / aResourceManager->GetTextureSize(0).y));
		aframe.myWorldSpace = Vector2Float((((i % RivalHouseMap.size()) * TILESIZE) + m_RivalHousePosition.myX), (((i / RivalHouseMap.size()) * TILESIZE) + m_RivalHousePosition.myY));

		myFrames.push_back(aframe);
	}
}

RivalHouse::~RivalHouse()
{
	myFrames.clear();
}

void RivalHouse::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	for (unsigned int i = 0; i < RivalHouseMap.size(); i++)
		myMesh->Draw(myFrames.at(i).myWorldSpace, myAngle, Vector2Float(TILESIZE, TILESIZE), camPos, projecScale, myTextureIdentifier, myFrames.at(i).myUVScale, myFrames.at(i).myUVOffset);
}
