#include "GamePCH.h"
#include "OakLabTableTop.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

OakLabTableTop::OakLabTableTop(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture)
	: Entity(myGame, myMesh, aTexture)
{
	myMesh = myMesh;
	myTextureIdentifier = aTexture;
	m_MyResourceManager = myResourceManager;
	m_MyTileMap = myTileMap;

	OakLabTableTopPosition = Vector2Float(10.0f * TILESIZE, 9.0f * TILESIZE);

	for (int i = 0; i < OakLabTableTop_NumTiles; i++)
	{
		TileInfo atile = m_MyTileMap->GetTileFromOakLabMap(Oak_Lab_Table_);

		Frame aframe = atile.MyVariant.at(OakLabTableTopMap[i]);

		aframe.myUVOffset = Vector2Float((aframe.myOrigin.myX / m_MyResourceManager->GetTextureSize(1).x), (aframe.myOrigin.myY / m_MyResourceManager->GetTextureSize(1).y));
		aframe.myUVScale = Vector2Float((aframe.mySize.myX / m_MyResourceManager->GetTextureSize(1).x), (aframe.mySize.myY / m_MyResourceManager->GetTextureSize(1).y));

		aframe.myWorldSpace = Vector2Float((((i % OakLabTableTop_NumTiles) * TILESIZE) + OakLabTableTopPosition.myX), (((i / OakLabTableTop_NumTiles)* TILESIZE) + OakLabTableTopPosition.myY));

		m_MyFrames.push_back(aframe);
	}
}

OakLabTableTop::~OakLabTableTop()
{
	m_MyFrames.clear();
}

void OakLabTableTop::Update(float deltatime)
{
}

void OakLabTableTop::Draw(Vector2Float camPos, Vector2Float camProject)
{
	for (int i = 0; i < OakLabTableTop_NumTiles; i++)
	{
		myMesh->Draw(m_MyFrames.at(i).myWorldSpace, myAngle, Vector2Float(TILESIZE, TILESIZE), camPos, camProject, myTextureIdentifier, m_MyFrames.at(i).myUVScale, m_MyFrames.at(i).myUVOffset);
	}
}
