#include "RivalHouse.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

RivalHouse::RivalHouse(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier)
	: Sprite(aTileMap, aGameCore, aMesh, aTextureIdentifier)
{
	myRivalHouseMap = { 0, 1, 2, 3, 4 };

	myPosition = Vector2Float(18.0f * TileSize, 24.0f * TileSize);

	for (unsigned int i = 0; i < myRivalHouseMap.size(); i++)
	{
		TileInfo atile = aTileMap->GetTileFromPalletTownMap(PalletTownTileType::TrainerHouse);
		Frame aframe = atile.myVariant.at(myRivalHouseMap[i]);
		aframe.myUVOffset = Vector2Float((aframe.myOrigin.myX / aResourceManager->GetTextureSize(0).x), (aframe.myOrigin.myY / aResourceManager->GetTextureSize(0).y));
		aframe.myUVScale = Vector2Float((aframe.mySize.myX / aResourceManager->GetTextureSize(0).x), (aframe.mySize.myY / aResourceManager->GetTextureSize(0).y));
		aframe.myWorldSpace = Vector2Float((((i % myRivalHouseMap.size()) * TileSize) + myPosition.myX), (((i / myRivalHouseMap.size()) * TileSize) + myPosition.myY));

		myFrames.push_back(aframe);
	}
}

RivalHouse::~RivalHouse()
{
	myFrames.clear();
}

void RivalHouse::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	for (unsigned int i = 0; i < myRivalHouseMap.size(); i++)
		myMesh->Draw(myFrames.at(i).myWorldSpace, myAngle, Vector2Float(TileSize, TileSize), camPos, projecScale, myTextureIdentifier, myFrames.at(i).myUVScale, myFrames.at(i).myUVOffset);
}
