#include "GamePCH.h"
#include "OakHouse.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

OakHouse::OakHouse(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTexture)
	: Sprite(aTileMap, aGameCore, aMesh, aTexture)
{
	OakHouseMap = { 0, 1, 2, 3, 4, 5, 6 };
	myPosition = Vector2Float(17.0f * TILESIZE, 18.0f * TILESIZE);

	for (unsigned int i = 0; i < OakHouseMap.size(); i++)
	{
		TileInfo atile = aTileMap->GetTileFromPalletMap(Oak_House_);
		Frame aframe = atile.MyVariant.at(OakHouseMap[i]);
		aframe.myUVOffset = Vector2Float((aframe.myOrigin.myX / aResourceManager->GetTextureSize(0).x), (aframe.myOrigin.myY / aResourceManager->GetTextureSize(0).y));
		aframe.myUVScale = Vector2Float((aframe.mySize.myX / aResourceManager->GetTextureSize(0).x), (aframe.mySize.myY / aResourceManager->GetTextureSize(0).y));
		aframe.myWorldSpace = Vector2Float((((i % OakHouseMap.size()) * TILESIZE) + myPosition.myX), (((i / OakHouseMap.size())* TILESIZE) + myPosition.myY));

		myFrames.push_back(aframe);
	}
}

OakHouse::~OakHouse()
{
	myFrames.clear();
}

void OakHouse::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	for (unsigned int i = 0; i < OakHouseMap.size(); i++)
		myMesh->Draw(myFrames.at(i).myWorldSpace, myAngle, Vector2Float(TILESIZE, TILESIZE), camPos, projecScale, myTextureIdentifier, myFrames.at(i).myUVScale, myFrames.at(i).myUVOffset);
}
