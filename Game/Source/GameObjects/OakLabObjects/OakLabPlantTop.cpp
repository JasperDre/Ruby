#include "GamePCH.h"

#include "GameObjects/GameObject.h"
#include "OakLabPlantTop.h"

#include "Mesh/Mesh.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "GameplayHelpers/TileMapPalletTown.h"

OakLabPlantTop::OakLabPlantTop(ResourceManager * myResourceManager, TileMap * myTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture) : GameObject(myGame, myMesh, aTexture)
{
	m_pMesh = myMesh;
	m_pMyTexture = aTexture;
	m_MyResourceManager = myResourceManager;
	m_MyTileMap = myTileMap;

	for (int i = 0; i < OakLabPlant_NumTiles; i++)
	{

		TileInfo atile = m_MyTileMap->GetTileFromOakLabMap(Oak_Lab_Plant_);

		Frame aframe = atile.MyVariant.at(OakLabPlantMap[i]);

		aframe.uvoffset = vec2((aframe.origin.x / m_MyResourceManager->GetTextureSize(1).x), (aframe.origin.y / m_MyResourceManager->GetTextureSize(1).y));
		aframe.uvscale = vec2((aframe.size.x / m_MyResourceManager->GetTextureSize(1).x), (aframe.size.y / m_MyResourceManager->GetTextureSize(1).y));

		aframe.worldSpace = vec2((((i % OakLabPlant_NumTiles) * (NUM_LAB_COLUMNS - 1)) * TILESIZE), (2.0f * TILESIZE));

		if (i % 2 == 0)
		{
			aframe.worldSpace += vec2(2.1f, 0.0f);
		}
		else
		{
			aframe.worldSpace -= vec2(2.05f, 0.0f);
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

void OakLabPlantTop::Draw(vec2 camPos, vec2 camProject)
{
	for (int i = 0; i < OakLabPlant_NumTiles; i++)
	{
		m_pMesh->Draw(m_MyFrames.at(i).worldSpace, m_Angle, vec2(TILESIZE, TILESIZE), camPos, camProject, m_pMyTexture, m_MyFrames.at(i).uvscale, m_MyFrames.at(i).uvoffset);
	}
}
