#include "GamePCH.h"
#include "OakLabPlantTop.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

OakLabPlantTop::OakLabPlantTop(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier)
	: Sprite(aTileMap, aGameCore, aMesh, aTextureIdentifier)
{
	OakLabPlantMap = { 2, 3 };

	for (unsigned int i = 0; i < OakLabPlantMap.size(); i++)
	{
		TileInfo atile = aTileMap->GetTileFromOakLabMap(Oak_Lab_Plant_);
		Frame aframe = atile.MyVariant.at(OakLabPlantMap[i]);
		aframe.myUVOffset = Vector2Float((aframe.myOrigin.myX / aResourceManager->GetTextureSize(1).x), (aframe.myOrigin.myY / aResourceManager->GetTextureSize(1).y));
		aframe.myUVScale = Vector2Float((aframe.mySize.myX / aResourceManager->GetTextureSize(1).x), (aframe.mySize.myY / aResourceManager->GetTextureSize(1).y));
		aframe.myWorldSpace = Vector2Float((((i % OakLabPlantMap.size()) * (NUM_LAB_COLUMNS - 1)) * TILESIZE), (2.0f * TILESIZE));

		if (i % 2 == 0)
		{
			aframe.myWorldSpace += Vector2Float(2.1f, 0.0f);
		}
		else
		{
			aframe.myWorldSpace -= Vector2Float(2.05f, 0.0f);
		}

		myFrames.push_back(aframe);
	}
}

OakLabPlantTop::~OakLabPlantTop()
{
	myFrames.clear();
}

void OakLabPlantTop::Draw(Vector2Float camPos, Vector2Float camProject)
{
	for (unsigned int i = 0; i < OakLabPlantMap.size(); i++)
	{
		myMesh->Draw(myFrames.at(i).myWorldSpace, myAngle, Vector2Float(TILESIZE, TILESIZE), camPos, camProject, myTextureIdentifier, myFrames.at(i).myUVScale, myFrames.at(i).myUVOffset);
	}
}
