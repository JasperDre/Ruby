#pragma once

class Scene;
class Mesh;
class TileMap;
class TileMapWoods;
class Trainer;
class PettleburgWoodsMap;


class PettleBurgWoods : public Scene
{

public:
	PettleBurgWoods(GameCore* myGame, Areas myArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Trainer* aPlayer, GLuint aTexture);
	~PettleBurgWoods();

	void LoadContent();

	void Update(float deltatime);

	void Draw(vec2 camPos, vec2 camProjection) override;

	virtual TileMap* GetMyTileMap() override;

	virtual void OnIsActive() override;

	virtual void Reload() override;

	virtual void Unload() override;

private:

	TileMap* m_MyTileMap;

	Trainer* m_MyTrainer;
	PettleburgWoodsMap* m_MyPettleburgWoods;
	vec2 PlayerSavedPosition;

};