#pragma once
class GameObject;
class TileMap;
class ResourceManager;

class PokeBall : public GameObject
{
protected:

public:
	PokeBall(ResourceManager* aResourceManager, TileMap* aTileMap, GameCore* myGame, Mesh* myMesh, GLuint aTexture);
	~PokeBall();

	virtual void Update(float deltatime) override;

	virtual void Draw(vec2 camPos, vec2 camProjection);

private:
	TileMap* m_MyExtrasTileMap;
	ResourceManager* m_MyResourceManager;

	Frame m_MyFrame;
};