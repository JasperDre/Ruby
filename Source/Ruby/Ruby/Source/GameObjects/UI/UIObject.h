#pragma once
class GameObject;
class TileMap;
class PokeBall;
class ScoreNumber;

class UIObject : public GameObject
{
protected:

public:
	UIObject(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~UIObject();

	virtual void Update(float deltatime) override;

	virtual void Draw(vec2 camPos, vec2 camProjection);

	void SetScore(int aScore);
private:
	PokeBall* m_PokeBall;
	ScoreNumber* m_ScoreNumber;

};