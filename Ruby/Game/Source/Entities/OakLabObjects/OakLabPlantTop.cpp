#include "GamePCH.h"
#include "OakLabPlantTop.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

OakLabPlantTop::OakLabPlantTop(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture)
	: Entity(myGame, myMesh, aTexture)
{
	m_pMesh = myMesh;
	myTextureIdentifier = aTexture;
	m_MyResourceManager = myResourceManager;
	m_MyTileMap = myTileMap;

	for (int i = 0; i < OakLabPlant_NumTiles; i++)
	{
		TileInfo atile = m_MyTileMap->GetTileFromOakLabMap(Oak_Lab_Plant_);

		Frame aframe = atile.MyVariant.at(OakLabPlantMap[i]);

		aframe.myUVOffset = Vector2Float((aframe.myOrigin.myX / m_MyResourceManager->GetTextureSize(1).x), (aframe.myOrigin.myY / m_MyResourceManager->GetTextureSize(1).y));
		aframe.myUVScale = Vector2Float((aframe.mySize.myX / m_MyResourceManager->GetTextureSize(1).x), (aframe.mySize.myY / m_MyResourceManager->GetTextureSize(1).y));

		aframe.myWorldSpace = Vector2Float((((i % OakLabPlant_NumTiles) * (NUM_LAB_COLUMNS - 1)) * TILESIZE), (2.0f * TILESIZE));

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

void OakLabPlantTop::Update(float deltatime)
{
}

void OakLabPlantTop::Draw(Vector2Float camPos, Vector2Float camProject)
{
	for (int i = 0; i < OakLabPlant_NumTiles; i++)
	{
		m_pMesh->Draw(m_MyFrames.at(i).myWorldSpace, m_Angle, Vector2Float(TILESIZE, TILESIZE), camPos, camProject, myTextureIdentifier, m_MyFrames.at(i).myUVScale, m_MyFrames.at(i).myUVOffset);
	}
}
