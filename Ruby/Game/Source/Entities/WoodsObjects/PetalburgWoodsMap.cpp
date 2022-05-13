#include "GamePCH.h"
#include "PetalburgWoodsMap.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Canvas.h"
#include "Mesh/Mesh.h"

PetalburgWoodsMap::PetalburgWoodsMap(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier)
	: Level(aTileMap, aGameCore, aMesh, aTextureIdentifier)
{
	myCanvas = new Canvas(myTileMap, aResourceManager);
	myCanvas->SetShader(myGameCore->GetShader(), myGameCore->GetDebugShader());
	myCanvas->GenerateForestVertexData(ForestBitMap);
	myCanvas->GenterateCanvasMesh((FORESTMAPSIZE * 4) - (NUM_FOREST_COLUMNS));
}

PetalburgWoodsMap::~PetalburgWoodsMap()
{
	delete myCanvas;
}

void PetalburgWoodsMap::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	myCanvas->DrawCanvas(camPos, projecScale, myTextureIdentifier);
}
