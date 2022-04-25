#pragma once
class GameObject;
class TileMap;
class ResourceManager;

using namespace std;

class ScoreNumber : public GameObject
{
protected:

public:
	ScoreNumber(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~ScoreNumber();

	virtual void Update(float deltatime) override;

	virtual void Draw(vec2 camPos, vec2 camProjection);

	void SetScore(int aScore);

private:
	vector<Frame>MyScoreFrames;
	TileMap* m_MyExtrasTileMap;
	ResourceManager* m_MyResourceManager;

	int DigitsOnScore[6];
};