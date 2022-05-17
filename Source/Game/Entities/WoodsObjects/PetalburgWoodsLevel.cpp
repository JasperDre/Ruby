#include "PetalburgWoodsLevel.h"

#include "GameCore/GameCore.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Canvas.h"
#include "Mesh/Mesh.h"

PetalburgWoodsLevel::PetalburgWoodsLevel(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier)
	: Level(aTileMap, aGameCore, aMesh, aTextureIdentifier)
{
	myCanvas = new Canvas(myTileMap, aResourceManager);
	myCanvas->SetShader(myGameCore->GetShader(), myGameCore->GetDebugShader());
	myCanvas->GenerateForestVertexData(ForestBitMap);
	myCanvas->GenterateCanvasMesh((FORESTMAPSIZE * 4) - (NUM_FOREST_COLUMNS));
}

PetalburgWoodsLevel::~PetalburgWoodsLevel()
{
	delete myCanvas;
}

void PetalburgWoodsLevel::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	myCanvas->DrawCanvas(camPos, projecScale, myTextureIdentifier);
}
