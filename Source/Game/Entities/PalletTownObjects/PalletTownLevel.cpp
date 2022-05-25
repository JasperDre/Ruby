#include "PalletTownLevel.h"

#include "GameCore/GameCore.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Canvas.h"
#include "Mesh/Mesh.h"

PalletTownLevel::PalletTownLevel(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier)
	: Level(aTileMap, aGameCore, aMesh, aTextureIdentifier)
{
	myCanvas = new Canvas(myTileMap, aResourceManager);
	myCanvas->SetShaders(myGameCore->GetShader(), myGameCore->GetDebugShader());
	myCanvas->GeneratePalletVertexData(PalletTownBitMap);
	myCanvas->GenterateCanvasMesh();
}

PalletTownLevel::~PalletTownLevel()
{
	delete myCanvas;
}

void PalletTownLevel::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	myCanvas->DrawCanvas(camPos, projecScale, myTextureIdentifier);
}
