#include "OakLabPlantTop.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

OakLabPlantTop::OakLabPlantTop(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier)
	: Sprite(aTileMap, aGameCore, aMesh, aTextureIdentifier)
{
	myOakLabPlantMap = { 2, 3 };

	for (unsigned int i = 0; i < myOakLabPlantMap.size(); i++)
	{
		TileInfo tileInfo = aTileMap->GetTileFromOakLabMap(OakLabPlant);
		Frame frame = tileInfo.myVariant.at(myOakLabPlantMap[i]);
		frame.myUVOffset = Vector2Float((frame.myOrigin.myX / aResourceManager->GetTextureSize(1).x), (frame.myOrigin.myY / aResourceManager->GetTextureSize(1).y));
		frame.myUVScale = Vector2Float((frame.mySize.myX / aResourceManager->GetTextureSize(1).x), (frame.mySize.myY / aResourceManager->GetTextureSize(1).y));
		frame.myWorldSpace = Vector2Float((((i % myOakLabPlantMap.size()) * (NUM_LAB_COLUMNS - 1)) * TILESIZE), (2.0f * TILESIZE));

		if (i % 2 == 0)
		{
			frame.myWorldSpace += Vector2Float(2.1f, 0.0f);
		}
		else
		{
			frame.myWorldSpace -= Vector2Float(2.05f, 0.0f);
		}

		myFrames.push_back(frame);
	}
}

OakLabPlantTop::~OakLabPlantTop()
{
	myFrames.clear();
}

void OakLabPlantTop::Draw(Vector2Float camPos, Vector2Float camProject)
{
	for (unsigned int i = 0; i < myOakLabPlantMap.size(); i++)
	{
		myMesh->Draw(myFrames.at(i).myWorldSpace, myAngle, Vector2Float(TILESIZE, TILESIZE), camPos, camProject, myTextureIdentifier, myFrames.at(i).myUVScale, myFrames.at(i).myUVOffset);
	}
}
