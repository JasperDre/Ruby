#include "GamePCH.h"

#include "GameObjects/GameObject.h"
#include "OakLabMachineTop.h"

#include "Mesh/Mesh.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "GameplayHelpers/TileMapPalletTown.h"

OakLabMachineTop::OakLabMachineTop(ResourceManager * myResourceManager, TileMap * myTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture) : GameObject(myGame, myMesh, aTexture)
{
	m_pMesh = myMesh;
	m_pMyTexture = aTexture;
	m_MyResourceManager = myResourceManager;
	m_MyTileMap = myTileMap;
	OaklabMachinePosition = vec2(3.0f * TILESIZE, 10.0f * TILESIZE);

	for (int i = 0; i < OakLabMachine_NumTiles; i++)
	{

		TileInfo atile = m_MyTileMap->GetTileFromOakLabMap(Oak_Lab_Machine_);

		Frame aframe = atile.MyVariant.at(OakLabMachineMap[i]);

		aframe.uvoffset = vec2((aframe.origin.x / m_MyResourceManager->GetTextureSize(1).x), (aframe.origin.y / m_MyResourceManager->GetTextureSize(1).y));
		aframe.uvscale = vec2((aframe.size.x / m_MyResourceManager->GetTextureSize(1).x), (aframe.size.y / m_MyResourceManager->GetTextureSize(1).y));

		aframe.worldSpace = vec2((((i % OakLabMachine_NumTiles) * TILESIZE) + OaklabMachinePosition.x), (((i / OakLabMachine_NumTiles)* TILESIZE) + OaklabMachinePosition.y));

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

void OakLabMachineTop::Draw(vec2 camPos, vec2 camProject)
{
	for (int i = 0; i < OakLabMachine_NumTiles; i++)
	{
		m_pMesh->Draw(m_MyFrames.at(i).worldSpace, m_Angle, vec2(TILESIZE, TILESIZE), camPos, camProject, m_pMyTexture, m_MyFrames.at(i).uvscale, m_MyFrames.at(i).uvoffset);
	}
}
