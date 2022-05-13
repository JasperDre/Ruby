#include "GamePCH.h"
#include "OakLabTableTop.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

OakLabTableTop::OakLabTableTop(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTexture)
	: Sprite(aTileMap, aGameCore, aMesh, aTexture)
{
	OakLabTableTopMap = { 3, 4, 5 };

	OakLabTableTopPosition = Vector2Float(10.0f * TILESIZE, 9.0f * TILESIZE);

	for (unsigned int i = 0; i < OakLabTableTopMap.size(); i++)
	{
		TileInfo atile = aTileMap->GetTileFromOakLabMap(Oak_Lab_Table_);
		Frame aframe = atile.MyVariant.at(OakLabTableTopMap[i]);
		aframe.myUVOffset = Vector2Float((aframe.myOrigin.myX / aResourceManager->GetTextureSize(1).x), (aframe.myOrigin.myY / aResourceManager->GetTextureSize(1).y));
		aframe.myUVScale = Vector2Float((aframe.mySize.myX / aResourceManager->GetTextureSize(1).x), (aframe.mySize.myY / aResourceManager->GetTextureSize(1).y));
		aframe.myWorldSpace = Vector2Float((((i % OakLabTableTopMap.size()) * TILESIZE) + OakLabTableTopPosition.myX), (((i / OakLabTableTopMap.size())* TILESIZE) + OakLabTableTopPosition.myY));

		myFrames.push_back(aframe);
	}
}

OakLabTableTop::~OakLabTableTop()
{
	myFrames.clear();
}

void OakLabTableTop::Draw(Vector2Float camPos, Vector2Float camProject)
{
	for (unsigned int i = 0; i < OakLabTableTopMap.size(); i++)
		myMesh->Draw(myFrames.at(i).myWorldSpace, myAngle, Vector2Float(TILESIZE, TILESIZE), camPos, camProject, myTextureIdentifier, myFrames.at(i).myUVScale, myFrames.at(i).myUVOffset);
}
