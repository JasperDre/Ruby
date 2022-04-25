#include "GamePCH.h"

#include "GameObjects/GameObject.h"
#include "OakLabDeskTop.h"

#include "Mesh/Mesh.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "GameplayHelpers/TileMapPalletTown.h"

OakLabDeskTop::OakLabDeskTop(ResourceManager * myResourceManager, TileMap * myTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture) : GameObject(myGame, myMesh, aTexture)
{
	m_pMesh = myMesh;
	m_pMyTexture = aTexture;
	m_MyResourceManager = myResourceManager;
	m_MyTileMap = myTileMap;
	OaklabDeskPosition = vec2(1.0f * TILESIZE, 13.0f * TILESIZE);

	for (int i = 0; i < OakLabDesk_NumTiles; i++)
	{

		TileInfo atile = m_MyTileMap->GetTileFromOakLabMap(Oak_Lab_WorkDesk_);

		Frame aframe = atile.MyVariant.at(OakHOakLabDeskMap[i]);

		aframe.uvoffset = vec2((aframe.origin.x / m_MyResourceManager->GetTextureSize(1).x), (aframe.origin.y / m_MyResourceManager->GetTextureSize(1).y));
		aframe.uvscale = vec2((aframe.size.x / m_MyResourceManager->GetTextureSize(1).x), (aframe.size.y / m_MyResourceManager->GetTextureSize(1).y));

		aframe.worldSpace = vec2((((i % OakLabDesk_NumTiles) * TILESIZE) + OaklabDeskPosition.x), (((i / OakLabDesk_NumTiles)* TILESIZE) + OaklabDeskPosition.y));

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

void OakLabDeskTop::Draw(vec2 camPos, vec2 camProject)
{
	for (int i = 0; i < OakLabDesk_NumTiles; i++)
	{
		m_pMesh->Draw(m_MyFrames.at(i).worldSpace, m_Angle, vec2(TILESIZE, TILESIZE), camPos, camProject, m_pMyTexture, m_MyFrames.at(i).uvscale, m_MyFrames.at(i).uvoffset);
	}
}
