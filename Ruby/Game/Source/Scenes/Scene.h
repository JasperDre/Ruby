#pragma once

#include <vector>

class GameCore;
class Mesh;
class ResourceManager;
class TileMap;
class Entity;
class Trainer;

class Scene
{
public:
	Scene(GameCore* myGame, Areas myArea, TileMap* aTileMap, ResourceManager* aResourceManager, Mesh* aMesh, Trainer* aPlayer, Vector2Float aPlayerStartPosition, GLuint aTexture);
	virtual ~Scene() = default;

	virtual void LoadContent() = 0;
	virtual void Update(float delatime) = 0;
	virtual void Draw(Vector2Float camPos, Vector2Float camProjection) = 0;
	virtual void OnEvent(Event* anEvent) = 0;
	virtual void OnIsActive() = 0;
	virtual void Unload() = 0;
	virtual void Reload() = 0;

	virtual void SetIsActive(bool setActive);
	virtual void SetPlayerStart(Vector2Float PlayerLastPos) { m_pMyPlayerStart = PlayerLastPos; }

	[[nodiscard]] virtual bool GetIsActive() const { return m_Active; }
	[[nodiscard]] virtual Areas GetMyArea() const { return m_MyArea; }
	[[nodiscard]] virtual Trainer* GetMyPlayer() const { return m_pMyTrainer; }
	[[nodiscard]] virtual TileMap* GetMyTileMap() const { return m_MyTileMap;}
	[[nodiscard]] virtual Vector2Float GetPlayerStart() const { return m_pMyPlayerStart; }

protected:
	std::vector<Entity*> m_MyGameObjects;
	Areas m_MyArea;
	Vector2Float m_pMyPlayerStart;
	TileMap* m_MyTileMap;
	GameCore* m_pMyGame;
	ResourceManager* m_pMyResourceManager;
	Mesh* m_pMyMesh;
	Trainer* m_pMyTrainer;
	GLuint m_pMyTexture;
	bool m_Active;
};