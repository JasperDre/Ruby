#include "GamePCH.h"
#include "PetalburgWoodsMap.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Canvas.h"
#include "Mesh/Mesh.h"

PetalburgWoodsMap::PetalburgWoodsMap(ResourceManager * myResourceManager, TileMap * myTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture) : GameObject(myGame, myMesh, aTexture)
{
	m_pMyTexture = aTexture;
	m_MyTileMap = myTileMap;
	m_MyResourceManager = myResourceManager;

	m_MyCanvas = new Canvas(m_MyTileMap, m_MyResourceManager);
	m_MyCanvas->SetShader(m_pGame->GetShader(), m_pGame->GetDebugShader());

	m_MyCanvas->GenerateForestVertexData(ForestBitMap);

	m_MyCanvas->GenterateCanvasMesh((FORESTMAPSIZE * 4) - (NUM_FOREST_COLUMNS));
}

PetalburgWoodsMap::~PetalburgWoodsMap()
{
	delete m_MyCanvas;
}

void PetalburgWoodsMap::Update(float deltatime)
{

}

void PetalburgWoodsMap::Draw(vec2 camPos, vec2 projecScale)
{
	m_MyCanvas->DrawCanvas(camPos, projecScale, m_pMyTexture);
}
