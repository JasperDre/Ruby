#include "OakHouse.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

OakHouse::OakHouse(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier)
	: Sprite(aTileMap, aGameCore, aMesh, aTextureIdentifier)
{
	myOakHouseMap = { 0, 1, 2, 3, 4, 5, 6 };
	myPosition = Vector2Float(17.0f * TileSize, 18.0f * TileSize);

	for (unsigned int i = 0; i < myOakHouseMap.size(); i++)
	{
		TileInfo atile = aTileMap->GetTileFromPalletTownMap(PalletTownTileType::OakHouse);
		Frame aframe = atile.myVariant.at(myOakHouseMap[i]);
		aframe.myUVOffset = Vector2Float((aframe.myOrigin.myX / aResourceManager->GetTextureSize(0).x), (aframe.myOrigin.myY / aResourceManager->GetTextureSize(0).y));
		aframe.myUVScale = Vector2Float((aframe.mySize.myX / aResourceManager->GetTextureSize(0).x), (aframe.mySize.myY / aResourceManager->GetTextureSize(0).y));
		aframe.myWorldSpace = Vector2Float((((i % myOakHouseMap.size()) * TileSize) + myPosition.myX), (((i / myOakHouseMap.size())* TileSize) + myPosition.myY));

		myFrames.push_back(aframe);
	}
}

OakHouse::~OakHouse()
{
	myFrames.clear();
}

void OakHouse::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	for (unsigned int i = 0; i < myOakHouseMap.size(); i++)
		myMesh->Draw(myFrames.at(i).myWorldSpace, myAngle, Vector2Float(TileSize, TileSize), camPos, projecScale, myTextureIdentifier, myFrames.at(i).myUVScale, myFrames.at(i).myUVOffset);
}

