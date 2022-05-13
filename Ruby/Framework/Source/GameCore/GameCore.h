#pragma once

class Framework;
class Event;
class EventManager;
class TileMap;
class SceneManager;
class ShaderProgram;
class Player;

class GameCore
{
public:
	GameCore(Framework* pFramework, EventManager* pEventManager);
	virtual ~GameCore();

	virtual void OnSurfaceChanged(unsigned int width, unsigned int height) = 0;
	virtual void LoadContent() = 0;

	virtual void OnEvent(Event* pEvent) = 0;
	virtual void Update(float deltatime) = 0;
	virtual void Draw() = 0;

	virtual TileMap* GetTileMap() = 0;
	virtual SceneManager* GetSceneManager() = 0;
	virtual ShaderProgram* GetShader() = 0;
	virtual ShaderProgram* GetDebugShader() = 0;

	virtual Player* GetMyPlayer() = 0;

	[[nodiscard]] Framework* GetFramework() const { return m_pFramework; }
	[[nodiscard]] EventManager* GetEventManager() const { return m_pEventManager; }

protected:
	Framework* m_pFramework;
	EventManager* m_pEventManager;
};