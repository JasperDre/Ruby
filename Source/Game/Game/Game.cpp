#include "GamePCH.h"
#include "Game/Game.h"

#include <filesystem>

#include "InputManager.h"
#include "Controllers/PlayerController.h"
#include "Entities/GameCamera.h"
#include "Entities/Entity.h"
#include "Entities/Player.h"
#include "Entities/UI/UIObject.h"
#include "Events/InputEvent.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/SceneManager.h"
#include "GameplayHelpers/TileMap.h"
#include "GameplayHelpers/TileMapExtras.h"
#include "GameplayHelpers/TileMapOakLab.h"
#include "GameplayHelpers/TileMapPalletTown.h"
#include "GameplayHelpers/TileMapWoods.h"
#include "Mesh/Mesh.h"
#include "Scenes/Scene.h"

static std::string GetFilePath(const std::string& aRootDirectory, const char* aFilename)
{
	std::string path = aRootDirectory;
	path.append(aFilename);
	return path;
}

Game::Game(Framework* pFramework)
	: GameCore(pFramework, new EventManager())
	, m_pShader(nullptr)
	, m_pDebugShader(nullptr)
	, m_TrainerMesh(nullptr)
	, m_TileMesh(nullptr)
	, m_CameraMesh(nullptr)
	, m_UIMesh(nullptr)
	, m_MyResourceManager(nullptr)
	, m_PalletTileMap(nullptr)
	, m_OakLabTileMap(nullptr)
	, m_WoodsTileMap(nullptr)
	, m_ExtrasTileMap(nullptr)
	, myPlayer(nullptr)
	, m_UICanvas(nullptr)
	, m_TrainerCamera(nullptr)
	, m_pPlayerController(nullptr)
	, m_MySceneManager(nullptr)
	, m_Tileset(0)
	, m_OakLabTileset(0)
	, m_Sprites(0)
	, m_WoodsTileset(0)
	, m_ExtrasSet(0)
	, m_BattleScene(0)
{}

Game::~Game()
{
	delete m_MySceneManager;
	delete m_pPlayerController;
	delete m_TrainerCamera;
	delete m_UICanvas;
	delete myPlayer;
	delete m_ExtrasTileMap;
	delete m_WoodsTileMap;
	delete m_OakLabTileMap;
	delete m_PalletTileMap;
	delete m_MyResourceManager;
	delete m_UIMesh;
	delete m_CameraMesh;
	delete m_TileMesh;
	delete m_TrainerMesh;
	delete m_pDebugShader;
	delete m_pShader;
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

	// Create our shaders.
	m_pShader = new ShaderProgram(GetFilePath(rootDirectory, "Data/Shaders/Moving.vert"), GetFilePath(rootDirectory, "Data/Shaders/Moving.frag"));
	m_pDebugShader = new ShaderProgram(GetFilePath(rootDirectory, "Data/Shaders/Color.vert"), GetFilePath(rootDirectory, "Data/Shaders/Color.frag"));

	// Create out meshes.
	m_TrainerMesh = new Mesh();
	m_TrainerMesh->SetShader(m_pShader, m_pDebugShader);

	m_TileMesh = new Mesh();
	m_TileMesh->SetShader(m_pShader, m_pDebugShader);
	m_TileMesh->GenerateTileMesh();

	m_CameraMesh = new Mesh();
	m_CameraMesh->SetShader(m_pShader, m_pDebugShader);

	m_UIMesh = new Mesh();
	m_UIMesh->SetShader(m_pShader, m_pDebugShader);
	m_UIMesh->GenerateTileMesh();

	//Create our Textures
	m_Tileset = GLHelpers::LoadTexture(GetFilePath(rootDirectory, "Data/Textures/TileSet.png"));
	m_OakLabTileset = GLHelpers::LoadTexture(GetFilePath(rootDirectory, "Data/Textures/OakLabTileSet.png"));
	m_Sprites = GLHelpers::LoadTexture(GetFilePath(rootDirectory, "Data/Textures/Player_NPCSprites.png"));
	m_WoodsTileset = GLHelpers::LoadTexture(GetFilePath(rootDirectory, "Data/Textures/WoodsTileSet.png"));
	m_ExtrasSet = GLHelpers::LoadTexture(GetFilePath(rootDirectory, "Data/Textures/ExtrasTileSet.png"));
	m_BattleScene = GLHelpers::LoadTexture(GetFilePath(rootDirectory, "Data/Textures/BattleScene.png"));

	//Create a Resource Manager to parse JSON file and set up frames from sprite sheet
	m_PalletTileMap = new TileMapPalletTown(this, Areas::Area_PalletTown);
	m_OakLabTileMap = new TileMapOakLab(this, Areas::Area_OakLab);
	m_WoodsTileMap = new TileMapWoods(this, Areas::Area_Woods);
	m_ExtrasTileMap = new TileMapExtras(this, Areas::Area_Null);
	m_MyResourceManager = new ResourceManager();

	m_MyResourceManager->UnpackJson(GetFilePath(rootDirectory, "Data/Textures/TileSet.json"), m_PalletTileMap);
	m_MyResourceManager->UnpackJson(GetFilePath(rootDirectory, "Data/Textures/OakLabTileSet.json"), m_OakLabTileMap);
	m_MyResourceManager->UnpackJson(GetFilePath(rootDirectory, "Data/Textures/Player_NPCSprites.json"), m_PalletTileMap);
	m_MyResourceManager->UnpackJson(GetFilePath(rootDirectory, "Data/Textures/WoodsTileSet.json"), m_WoodsTileMap);
	m_MyResourceManager->UnpackJson(GetFilePath(rootDirectory, "Data/Textures/ExtrasTileSet.json"), m_ExtrasTileMap);
	m_MyResourceManager->UnpackJson(GetFilePath(rootDirectory, "Data/Textures/BattleScene.json"), m_ExtrasTileMap);

	m_MyResourceManager->HoldTexture(TextureHandle::TileSet, m_Tileset);
	m_MyResourceManager->HoldTexture(TextureHandle::OakLabTileSet, m_OakLabTileset);
	m_MyResourceManager->HoldTexture(TextureHandle::Player_NPCSprites, m_Sprites);
	m_MyResourceManager->HoldTexture(TextureHandle::ForestTileSet, m_WoodsTileset);

	//Create our game objects
	myPlayer = new Player(m_MyResourceManager, this, m_TrainerMesh, m_Sprites);
	m_UICanvas = new UIObject(m_MyResourceManager, m_ExtrasTileMap, this, m_UIMesh, m_ExtrasSet);


	// Assign our controllers.
	m_pPlayerController = new PlayerController();
	myPlayer->SetPlayerController(m_pPlayerController);

	//Create our player camera
	m_TrainerCamera = new GameCamera(this, m_CameraMesh, 0, myPlayer);
	m_TrainerCamera->SetMyProjection(1 / (aWindowSize.myX / 40));

	//Finally Create our SceneManager and Scenes
	m_MySceneManager = new SceneManager();
	m_MySceneManager->GenerateScenes(this, Areas::Area_PalletTown, m_PalletTileMap, m_MyResourceManager, m_TileMesh, myPlayer, m_Tileset);
	m_MySceneManager->GenerateScenes(this, Areas::Area_OakLab, m_OakLabTileMap, m_MyResourceManager, m_TileMesh, myPlayer, m_OakLabTileset);
	m_MySceneManager->GenerateScenes(this, Areas::Area_Woods, m_WoodsTileMap, m_MyResourceManager, m_TileMesh, myPlayer, m_WoodsTileset);
	m_MySceneManager->SetActiveScene(Areas::Area_PalletTown);

	m_UICanvas->SetPosition(m_TrainerCamera->GetPosition());

	GLHelpers::CheckForGLErrors();
}

