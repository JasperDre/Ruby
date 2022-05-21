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
	GameCore(Framework* aFramework, EventManager* anEventManager);
	virtual ~GameCore();

	virtual void OnSurfaceChanged(int aWidth, int aHeight) = 0;
	virtual void LoadContent() = 0;

	virtual void OnEvent(Event* anEvent) = 0;
	virtual void Update(float aDeltaTime) = 0;
	virtual void Draw() = 0;
	virtual void DrawImGUI(float aDeltaTime) = 0;

	[[nodiscard]] virtual TileMap* GetTileMap() const = 0;
	[[nodiscard]] virtual SceneManager* GetSceneManager() const = 0;
	[[nodiscard]] virtual ShaderProgram* GetShader() const = 0;
	[[nodiscard]] virtual ShaderProgram* GetDebugShader() const = 0;
	[[nodiscard]] virtual Player* GetMyPlayer() const = 0;
	[[nodiscard]] virtual Framework* GetFramework() const { return myFramework; }
	[[nodiscard]] virtual EventManager* GetEventManager() const { return myEventManager; }

protected:
	Framework* myFramework;
	EventManager* myEventManager;
};