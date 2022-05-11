#include "GamePCH.h"
#include "OakLabMachineTop.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

OakLabMachineTop::OakLabMachineTop(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture)
	: Entity(myGame, myMesh, aTexture)
{
	m_pMesh = myMesh;
	myTextureIdentifier = aTexture;
	m_MyResourceManager = myResourceManager;
	m_MyTileMap = myTileMap;
	OaklabMachinePosition = Vector2Float(3.0f * TILESIZE, 10.0f * TILESIZE);

	for (int i = 0; i < OakLabMachine_NumTiles; i++)
	{
		TileInfo atile = m_MyTileMap->GetTileFromOakLabMap(Oak_Lab_Machine_);

		Frame aframe = atile.MyVariant.at(OakLabMachineMap[i]);

		aframe.myUVOffset = Vector2Float((aframe.myOrigin.myX / m_MyResourceManager->GetTextureSize(1).x), (aframe.myOrigin.myY / m_MyResourceManager->GetTextureSize(1).y));
		aframe.myUVScale = Vector2Float((aframe.mySize.myX / m_MyResourceManager->GetTextureSize(1).x), (aframe.mySize.myY / m_MyResourceManager->GetTextureSize(1).y));

		aframe.myWorldSpace = Vector2Float((((i % OakLabMachine_NumTiles) * TILESIZE) + OaklabMachinePosition.myX), (((i / OakLabMachine_NumTiles)* TILESIZE) + OaklabMachinePosition.myY));

		m_MyFrames.push_back(aframe);
	}
}

OakLabMachineTop::~OakLabMachineTop()
{
	m_MyFrames.clear();
}

void OakLabMachineTop::Update(float deltatime)
{
}

void OakLabMachineTop::Draw(Vector2Float camPos, Vector2Float camProject)
{
	for (int i = 0; i < OakLabMachine_NumTiles; i++)
	{
		m_pMesh->Draw(m_MyFrames.at(i).myWorldSpace, m_Angle, Vector2Float(TILESIZE, TILESIZE), camPos, camProject, myTextureIdentifier, m_MyFrames.at(i).myUVScale, m_MyFrames.at(i).myUVOffset);
	}
}