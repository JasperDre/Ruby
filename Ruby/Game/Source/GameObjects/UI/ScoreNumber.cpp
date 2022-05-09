#include "GamePCH.h"
#include "GameObjects/UI/ScoreNumber.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

ScoreNumber::ScoreNumber(ResourceManager * aResourceManager, TileMap* aTileMap, GameCore * myGame, Mesh * myMesh, GLuint aTexture) : GameObject(myGame, myMesh, aTexture)
{
	m_pMesh = myMesh;
	m_pMyTexture = aTexture;
	m_MyResourceManager = aResourceManager;

	m_MyExtrasTileMap = aTileMap;

	for (int i = 0; i < 7; i++)
	{
		Frame myNewScore = m_MyExtrasTileMap->GetFrameFromExtrasMap(std::to_string(0) + ".png");
		myNewScore.myUVOffset = vec2((myNewScore.myOrigin.x / m_MyResourceManager->GetTextureSize(4).x), (myNewScore.myOrigin.y / m_MyResourceManager->GetTextureSize(4).y));
		myNewScore.myUVScale = vec2((myNewScore.mySize.x / m_MyResourceManager->GetTextureSize(4).x), (myNewScore.mySize.y / m_MyResourceManager->GetTextureSize(4).y));

		MyScoreFrames.push_back(myNewScore);
	}
}

ScoreNumber::~ScoreNumber()
{
	MyScoreFrames.clear();
}

void ScoreNumber::Draw(vec2 camPos, vec2 camProjection)
{
	for (int i = 0; i < 7; i++)
	{
		MyScoreFrames.at(i).myWorldSpace = vec2((((i % 7) * TILESIZE) + m_Position.x), m_Position.y);

		m_pMesh->Draw(MyScoreFrames.at(i).myWorldSpace, 0, TILESIZE, 0, camProjection, m_pMyTexture, MyScoreFrames.at(i).myUVScale, MyScoreFrames.at(i).myUVOffset);
	}
}

void ScoreNumber::SetScore(int aScore)
{
	const int DigitsOnScore[6] = {
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

		aNewScoreFrame.myUVOffset = vec2((aNewScoreFrame.myOrigin.x / m_MyResourceManager->GetTextureSize(4).x), (aNewScoreFrame.myOrigin.y / m_MyResourceManager->GetTextureSize(4).y));
		aNewScoreFrame.myUVScale = vec2((aNewScoreFrame.mySize.x / m_MyResourceManager->GetTextureSize(4).x), (aNewScoreFrame.mySize.y / m_MyResourceManager->GetTextureSize(4).y));

		MyScoreFrames.push_back(aNewScoreFrame);
	}
}
