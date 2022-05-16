#include "GamePCH.h"
#include "PlayerHouse.h"

#include "Entities/Entity.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

PlayerHouse::PlayerHouse(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier)
	: Sprite(aTileMap, aGameCore, aMesh, aTextureIdentifier)
{
	myPlayerHouseMap = { 0, 1, 2, 3, 4 };

	myPosition = Vector2Float(8.0f * TILESIZE, 24.0f * TILESIZE);

	for (unsigned int i = 0; i < myPlayerHouseMap.size(); i++)
	{
		TileInfo atile = aTileMap->GetTileFromPalletMap(Trainer_House_);
		Frame aframe = atile.myVariant.at(myPlayerHouseMap[i]);
		aframe.myUVOffset = Vector2Float((aframe.myOrigin.myX / aResourceManager->GetTextureSize(0).x), (aframe.myOrigin.myY / aResourceManager->GetTextureSize(0).y));
		aframe.myUVScale = Vector2Float((aframe.mySize.myX / aResourceManager->GetTextureSize(0).x), (aframe.mySize.myY / aResourceManager->GetTextureSize(0).y));
		aframe.myWorldSpace = Vector2Float((((i % myPlayerHouseMap.size()) * TILESIZE) + myPosition.myX), (((i / myPlayerHouseMap.size())* TILESIZE) + myPosition.myY));

		myFrames.push_back(aframe);
	}
}

PlayerHouse::~PlayerHouse()
{
	myFrames.clear();
}

void PlayerHouse::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	for (unsigned int i = 0; i < myPlayerHouseMap.size(); i++)
		myMesh->Draw(myFrames.at(i).myWorldSpace, myAngle, Vector2Float(TILESIZE, TILESIZE), camPos, projecScale, myTextureIdentifier, myFrames.at(i).myUVScale, myFrames.at(i).myUVOffset);
}

