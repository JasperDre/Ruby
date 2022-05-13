#include "GamePCH.h"

#include "OakLabMap.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"
#include "Mesh/Canvas.h"

OakLabMap::OakLabMap(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier)
	: Level(aTileMap, aGameCore, aMesh, aTextureIdentifier)
{
	myCanvas = new Canvas(myTileMap, aResourceManager);
	myCanvas->SetShader(myGameCore->GetShader(), myGameCore->GetDebugShader());
	myCanvas->GenerateLabVertexData(OakLabBitMap);
	myCanvas->GenterateCanvasMesh((LABSIZE * 4) - (NUM_LAB_COLUMNS * 11));
}

OakLabMap::~OakLabMap()
{
	delete myCanvas;
}

void OakLabMap::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	myCanvas->DrawCanvas(camPos, projecScale, myTextureIdentifier);
}
