#include "Game/Game.h"

#include <filesystem>

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

static std::string GetFilePath(const std::string& aRootDirectory, const char* aFilename)
{
	std::string path = aRootDirectory;
	path.append(aFilename);
	return path;
}

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
{}

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
	unsigned char* iconSource = GLHelpers::LoadImage(GetFilePath(rootDirectory, "Data/Textures/Icon.png"), iconWidth, iconHeight, iconNumberOfComponents);
	GetFramework()->SetWindowIcon(iconSource, iconWidth, iconHeight);

	TilemapLoader::Load(GetFilePath(rootDirectory, "Data/Tilemaps/OakPokemonResearchLab.tmx"), GetFilePath(rootDirectory, "Data/Tilemaps/OakPokemonResearchLab.tsx"));

	// Create our shaders.
	myShader = new ShaderProgram(GetFilePath(rootDirectory, "Data/Shaders/Moving.vert"), GetFilePath(rootDirectory, "Data/Shaders/Moving.frag"));
	myDebugShader = new ShaderProgram(GetFilePath(rootDirectory, "Data/Shaders/Color.vert"), GetFilePath(rootDirectory, "Data/Shaders/Color.frag"));

	// Create out meshes.
	myPlayerMesh = new Mesh();
	myPlayerMesh->SetShader(myShader, myDebugShader);

	myTileMesh = new Mesh();
	myTileMesh->SetShader(myShader, myDebugShader);
	myTileMesh->GenerateTileMesh();

	myCameraMesh = new Mesh();
	myCameraMesh->SetShader(myShader, myDebugShader);

	myUIMesh = new Mesh();
	myUIMesh->SetShader(myShader, myDebugShader);
	myUIMesh->GenerateTileMesh();

	//Create our Textures
	myTilesetTextureIdentifier = GLHelpers::LoadTexture(GetFilePath(rootDirectory, "Data/Textures/TileSet.png"));
	myOakLabTilesetTextureIdentifier = GLHelpers::LoadTexture(GetFilePath(rootDirectory, "Data/Textures/OakLabTileSet.png"));
	mySpritesTextureIdentifier = GLHelpers::LoadTexture(GetFilePath(rootDirectory, "Data/Textures/Player_NPCSprites.png"));
	myWoodsTilesetTextureIdentifier = GLHelpers::LoadTexture(GetFilePath(rootDirectory, "Data/Textures/WoodsTileSet.png"));
	myExtrasSetTextureIdentifier = GLHelpers::LoadTexture(GetFilePath(rootDirectory, "Data/Textures/ExtrasTileSet.png"));
	myBattleSceneTextureIdentifier = GLHelpers::LoadTexture(GetFilePath(rootDirectory, "Data/Textures/BattleScene.png"));

	//Create a Resource Manager to parse JSON file and set up frames from sprite sheet
	myPalletTileMap = new TileMapPalletTown(this, Areas::Area_PalletTown);
	myOakLabTileMap = new TileMapOakLab(this, Areas::Area_OakLab);
	myWoodsTileMap = new TileMapWoods(this, Areas::Area_Woods);
	myExtrasTileMap = new TileMapExtras(this, Areas::Area_Null);
	myResourceManager = new ResourceManager();

	myResourceManager->UnpackJson(GetFilePath(rootDirectory, "Data/Textures/TileSet.json"), myPalletTileMap);
	myResourceManager->UnpackJson(GetFilePath(rootDirectory, "Data/Textures/OakLabTileSet.json"), myOakLabTileMap);
	myResourceManager->UnpackJson(GetFilePath(rootDirectory, "Data/Textures/Player_NPCSprites.json"), myPalletTileMap);
	myResourceManager->UnpackJson(GetFilePath(rootDirectory, "Data/Textures/WoodsTileSet.json"), myWoodsTileMap);
	myResourceManager->UnpackJson(GetFilePath(rootDirectory, "Data/Textures/ExtrasTileSet.json"), myExtrasTileMap);
	myResourceManager->UnpackJson(GetFilePath(rootDirectory, "Data/Textures/BattleScene.json"), myExtrasTileMap);

	myResourceManager->HoldTexture(TextureHandle::TileSet, myTilesetTextureIdentifier);
	myResourceManager->HoldTexture(TextureHandle::OakLabTileSet, myOakLabTilesetTextureIdentifier);
	myResourceManager->HoldTexture(TextureHandle::Player_NPCSprites, mySpritesTextureIdentifier);
	myResourceManager->HoldTexture(TextureHandle::ForestTileSet, myWoodsTilesetTextureIdentifier);

	//Create our game objects
	myPlayer = new Player(myResourceManager, this, myPlayerMesh, mySpritesTextureIdentifier);
	myUICanvas = new UIObject(myResourceManager, myExtrasTileMap, this, myUIMesh, myExtrasSetTextureIdentifier);

	// Assign our controllers.
	myPlayerController = new PlayerController();
	myPlayer->SetPlayerController(myPlayerController);

	//Create our player camera
	myPlayerCamera = new GameCamera(this, myCameraMesh, 0, myPlayer);
	myPlayerCamera->SetMyProjection(1.0f / (myWindowSize.myX / 40.0f));

	//Finally Create our SceneManager and Scenes
	mySceneManager = new SceneManager();
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
	// Setup the values we will clear to, then actually clear the color and depth buffers.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // black
#if WIN32
	glClearDepth(1); // 1 is maximum depth
#endif
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Scene* aSceneDraw = mySceneManager->GetActiveScene();

	// Draw our game objects.
	aSceneDraw->Draw(myPlayerCamera->GetCameraPosition(), myPlayerCamera->GetCameraProjection());

	myUICanvas->Draw(0, myPlayerCamera->GetCameraProjection());

	GLHelpers::CheckForGLErrors();
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
