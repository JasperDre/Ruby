#include "GamePCH.h"
#include "OakLabTableTop.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

OakLabTableTop::OakLabTableTop(ResourceManager * myResourceManager, TileMap * myTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture) : GameObject(myGame, myMesh, aTexture)
{
	m_pMesh = myMesh;
	m_pMyTexture = aTexture;
	m_MyResourceManager = myResourceManager;
	m_MyTileMap = myTileMap;

	OakLabTableTopPosition = vec2(10.0f * TILESIZE, 9.0f * TILESIZE);

	for (int i = 0; i < OakLabTableTop_NumTiles; i++)
	{

		TileInfo atile = m_MyTileMap->GetTileFromOakLabMap(Oak_Lab_Table_);

		Frame aframe = atile.MyVariant.at(OakLabTableTopMap[i]);

		aframe.myUVOffset = vec2((aframe.myOrigin.x / m_MyResourceManager->GetTextureSize(1).x), (aframe.myOrigin.y / m_MyResourceManager->GetTextureSize(1).y));
		aframe.myUVScale = vec2((aframe.mySize.x / m_MyResourceManager->GetTextureSize(1).x), (aframe.mySize.y / m_MyResourceManager->GetTextureSize(1).y));

		aframe.myWorldSpace = vec2((((i % OakLabTableTop_NumTiles) * TILESIZE) + OakLabTableTopPosition.x), (((i / OakLabTableTop_NumTiles)* TILESIZE) + OakLabTableTopPosition.y));

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

void OakLabTableTop::Draw(vec2 camPos, vec2 camProject)
{
	for (int i = 0; i < OakLabTableTop_NumTiles; i++)
	{
		m_pMesh->Draw(m_MyFrames.at(i).myWorldSpace, m_Angle, vec2(TILESIZE, TILESIZE), camPos, camProject, m_pMyTexture, m_MyFrames.at(i).myUVScale, m_MyFrames.at(i).myUVOffset);
	}
}
