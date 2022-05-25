#include "OakLabLevel.h"

#include "GameCore/GameCore.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Canvas.h"
#include "Mesh/Mesh.h"

OakLabLevel::OakLabLevel(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier)
	: Level(aTileMap, aGameCore, aMesh, aTextureIdentifier)
{
	myCanvas = new Canvas(myTileMap, aResourceManager);
	myCanvas->SetShaders(myGameCore->GetShader(), myGameCore->GetDebugShader());
	myCanvas->GenerateLabVertexData(OakLabBitMap);
	myCanvas->GenterateCanvasMesh();
}

OakLabLevel::~OakLabLevel()
{
	delete myCanvas;
}

void OakLabLevel::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	myCanvas->DrawCanvas(camPos, projecScale, myTextureIdentifier);
}
