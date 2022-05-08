#include "GamePCH.h"

#include "GameObjects/GameObject.h"
#include "UIObject.h"
#include "GameObjects/UI/ScoreNumber.h"
#include "GameObjects/UI/PokeBall.h"

#include "GameplayHelpers/TileMap.h"
#include "GameplayHelpers/TileMapExtras.h"
#include "Mesh/Mesh.h"

#include "Game/Game.h"
#include "GameObjects/Trainer.h"

UIObject::UIObject(ResourceManager * aResourceManager, TileMap* aTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture) : GameObject(myGame, myMesh, aTexture)
{
	m_PokeBall = new PokeBall(aResourceManager, aTileMap, myGame, myMesh, aTexture);
	m_ScoreNumber = new ScoreNumber(aResourceManager, aTileMap, myGame, myMesh, aTexture);

	m_PokeBall->SetPosition(vec2(m_Position.x - 14.0f, m_Position.y + 12.5f));
	m_ScoreNumber->SetPosition(vec2(m_Position.x - 12.5f, m_Position.y + 12.5f));
}

UIObject::~UIObject()
{
	delete m_PokeBall;
	delete m_ScoreNumber;
}

void UIObject::Update(float deltatime)
{
}

void UIObject::Draw(vec2 camPos, vec2 camProjection)
{
	m_PokeBall->Draw(camPos, camProjection);
	m_ScoreNumber->Draw(camPos, camProjection);
}

void UIObject::SetScore(int aScore)
{
	m_ScoreNumber->SetScore(aScore);
}
