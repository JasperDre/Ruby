#include "GamePCH.h"

#include "GameObjects/GameObject.h"
#include "PalletTownMap.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "GameplayHelpers/TileMapPalletTown.h"

#include "Mesh/Mesh.h"
#include "Mesh/Canvas.h"

PalletTownMap::PalletTownMap(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture) : GameObject(myGame, myMesh, aTexture)
{
	m_pMyTexture = aTexture;
	m_MyTileMap = myTileMap;
	m_MyResourceManager = myResourceManager;

	m_MyCanvas = new Canvas(m_MyTileMap, m_MyResourceManager);
	m_MyCanvas->SetShader(m_pGame->GetShader(), m_pGame->GetDebugShader());

	m_MyCanvas->GeneratePalletVertexData(PalletTownBitMap);

	m_MyCanvas->GenterateCanvasMesh((MAPSIZE * 4) - NUM_COLUMNS);
}

PalletTownMap::~PalletTownMap()
{
	delete m_MyCanvas;
}

void PalletTownMap::Update(float deltatime)
{


}

void PalletTownMap::Draw(vec2 camPos, vec2 projecScale)
{
	m_MyCanvas->DrawCanvas(camPos, projecScale, m_pMyTexture);
}
