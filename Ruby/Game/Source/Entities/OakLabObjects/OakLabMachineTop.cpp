#include "GamePCH.h"
#include "OakLabMachineTop.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

OakLabMachineTop::OakLabMachineTop(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier)
	: Sprite(aTileMap, aGameCore, aMesh, aTextureIdentifier)
{
	OakLabMachineMap = { 4, 5 };
	myPosition = Vector2Float(3.0f * TILESIZE, 10.0f * TILESIZE);

	for (unsigned int i = 0; i < OakLabMachineMap.size(); i++)
	{
		TileInfo atile = aTileMap->GetTileFromOakLabMap(Oak_Lab_Machine_);
		Frame aframe = atile.MyVariant.at(OakLabMachineMap[i]);
		aframe.myUVOffset = Vector2Float((aframe.myOrigin.myX / aResourceManager->GetTextureSize(1).x), (aframe.myOrigin.myY / aResourceManager->GetTextureSize(1).y));
		aframe.myUVScale = Vector2Float((aframe.mySize.myX / aResourceManager->GetTextureSize(1).x), (aframe.mySize.myY / aResourceManager->GetTextureSize(1).y));
		aframe.myWorldSpace = Vector2Float((((i % OakLabMachineMap.size()) * TILESIZE) + myPosition.myX), (((i / OakLabMachineMap.size()) * TILESIZE) + myPosition.myY));

		myFrames.push_back(aframe);
	}
}

OakLabMachineTop::~OakLabMachineTop()
{
	myFrames.clear();
}

void OakLabMachineTop::Draw(Vector2Float camPos, Vector2Float camProject)
{
	for (unsigned int i = 0; i < OakLabMachineMap.size(); i++)
		myMesh->Draw(myFrames.at(i).myWorldSpace, myAngle, Vector2Float(TILESIZE, TILESIZE), camPos, camProject, myTextureIdentifier, myFrames.at(i).myUVScale, myFrames.at(i).myUVOffset);
}
