#include "Game/Game.h"

#include <filesystem>

#include "imgui.h"
#include "Controllers/PlayerController.h"
#include "Entities/Entity.h"
#include "Entities/GameCamera.h"
#include "Entities/Player.h"
#include "Entities/UI/UIObject.h"
#include "Events/EventManager.h"
#include "Events/InputEvent.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/SceneManager.h"
#include "GameplayHelpers/TileMap.h"
#include "GameplayHelpers/TileMapExtras.h"
#include "GameplayHelpers/TileMapOakLab.h"
#include "GameplayHelpers/TileMapPalletTown.h"
#include "GameplayHelpers/TileMapWoods.h"
#include "GL/GLHelpers.h"
#include "Input/InputManager.h"
#include "Mesh/Mesh.h"
#include "Scenes/Scene.h"
#include "Utility/ShaderProgram.h"
#include "Win32/FrameworkMain.h"
#include "TilemapLoader.h"

Game::Game(Framework* aFramework)
	: GameCore(aFramework, new EventManager())
	, myShader(nullptr)
	, myDebugShader(nullptr)
	, myPlayerMesh(nullptr)
	, myTileMesh(nullptr)
	, myCameraMesh(nullptr)
	, myUIMesh(nullptr)
	, myResourceManager(nullptr)
	, myPalletTileMap(nullptr)
	, myOakLabTileMap(nullptr)
	, myWoodsTileMap(nullptr)
	, myExtrasTileMap(nullptr)
	, myPlayer(nullptr)
	, myUICanvas(nullptr)
	, myPlayerCamera(nullptr)
	, myPlayerController(nullptr)
	, mySceneManager(nullptr)
	, myTilesetTextureIdentifier(0)
	, myOakLabTilesetTextureIdentifier(0)
	, mySpritesTextureIdentifier(0)
	, myWoodsTilesetTextureIdentifier(0)
	, myExtrasSetTextureIdentifier(0)
	, myBattleSceneTextureIdentifier(0)
{
	myResourceManager = new ResourceManager();
	myShader = new ShaderProgram();
	myDebugShader = new ShaderProgram();
	mySceneManager = new SceneManager();
	myPlayerController = new PlayerController();
	myPlayerMesh = new Mesh();
	myTileMesh = new Mesh();
	myCameraMesh = new Mesh();
	myUIMesh = new Mesh();
	myPalletTileMap = new TileMapPalletTown(this, Areas::Area_PalletTown);
	myOakLabTileMap = new TileMapOakLab(this, Areas::Area_OakLab);
	myWoodsTileMap = new TileMapWoods(this, Areas::Area_Woods);
	myExtrasTileMap = new TileMapExtras(this, Areas::Area_Null);
}

Game::~Game()
{
	delete mySceneManager;
	delete myPlayerController;
	delete myPlayerCamera;
	delete myUICanvas;
	delete myPlayer;
	delete myExtrasTileMap;
	delete myWoodsTileMap;
	delete myOakLabTileMap;
	delete myPalletTileMap;
	delete myResourceManager;
	delete myUIMesh;
	delete myCameraMesh;
	delete myTileMesh;
	delete myPlayerMesh;
	delete myDebugShader;
	delete myShader;
}

void Game::OnSurfaceChanged(int width, int height)
{
	//Keep ratio of 1:1
	if (width > height)
	{
		const GLint newWidth = height;
		const GLint centerOffset = width / 4;
		glViewport(centerOffset, 0, newWidth, height);
	}
	else
	{
		//open viewport of size if aspect ratio is already 1:1
		glViewport(0, 0, width, height);
	}

	SetCameraScreenSize(static_cast<float>(width), static_cast<float>(height));
}

