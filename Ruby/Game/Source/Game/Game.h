#pragma once

#include "GameCore/GameCore.h"

class Mesh;
class Entity;
class ResourceManager;
class TileMap;
class TileMapPalletTown;
class TileMapOakLab;
class TileMapExtras;
class Trainer;
class UIObject;
class PlayerController;
class GameCamera;
class SceneManager;

class Game : public GameCore
{
public:
	static constexpr int Game_WORLD_SIZE_X = 50;
	static constexpr int Game_WORLD_SIZE_Y = 50;

	Game(Framework* pFramework);
	~Game() override;

	void OnSurfaceChanged(unsigned int width, unsigned int height) override;
	void LoadContent() override;

	void OnEvent(Event* pEvent) override;
	void Update(float deltatime) override;
	void Draw() override;

	TileMap* GetTileMap() override;
	SceneManager* GetSceneManager() override;
	ShaderProgram* GetShader() override;
	ShaderProgram* GetDebugShader() override;
	Trainer* GetMyPlayer() override;

	void SetCameraScreenSize(float width, float height);
	void CheckForCollisions();

protected:
	ShaderProgram* m_pShader;
	ShaderProgram* m_pDebugShader;
	Mesh* m_TrainerMesh;
	Mesh* m_TileMesh;
	Mesh* m_CameraMesh;
	Mesh* m_UIMesh;
	ResourceManager* m_MyResourceManager;
	TileMap* m_PalletTileMap;
	TileMap* m_OakLabTileMap;
	TileMap* m_WoodsTileMap;
	TileMap* m_ExtrasTileMap;
	Trainer* m_Trainer;
	UIObject* m_UICanvas;
	GameCamera* m_TrainerCamera;
	PlayerController* m_pPlayerController;
	SceneManager* m_MySceneManager;
	Vector2Float aWindowSize;
	GLuint m_Tileset;
	GLuint m_OakLabTileset;
	GLuint m_Sprites;
	GLuint m_WoodsTileset;
	GLuint m_ExtrasSet;
	GLuint m_BattleScene;
};
