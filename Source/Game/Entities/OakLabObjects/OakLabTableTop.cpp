#include "OakLabTableTop.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

OakLabTableTop::OakLabTableTop(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTexture)
	: Sprite(aTileMap, aGameCore, aMesh, aTexture)
{
	myOakLabTableTopMap = { 3, 4, 5 };

	myPosition = Vector2Float(10.0f * TileSize, 9.0f * TileSize);

	for (unsigned int i = 0; i < myOakLabTableTopMap.size(); i++)
	{
		TileInfo atile = aTileMap->GetTileFromOakLabMap(OakLabTileType::Table);
		Frame aframe = atile.myVariant.at(myOakLabTableTopMap[i]);
		aframe.myUVOffset = Vector2Float((aframe.myOrigin.myX / aResourceManager->GetTextureSize(1).x), (aframe.myOrigin.myY / aResourceManager->GetTextureSize(1).y));
		aframe.myUVScale = Vector2Float((aframe.mySize.myX / aResourceManager->GetTextureSize(1).x), (aframe.mySize.myY / aResourceManager->GetTextureSize(1).y));
		aframe.myWorldSpace = Vector2Float((((i % myOakLabTableTopMap.size()) * TileSize) + myPosition.myX), (((i / myOakLabTableTopMap.size())* TileSize) + myPosition.myY));

		myFrames.push_back(aframe);
	}
}

OakLabTableTop::~OakLabTableTop()
{
	myFrames.clear();
}

void OakLabTableTop::Draw(Vector2Float camPos, Vector2Float camProject)
{
	for (unsigned int i = 0; i < myOakLabTableTopMap.size(); i++)
		myMesh->Draw(myFrames.at(i).myWorldSpace, myAngle, Vector2Float(TileSize, TileSize), camPos, camProject, myTextureIdentifier, myFrames.at(i).myUVScale, myFrames.at(i).myUVOffset);
}
