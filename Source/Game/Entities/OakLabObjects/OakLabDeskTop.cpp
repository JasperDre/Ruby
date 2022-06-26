#include "OakLabDeskTop.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

OakLabDeskTop::OakLabDeskTop(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier)
	: Sprite(aTileMap, aGameCore, aMesh, aTextureIdentifier)
{
	myOakLabDeskTopMap = { 11, 10, 9, 8, 7, 6 };
	myPosition = Vector2Float(1.0f * TILESIZE, 13.0f * TILESIZE);

	for (unsigned int i = 0; i < myOakLabDeskTopMap.size(); i++)
	{
		TileInfo atile = aTileMap->GetTileFromOakLabMap(OakLabWorkDesk);
		Frame aframe = atile.myVariant.at(myOakLabDeskTopMap[i]);
		aframe.myUVOffset = Vector2Float((aframe.myOrigin.myX / aResourceManager->GetTextureSize(1).x), (aframe.myOrigin.myY / aResourceManager->GetTextureSize(1).y));
		aframe.myUVScale = Vector2Float((aframe.mySize.myX / aResourceManager->GetTextureSize(1).x), (aframe.mySize.myY / aResourceManager->GetTextureSize(1).y));
		aframe.myWorldSpace = Vector2Float((((i % myOakLabDeskTopMap.size()) * TILESIZE) + myPosition.myX), (((i / myOakLabDeskTopMap.size())* TILESIZE) + myPosition.myY));

		myFrames.push_back(aframe);
	}
}

OakLabDeskTop::~OakLabDeskTop()
{
	myFrames.clear();
}

void OakLabDeskTop::Draw(Vector2Float camPos, Vector2Float camProject)
{
	for (unsigned int i = 0; i < myOakLabDeskTopMap.size(); i++)
		myMesh->Draw(myFrames.at(i).myWorldSpace, myAngle, Vector2Float(TILESIZE, TILESIZE), camPos, camProject, myTextureIdentifier, myFrames.at(i).myUVScale, myFrames.at(i).myUVOffset);
}