void Game::LoadContent()
{
	std::string rootDirectory = std::filesystem::current_path().generic_string();
	rootDirectory += "/../../../";

	int iconWidth = 0;
	int iconHeight = 0;
	int iconNumberOfComponents = 0;
	unsigned char* iconSource = GLHelpers::LoadImage("Data/Textures/Icon.png", iconWidth, iconHeight, iconNumberOfComponents);
	GetFramework()->SetWindowIcon(iconSource, iconWidth, iconHeight);

	const std::vector<TilemapLoader::Tile> tiles = TilemapLoader::Load("Data/Tilemaps/OakPokemonResearchLabTilemap.json");

	myShader->LoadShaders("Data/Shaders/Moving.vert", "Data/Shaders/Moving.frag");
	myDebugShader->LoadShaders("Data/Shaders/Color.vert", "Data/Shaders/Color.frag");

	myPlayerMesh->SetShaders(myShader, myDebugShader);

	myTileMesh->SetShaders(myShader, myDebugShader);
	myTileMesh->GenerateTileMesh();

	myCameraMesh->SetShaders(myShader, myDebugShader);

	myUIMesh->SetShaders(myShader, myDebugShader);
	myUIMesh->GenerateTileMesh();

	myTilesetTextureIdentifier = GLHelpers::LoadTexture("Data/Textures/TileSet.png");
	myOakLabTilesetTextureIdentifier = GLHelpers::LoadTexture("Data/Textures/OakLabTileSet.png");
	mySpritesTextureIdentifier = GLHelpers::LoadTexture("Data/Textures/Player_NPCSprites.png");
	myWoodsTilesetTextureIdentifier = GLHelpers::LoadTexture("Data/Textures/WoodsTileSet.png");
	myExtrasSetTextureIdentifier = GLHelpers::LoadTexture("Data/Textures/ExtrasTileSet.png");
	myBattleSceneTextureIdentifier = GLHelpers::LoadTexture("Data/Textures/BattleScene.png");

	myResourceManager->UnpackJson("Data/Textures/TileSet.json", myPalletTileMap);
	myResourceManager->UnpackJson("Data/Textures/OakLabTileSet.json", myOakLabTileMap);
	myResourceManager->UnpackJson("Data/Textures/Player_NPCSprites.json", myPalletTileMap);
	myResourceManager->UnpackJson("Data/Textures/WoodsTileSet.json", myWoodsTileMap);
	myResourceManager->UnpackJson("Data/Textures/ExtrasTileSet.json", myExtrasTileMap);
	myResourceManager->UnpackJson("Data/Textures/BattleScene.json", myExtrasTileMap);

	myResourceManager->HoldTexture(TextureHandle::TileSet, myTilesetTextureIdentifier);
	myResourceManager->HoldTexture(TextureHandle::OakLabTileSet, myOakLabTilesetTextureIdentifier);
	myResourceManager->HoldTexture(TextureHandle::Player_NPCSprites, mySpritesTextureIdentifier);
	myResourceManager->HoldTexture(TextureHandle::ForestTileSet, myWoodsTilesetTextureIdentifier);

	myPlayer = new Player(myResourceManager, this, myPlayerMesh, mySpritesTextureIdentifier);
	myUICanvas = new UIObject(myResourceManager, myExtrasTileMap, this, myUIMesh, myExtrasSetTextureIdentifier);

	myPlayer->SetPlayerController(myPlayerController);

	myPlayerCamera = new GameCamera(this, myCameraMesh, 0, myPlayer);
	myPlayerCamera->SetMyProjection(1.0f / (myWindowSize.myX / 40.0f));

	mySceneManager->GenerateScenes(this, Areas::Area_PalletTown, myPalletTileMap, myResourceManager, myTileMesh, myPlayer, myTilesetTextureIdentifier);
	mySceneManager->GenerateScenes(this, Areas::Area_OakLab, myOakLabTileMap, myResourceManager, myTileMesh, myPlayer, myOakLabTilesetTextureIdentifier);
	mySceneManager->GenerateScenes(this, Areas::Area_Woods, myWoodsTileMap, myResourceManager, myTileMesh, myPlayer, myWoodsTilesetTextureIdentifier);
	mySceneManager->SetActiveScene(Areas::Area_PalletTown);

	myUICanvas->SetPosition(myPlayerCamera->GetPosition());

	GLHelpers::CheckForGLErrors();
}

void Game::OnEvent(Event* pEvent)
{
	switch (pEvent->GetEventType())
	{
		case EventTypes::EventType_Input:
		{
			myPlayerController->OnEvent(pEvent);
			break;
		}
		case EventTypes::EventType_Collision:
		{
			myPlayer->OnEvent(pEvent);
			break;
		}
		case EventTypes::EventType_Door:
		{
			mySceneManager->OnEvent(pEvent);
			if (pEvent->GetEventType() != EventTypes::EventType_Input)
			{
				myPlayer->OnEvent(pEvent);
				myPlayerCamera->OnEvent(pEvent);
			}

			break;
		}
	}
}

void Game::Update(float deltatime)
{
	if (deltatime > 1.0f / 60.0f)
		deltatime = 1.0f / 60.0f;

	Scene* aActiveScene = mySceneManager->GetActiveScene();
	aActiveScene->Update(deltatime);

	myPlayerCamera->Update(deltatime);
	myPlayerCamera->ClampToPlayer(myPlayer->GetPosition());
	myUICanvas->SetPosition(myPlayerCamera->GetCameraPosition());

	for (const Keys key : InputManager::GetInstance().GetPressedKeysThisFrame())
	{
		Event* pEvent = new InputEvent(key, false);
		GetEventManager()->QueueEvent(pEvent);
	}

	for (const Keys key : InputManager::GetInstance().GetReleasedKeysThisFrame())
	{
		Event* pEvent = new InputEvent(key, true);
		GetEventManager()->QueueEvent(pEvent);
	}

	InputManager::GetInstance().ClearKeyActionsThisFrame();
}

void Game::Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1); // 1 is maximum depth
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Scene* aSceneDraw = mySceneManager->GetActiveScene();
	aSceneDraw->Draw(myPlayerCamera->GetCameraPosition(), myPlayerCamera->GetCameraProjection());

	myUICanvas->Draw(0, myPlayerCamera->GetCameraProjection());

	GLHelpers::CheckForGLErrors();
}

void Game::DrawImGUI()
{
	ImGui::Begin("ImGUI");
	ImGui::Text("Hello world!");
	ImGui::End();
}

TileMap* Game::GetTileMap() const
{
	return mySceneManager->GetActiveScene()->GetMyTileMap();
}

SceneManager* Game::GetSceneManager() const
{
	return mySceneManager;
}

ShaderProgram* Game::GetShader() const
{
	return myShader;
}

ShaderProgram* Game::GetDebugShader() const
{
	return myDebugShader;
}

Player* Game::GetMyPlayer() const
{
	return myPlayer;
}

void Game::SetCameraScreenSize(float width, float height)
{
	myWindowSize = Vector2Float(width, height);

	if (myPlayerCamera)
		myPlayerCamera->SetScreenSize(myWindowSize);
}
