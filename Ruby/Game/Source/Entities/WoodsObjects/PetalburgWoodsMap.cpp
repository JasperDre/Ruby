#include "GamePCH.h"
#include "PetalburgWoodsMap.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Canvas.h"
#include "Mesh/Mesh.h"

PetalburgWoodsMap::PetalburgWoodsMap(ResourceManager * myResourceManager, TileMap * myTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture) : Entity(myGame, myMesh, aTexture)
{
	myTextureIdentifier = aTexture;
	m_MyTileMap = myTileMap;
	m_MyResourceManager = myResourceManager;

	m_MyCanvas = new Canvas(m_MyTileMap, m_MyResourceManager);
	m_MyCanvas->SetShader(myGameCore->GetShader(), myGameCore->GetDebugShader());

	m_MyCanvas->GenerateForestVertexData(ForestBitMap);

	m_MyCanvas->GenterateCanvasMesh((FORESTMAPSIZE * 4) - (NUM_FOREST_COLUMNS));
}

PetalburgWoodsMap::~PetalburgWoodsMap()
{
	delete m_MyCanvas;
}

void PetalburgWoodsMap::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	m_MyCanvas->DrawCanvas(camPos, projecScale, myTextureIdentifier);
}
