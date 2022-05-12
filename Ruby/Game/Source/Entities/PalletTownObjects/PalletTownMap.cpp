#include "GamePCH.h"
#include "PalletTownMap.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Canvas.h"
#include "Mesh/Mesh.h"

PalletTownMap::PalletTownMap(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture)
	: Entity(myGame, myMesh, aTexture)
{
	myTextureIdentifier = aTexture;
	m_MyTileMap = myTileMap;
	m_MyResourceManager = myResourceManager;
	m_MyCanvas = new Canvas(m_MyTileMap, m_MyResourceManager);
	m_MyCanvas->SetShader(myGameCore->GetShader(), myGameCore->GetDebugShader());
	m_MyCanvas->GeneratePalletVertexData(PalletTownBitMap);
	m_MyCanvas->GenterateCanvasMesh((MAPSIZE * 4) - NUM_COLUMNS);
}

PalletTownMap::~PalletTownMap()
{
	delete m_MyCanvas;
}

void PalletTownMap::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	m_MyCanvas->DrawCanvas(camPos, projecScale, myTextureIdentifier);
}
