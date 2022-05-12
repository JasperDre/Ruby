#include "GamePCH.h"
#include "UIObject.h"

#include "Game/Game.h"
#include "Entities/UI/PokeBall.h"
#include "Entities/UI/ScoreNumber.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

UIObject::UIObject(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* myGame, Mesh * myMesh, GLuint aTexture) : Entity(myGame, myMesh, aTexture)
{
	m_PokeBall = new PokeBall(aResourceManager, aTileMap, myGame, myMesh, aTexture);
	m_ScoreNumber = new ScoreNumber(aResourceManager, aTileMap, myGame, myMesh, aTexture);
	m_PokeBall->SetPosition(Vector2Float(myPosition.myX - 14.0f, myPosition.myY + 12.5f));
	m_ScoreNumber->SetPosition(Vector2Float(myPosition.myX - 12.5f, myPosition.myY + 12.5f));
}

UIObject::~UIObject()
{
	delete m_PokeBall;
	delete m_ScoreNumber;
}

void UIObject::Draw(Vector2Float camPos, Vector2Float camProjection)
{
	m_PokeBall->Draw(camPos, camProjection);
	m_ScoreNumber->Draw(camPos, camProjection);
}

void UIObject::SetScore(int aScore) const
{
	m_ScoreNumber->SetScore(aScore);
}
