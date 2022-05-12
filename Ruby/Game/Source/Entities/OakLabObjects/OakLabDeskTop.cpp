#include "GamePCH.h"
#include "OakLabDeskTop.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

OakLabDeskTop::OakLabDeskTop(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture)
	: Entity(myGame, myMesh, aTexture)
{
	myMesh = myMesh;
	myTextureIdentifier = aTexture;
	m_MyResourceManager = myResourceManager;
	m_MyTileMap = myTileMap;
	OaklabDeskPosition = Vector2Float(1.0f * TILESIZE, 13.0f * TILESIZE);

	for (int i = 0; i < OakLabDesk_NumTiles; i++)
	{
		TileInfo atile = m_MyTileMap->GetTileFromOakLabMap(Oak_Lab_WorkDesk_);

		Frame aframe = atile.MyVariant.at(OakHOakLabDeskMap[i]);

		aframe.myUVOffset = Vector2Float((aframe.myOrigin.myX / m_MyResourceManager->GetTextureSize(1).x), (aframe.myOrigin.myY / m_MyResourceManager->GetTextureSize(1).y));
		aframe.myUVScale = Vector2Float((aframe.mySize.myX / m_MyResourceManager->GetTextureSize(1).x), (aframe.mySize.myY / m_MyResourceManager->GetTextureSize(1).y));

		aframe.myWorldSpace = Vector2Float((((i % OakLabDesk_NumTiles) * TILESIZE) + OaklabDeskPosition.myX), (((i / OakLabDesk_NumTiles)* TILESIZE) + OaklabDeskPosition.myY));

		m_MyFrames.push_back(aframe);
	}
}

OakLabDeskTop::~OakLabDeskTop()
{
	m_MyFrames.clear();
}

void OakLabDeskTop::Update(float deltatime)
{
}

void OakLabDeskTop::Draw(Vector2Float camPos, Vector2Float camProject)
{
	for (int i = 0; i < OakLabDesk_NumTiles; i++)
	{
		myMesh->Draw(m_MyFrames.at(i).myWorldSpace, myAngle, Vector2Float(TILESIZE, TILESIZE), camPos, camProject, myTextureIdentifier, m_MyFrames.at(i).myUVScale, m_MyFrames.at(i).myUVOffset);
	}
}
