#include "UIObject.h"

#include "Game/Game.h"
#include "Entities/UI/PokeBall.h"
#include "Entities/UI/ScoreNumber.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

UIObject::UIObject(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* aGameCore, Mesh* aMesh, unsigned int aTextureIdentifier)
	: Entity(aGameCore, aMesh, aTextureIdentifier)
{
	myPokeBall = new PokeBall(aResourceManager, aTileMap, aGameCore, myMesh, aTextureIdentifier);
	myScoreNumber = new ScoreNumber(aResourceManager, aTileMap, aGameCore, myMesh, aTextureIdentifier);
	myPokeBall->SetPosition(Vector2Float(myPosition.myX - 14.0f, myPosition.myY + 12.5f));
	myScoreNumber->SetPosition(Vector2Float(myPosition.myX - 12.5f, myPosition.myY + 12.5f));
}

UIObject::~UIObject()
{
	delete myScoreNumber;
	delete myPokeBall;
}

void UIObject::Draw(Vector2Float camPos, Vector2Float camProjection)
{
	myPokeBall->Draw(camPos, camProjection);
	myScoreNumber->Draw(camPos, camProjection);
}

void UIObject::SetScore(int aScore) const
{
	myScoreNumber->SetScore(aScore);
}
