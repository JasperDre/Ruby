#pragma once

#include "GameCore/GameCore.h"

class Mesh;
class Entity;
class ResourceManager;
class TileMap;
class TileMapPalletTown;
class TileMapOakLab;
class TileMapExtras;
class Player;
class UIObject;
class PlayerController;
class GameCamera;
class SceneManager;

class Game : public GameCore
{
public:
	Game(Framework* pFramework);
	~Game() override;

	void OnSurfaceChanged(int width, int height) override;
	void LoadContent() override;

	void OnEvent(Event* pEvent) override;
	void Update(float deltatime) override;
	void Draw() override;

	void SetCameraScreenSize(float width, float height);

	[[nodiscard]] TileMap* GetTileMap() const override;
	[[nodiscard]] SceneManager* GetSceneManager() const override;
	[[nodiscard]] ShaderProgram* GetShader() const override;
	[[nodiscard]] ShaderProgram* GetDebugShader() const override;
	[[nodiscard]] Player* GetMyPlayer() const override;

protected:
	Vector2Float myWindowSize;
	ShaderProgram* myShader;
	ShaderProgram* myDebugShader;
	Mesh* myPlayerMesh;
	Mesh* myTileMesh;
	Mesh* myCameraMesh;
	Mesh* myUIMesh;
	ResourceManager* myResourceManager;
	TileMap* myPalletTileMap;
	TileMap* myOakLabTileMap;
	TileMap* myWoodsTileMap;
	TileMap* myExtrasTileMap;
	Player* myPlayer;
	UIObject* myUICanvas;
	GameCamera* myPlayerCamera;
	PlayerController* myPlayerController;
	SceneManager* mySceneManager;
	GLuint myTilesetTextureIdentifier;
	GLuint myOakLabTilesetTextureIdentifier;
	GLuint mySpritesTextureIdentifier;
	GLuint myWoodsTilesetTextureIdentifier;
	GLuint myExtrasSetTextureIdentifier;
	GLuint myBattleSceneTextureIdentifier;
};
