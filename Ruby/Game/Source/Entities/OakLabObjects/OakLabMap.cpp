#include "GamePCH.h"

#include "OakLabMap.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"
#include "Mesh/Canvas.h"

OakLabMap::OakLabMap(ResourceManager* myResourceManager, TileMap* myTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture)
	: Entity(myGame, myMesh, aTexture)
{
	myTextureIdentifier = aTexture;
	m_MyTileMap = myTileMap;
	m_MyResourceManager = myResourceManager;
	m_MyCanvas = new Canvas(m_MyTileMap, m_MyResourceManager);
	m_MyCanvas->SetShader(myGameCore->GetShader(), myGameCore->GetDebugShader());
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

void OakLabMap::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	m_MyCanvas->DrawCanvas(camPos, projecScale, myTextureIdentifier);
}
