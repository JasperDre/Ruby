#include "GamePCH.h"
#include "Entities/UI/ScoreNumber.h"

#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"

ScoreNumber::ScoreNumber(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture)
	: Entity(myGame, myMesh, aTexture)
	 , myResourceManager(aResourceManager)
{
	myTextureIdentifier = aTexture;

	m_MyExtrasTileMap = aTileMap;

	for (int i = 0; i < 7; i++)
	{
		Frame myNewScore = m_MyExtrasTileMap->GetFrameFromExtrasMap(std::to_string(0) + ".png");
		myNewScore.myUVOffset = Vector2Float((myNewScore.myOrigin.myX / myResourceManager->GetTextureSize(4).x), (myNewScore.myOrigin.myY / myResourceManager->GetTextureSize(4).y));
		myNewScore.myUVScale = Vector2Float((myNewScore.mySize.myX / myResourceManager->GetTextureSize(4).x), (myNewScore.mySize.myY / myResourceManager->GetTextureSize(4).y));

		MyScoreFrames.push_back(myNewScore);
	}
}

ScoreNumber::~ScoreNumber()
{
	MyScoreFrames.clear();
}

void ScoreNumber::Draw(Vector2Float camPos, Vector2Float camProjection)
{
	for (int i = 0; i < 7; i++)
	{
		MyScoreFrames.at(i).myWorldSpace = Vector2Float((((i % 7) * TILESIZE) + myPosition.myX), myPosition.myY);

		myMesh->Draw(MyScoreFrames.at(i).myWorldSpace, 0, TILESIZE, 0, camProjection, myTextureIdentifier, MyScoreFrames.at(i).myUVScale, MyScoreFrames.at(i).myUVOffset);
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

		aNewScoreFrame.myUVOffset = Vector2Float((aNewScoreFrame.myOrigin.myX / myResourceManager->GetTextureSize(4).x), (aNewScoreFrame.myOrigin.myY / myResourceManager->GetTextureSize(4).y));
		aNewScoreFrame.myUVScale = Vector2Float((aNewScoreFrame.mySize.myX / myResourceManager->GetTextureSize(4).x), (aNewScoreFrame.mySize.myY / myResourceManager->GetTextureSize(4).y));

		MyScoreFrames.push_back(aNewScoreFrame);
	}
}
