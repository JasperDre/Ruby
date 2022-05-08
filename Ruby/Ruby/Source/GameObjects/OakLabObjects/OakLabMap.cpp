#include "GamePCH.h"

#include "GameObjects/GameObject.h"
#include "OakLabMap.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "GameplayHelpers/TileMapPalletTown.h"

#include "Mesh/Mesh.h"
#include "Mesh/Canvas.h"

OakLabMap::OakLabMap(ResourceManager * myResourceManager, TileMap * myTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture) : GameObject(myGame, myMesh, aTexture)
{
	m_pMyTexture = aTexture;
	m_MyTileMap = myTileMap;
	m_MyResourceManager = myResourceManager;

	m_MyCanvas = new Canvas(m_MyTileMap, m_MyResourceManager);
	m_MyCanvas->SetShader(m_pGame->GetShader(), m_pGame->GetDebugShader());

	m_MyCanvas->GenerateLabVertexData(OakLabBitMap);

	m_MyCanvas->GenterateCanvasMesh((LABSIZE * 4) - (NUM_LAB_COLUMNS * 11));

}

OakLabMap::~OakLabMap()
{
	delete m_MyCanvas;
}

void OakLabMap::Update(float deltatime)
{

}

void OakLabMap::Draw(vec2 camPos, vec2 projecScale)
{
	m_MyCanvas->DrawCanvas(camPos, projecScale, m_pMyTexture);
}
