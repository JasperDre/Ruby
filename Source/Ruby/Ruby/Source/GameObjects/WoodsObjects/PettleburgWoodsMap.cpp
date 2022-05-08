#include "GamePCH.h"

#include "GameObjects/GameObject.h"
#include "PettleburgWoodsMap.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "GameplayHelpers/TileMapWoods.h"

#include "Mesh/Mesh.h"
#include "Mesh/Canvas.h"

PettleburgWoodsMap::PettleburgWoodsMap(ResourceManager * myResourceManager, TileMap * myTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture) : GameObject(myGame, myMesh, aTexture)
{
	m_pMyTexture = aTexture;
	m_MyTileMap = myTileMap;
	m_MyResourceManager = myResourceManager;

	m_MyCanvas = new Canvas(m_MyTileMap, m_MyResourceManager);
	m_MyCanvas->SetShader(m_pGame->GetShader(), m_pGame->GetDebugShader());

	m_MyCanvas->GenerateForestVertexData(ForestBitMap);

	m_MyCanvas->GenterateCanvasMesh((FORESTMAPSIZE * 4) - (NUM_FOREST_COLUMNS));
}

PettleburgWoodsMap::~PettleburgWoodsMap()
{
	delete m_MyCanvas;
}

void PettleburgWoodsMap::Update(float deltatime)
{

}

void PettleburgWoodsMap::Draw(vec2 camPos, vec2 projecScale)
{
	m_MyCanvas->DrawCanvas(camPos, projecScale, m_pMyTexture);
}
