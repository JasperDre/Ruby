#pragma once

#include "GameCore/GameCore.h"
#include "Math/Vector2Float.h"

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
	Game(Framework* aFramework);
	~Game() override;

	void OnSurfaceChanged(int width, int height) override;
	void LoadContent() override;

	void OnEvent(Event* pEvent) override;
	void Update(float deltatime) override;
	void Draw() override;
	void DrawImGUI() override;

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
	unsigned int myTilesetTextureIdentifier;
	unsigned int myOakLabTilesetTextureIdentifier;
	unsigned int mySpritesTextureIdentifier;
	unsigned int myWoodsTilesetTextureIdentifier;
	unsigned int myExtrasSetTextureIdentifier;
	unsigned int myBattleSceneTextureIdentifier;
};