void Game::OnEvent(Event* pEvent)
{
	switch (pEvent->GetEventType())
	{
		case EventTypes::EventType_Input:
		{
			m_pPlayerController->OnEvent(pEvent);
			break;
		}
		case EventTypes::EventType_Collision:
		{
			myPlayer->OnEvent(pEvent);
			break;
		}
		case EventTypes::EventType_Door:
		{
			m_MySceneManager->OnEvent(pEvent);
			if (pEvent->GetEventType() != EventTypes::EventType_Input)
			{
				myPlayer->OnEvent(pEvent);
				m_TrainerCamera->OnEvent(pEvent);
			}

			break;
		}
	}
}

void Game::Update(float deltatime)
{
	if (deltatime > 1.0f / 20.0f)
		deltatime = 1.0f / 20.0f;

	Scene* aActiveScene = m_MySceneManager->GetActiveScene();
	aActiveScene->Update(deltatime);

	m_TrainerCamera->Update(deltatime);
	m_TrainerCamera->ClampToPlayer(myPlayer->GetPosition());
	m_UICanvas->SetPosition(m_TrainerCamera->GetCameraPosition());

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

	Scene* aSceneDraw = m_MySceneManager->GetActiveScene();

	// Draw our game objects.
	aSceneDraw->Draw(m_TrainerCamera->GetCameraPosition(), m_TrainerCamera->GetCameraProjection());

	//m_UICanvas->Draw(0, m_TrainerCamera->GetCameraProjection());

	GLHelpers::CheckForGLErrors();
}

TileMap* Game::GetTileMap()
{
	return m_MySceneManager->GetActiveScene()->GetMyTileMap();
}

SceneManager* Game::GetSceneManager()
{
	return m_MySceneManager;
}

ShaderProgram* Game::GetShader()
{
	return m_pShader;
}

ShaderProgram* Game::GetDebugShader()
{
	return m_pDebugShader;
}

Player* Game::GetMyPlayer()
{
	return myPlayer;
}

void Game::SetCameraScreenSize(float width, float height)
{
	aWindowSize = Vector2Float(width, height);

	if (m_TrainerCamera)
		m_TrainerCamera->SetScreenSize(aWindowSize);
}
