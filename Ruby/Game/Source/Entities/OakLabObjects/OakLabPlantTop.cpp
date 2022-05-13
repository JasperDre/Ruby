#include "GamePCH.h"
#include "OakLabPlantTop.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

OakLabPlantTop::OakLabPlantTop(ResourceManager* aResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture)
	: Entity(myGame, myMesh, aTexture)
{
	OakLabPlantMap = { 2, 3 };
	myTextureIdentifier = aTexture;
	m_MyTileMap = myTileMap;

	for (unsigned int i = 0; i < OakLabPlantMap.size(); i++)
	{
		TileInfo atile = m_MyTileMap->GetTileFromOakLabMap(Oak_Lab_Plant_);
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

		m_MyFrames.push_back(aframe);
	}
}

OakLabPlantTop::~OakLabPlantTop()
{
	m_MyFrames.clear();
}

void OakLabPlantTop::Draw(Vector2Float camPos, Vector2Float camProject)
{
	for (unsigned int i = 0; i < OakLabPlantMap.size(); i++)
	{
		myMesh->Draw(m_MyFrames.at(i).myWorldSpace, myAngle, Vector2Float(TILESIZE, TILESIZE), camPos, camProject, myTextureIdentifier, m_MyFrames.at(i).myUVScale, m_MyFrames.at(i).myUVOffset);
	}
}
