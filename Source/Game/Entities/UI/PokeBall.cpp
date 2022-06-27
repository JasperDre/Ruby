#include "PokeBall.h"

#include "Entities/Entity.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

PokeBall::PokeBall(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier)
	: Entity(aGameCore, aMesh, aTextureIdentifier)
{
	myExtrasTileMap = aTileMap;
	myTextureIdentifier = aTextureIdentifier;

	myFrame = myExtrasTileMap->GetFrameFromExtrasMap("PokeBall_UIScore.png");
	myFrame.myUVOffset = Vector2Float(myFrame.myOrigin.myX / static_cast<float>(aResourceManager->GetTextureSize(4).x), myFrame.myOrigin.myY / static_cast<float>(aResourceManager->GetTextureSize(4).y));
	myFrame.myUVScale = Vector2Float(myFrame.mySize.myX / static_cast<float>(aResourceManager->GetTextureSize(4).x), myFrame.mySize.myY / static_cast<float>(aResourceManager->GetTextureSize(4).y));
}

void PokeBall::Draw(Vector2Float camPos, Vector2Float camProjection)
{
	myFrame.myWorldSpace = myPosition;
	myMesh->Draw(myFrame.myWorldSpace, 0.0f, TileSize * 0.8f, 0, camProjection, myTextureIdentifier, myFrame.myUVScale, myFrame.myUVOffset);
}
