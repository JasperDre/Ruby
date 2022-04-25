#include "GamePCH.h"

#include "GameObjects/GameObject.h"
#include "GameObjects/UI/ScoreNumber.h"

#include "GameplayHelpers/TileMap.h"
#include "GameplayHelpers/TileMapExtras.h"
#include "GameplayHelpers/ResourceManager.h"
#include "Mesh/Mesh.h"

#include "Game/Game.h"
#include "ScoreNumber.h"

ScoreNumber::ScoreNumber(ResourceManager * aResourceManager, TileMap* aTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture) : GameObject(myGame, myMesh, aTexture)
{
	m_pMesh = myMesh;
	m_pMyTexture = aTexture;
	m_MyResourceManager = aResourceManager;

	m_MyExtrasTileMap = aTileMap;

	for (int i = 0; i < 7; i++)
	{
		Frame myNewScore = m_MyExtrasTileMap->GetFrameFromExtrasMap(std::to_string(0) + ".png");
		myNewScore.uvoffset = vec2((myNewScore.origin.x / m_MyResourceManager->GetTextureSize(4).x), (myNewScore.origin.y / m_MyResourceManager->GetTextureSize(4).y));
		myNewScore.uvscale = vec2((myNewScore.size.x / m_MyResourceManager->GetTextureSize(4).x), (myNewScore.size.y / m_MyResourceManager->GetTextureSize(4).y));

		MyScoreFrames.push_back(myNewScore);
	}
}

ScoreNumber::~ScoreNumber()
{
	MyScoreFrames.clear();
}

void ScoreNumber::Update(float deltatime)
{
}

void ScoreNumber::Draw(vec2 camPos, vec2 camProjection)
{
	for (int i = 0; i < 7; i++)
	{
		MyScoreFrames.at(i).worldSpace = vec2((((i % 7) * TILESIZE) + m_Position.x), m_Position.y);

		m_pMesh->Draw(MyScoreFrames.at(i).worldSpace, 0, TILESIZE, 0, camProjection, m_pMyTexture, MyScoreFrames.at(i).uvscale, MyScoreFrames.at(i).uvoffset);
	}
}

void ScoreNumber::SetScore(int aScore)
{
	int DigitsOnScore[6] = {
								aScore % 10,
							  (aScore % 100 - aScore % 10) / 10,
							  (aScore % 1000 - aScore % 100) / 100,
							  (aScore % 10000 - aScore % 1000) / 1000,
							  (aScore % 100000 - aScore % 10000) / 10000,
							  (aScore % 1000000 - aScore % 100000) / 100000
	};

	for (int i = 0; i < 7; i++)
	{
		MyScoreFrames.pop_back();
		Frame aNewScoreFrame = m_MyExtrasTileMap->GetFrameFromExtrasMap(std::to_string(DigitsOnScore[i]) + ".png");

		aNewScoreFrame.uvoffset = vec2((aNewScoreFrame.origin.x / m_MyResourceManager->GetTextureSize(4).x), (aNewScoreFrame.origin.y / m_MyResourceManager->GetTextureSize(4).y));
		aNewScoreFrame.uvscale = vec2((aNewScoreFrame.size.x / m_MyResourceManager->GetTextureSize(4).x), (aNewScoreFrame.size.y / m_MyResourceManager->GetTextureSize(4).y));

		MyScoreFrames.push_back(aNewScoreFrame);
	}
}
