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
#include "GameplayHelpers/TileMapRoute1.h"
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
	, myRoute1TileMap(nullptr)
	, myExtrasTileMap(nullptr)
	, myPlayer(nullptr)
	, myUICanvas(nullptr)
	, myPlayerCamera(nullptr)
	, myPlayerController(nullptr)
	, mySceneManager(nullptr)
	, myDeltaTimeSum(0.0f)
	, myDeltaTimeIndex(0)
	, myTilesetTextureIdentifier(0)
	, myOakLabTilesetTextureIdentifier(0)
	, mySpritesTextureIdentifier(0)
	, myWoodsTilesetTextureIdentifier(0)
	, myExtrasSetTextureIdentifier(0)
	, myBattleSceneTextureIdentifier(0)
{
	for (float& deltaTime : myDeltaTimes)
		deltaTime = 0.0f;

	myResourceManager = new ResourceManager();
	myShader = new ShaderProgram();
	myDebugShader = new ShaderProgram();
	mySceneManager = new SceneManager();
	myPlayerController = new PlayerController();
	myPlayerMesh = new Mesh();
	myTileMesh = new Mesh();
	myCameraMesh = new Mesh();
	myUIMesh = new Mesh();
	myPalletTileMap = new TileMapPalletTown(this, Area::PalletTown);
	myOakLabTileMap = new TileMapOakLab(this, Area::OakLab);
	myRoute1TileMap = new TileMapRoute1(this, Area::Woods);
	myExtrasTileMap = new TileMapExtras(this, Area::Null);
}

Game::~Game()
{
	delete mySceneManager;
	delete myPlayerController;
	delete myPlayerCamera;
	delete myUICanvas;
	delete myPlayer;
	delete myExtrasTileMap;
	delete myRoute1TileMap;
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

void Game::OnSurfaceChanged(int aWidth, int aHeight)
{
	//Keep ratio of 1:1
	if (aWidth > aHeight)
	{
		const GLint newWidth = aHeight;
		const GLint centerOffset = aWidth / 4;
		glViewport(centerOffset, 0, newWidth, aHeight);
	}
	else
	{
		//open viewport of size if aspect ratio is already 1:1
		glViewport(0, 0, aWidth, aHeight);
	}

	SetCameraScreenSize(static_cast<float>(aWidth), static_cast<float>(aHeight));
}

void Game::LoadContent()
{
	std::string rootDirectory = std::filesystem::current_path().generic_string();
	rootDirectory += "/../../../";

	int iconWidth = 0;
	int iconHeight = 0;
	int iconNumberOfComponents = 0;
	unsigned char* iconSource = GLHelpers::LoadImage("Data/Textures/Icon.png", iconWidth, iconHeight, iconNumberOfComponents);
	myFramework->SetWindowIcon(iconSource, iconWidth, iconHeight);

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

	myPalletTileMap->LoadTileTypeMap("Data/TileTypes/PalletTownTileTypes.json");
	myRoute1TileMap->LoadTileTypeMap("Data/TileTypes/Route1TileTypes.json");

	myResourceManager->UnpackJson("Data/Textures/TileSet.json", myPalletTileMap);
	myResourceManager->UnpackJson("Data/Textures/OakLabTileSet.json", myOakLabTileMap);
	myResourceManager->UnpackJson("Data/Textures/Player_NPCSprites.json", myPalletTileMap);
	myResourceManager->UnpackJson("Data/Textures/WoodsTileSet.json", myRoute1TileMap);
	myResourceManager->UnpackJson("Data/Textures/ExtrasTileSet.json", myExtrasTileMap);
	myResourceManager->UnpackJson("Data/Textures/BattleScene.json", myExtrasTileMap);

	myResourceManager->HoldTexture(TextureHandle::TileSet, myTilesetTextureIdentifier);
	myResourceManager->HoldTexture(TextureHandle::OakLabTileSet, myOakLabTilesetTextureIdentifier);
	myResourceManager->HoldTexture(TextureHandle::PlayerNPCSprites, mySpritesTextureIdentifier);
	myResourceManager->HoldTexture(TextureHandle::Route1TileSet, myWoodsTilesetTextureIdentifier);

	myPlayer = new Player(myResourceManager, this, myPlayerMesh, mySpritesTextureIdentifier);
	myUICanvas = new UIObject(myResourceManager, myExtrasTileMap, this, myUIMesh, myExtrasSetTextureIdentifier);

	myPlayer->SetPlayerController(myPlayerController);

	myPlayerCamera = new GameCamera(this, myCameraMesh, 0, myPlayer);
	myPlayerCamera->SetProjection(1.0f / (myWindowSize.myX / 40.0f));

	mySceneManager->GenerateScenes(this, Area::PalletTown, myPalletTileMap, myResourceManager, myTileMesh, myPlayer, myTilesetTextureIdentifier);
	mySceneManager->GenerateScenes(this, Area::OakLab, myOakLabTileMap, myResourceManager, myTileMesh, myPlayer, myOakLabTilesetTextureIdentifier);
	mySceneManager->GenerateScenes(this, Area::Woods, myRoute1TileMap, myResourceManager, myTileMesh, myPlayer, myWoodsTilesetTextureIdentifier);
	mySceneManager->SetActiveScene(Area::PalletTown);

	myUICanvas->SetPosition(myPlayerCamera->GetPosition());

	GLHelpers::CheckForGLErrors();
}

void Game::OnEvent(Event* anEvent)
{
	switch (anEvent->GetEventType())
	{
		case EventTypes::EventType_Input:
		{
			myPlayerController->OnEvent(anEvent);
			break;
		}
		case EventTypes::EventType_Collision:
		{
			myPlayer->OnEvent(anEvent);
			break;
		}
		case EventTypes::EventType_Door:
		{
			mySceneManager->OnEvent(anEvent);
			if (anEvent->GetEventType() != EventTypes::EventType_Input)
			{
				myPlayer->OnEvent(anEvent);
				myPlayerCamera->OnEvent(anEvent);
			}

			break;
		}
	}
}

void Game::Update(float aDeltaTime)
{
	if (aDeltaTime > 1.0f / 60.0f)
		aDeltaTime = 1.0f / 60.0f;

	Scene* activeScene = mySceneManager->GetActiveScene();
	activeScene->Update(aDeltaTime);

	myPlayerCamera->Update(aDeltaTime);
	myPlayerCamera->ClampToPlayer(myPlayer->GetPosition());
	myUICanvas->SetPosition(myPlayerCamera->GetCameraPosition());

	for (const Keys key : InputManager::GetInstance().GetPressedKeysThisFrame())
		myEventManager->QueueEvent(new InputEvent(key, false));

	for (const Keys key : InputManager::GetInstance().GetReleasedKeysThisFrame())
		myEventManager->QueueEvent(new InputEvent(key, true));

	InputManager::GetInstance().ClearKeyActionsThisFrame();
}

void Game::Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1); // 1 is maximum depth
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Scene* activeScene = mySceneManager->GetActiveScene();
	activeScene->Draw(myPlayerCamera->GetCameraPosition(), myPlayerCamera->GetProjection());

	myUICanvas->Draw(0, myPlayerCamera->GetProjection());

	GLHelpers::CheckForGLErrors();
}

void Game::DrawImGUI(float aDeltaTime)
{
	ImGui::Begin("Debug");
	ImGui::SetNextItemOpen(true);
	if (ImGui::TreeNode("Stats"))
	{
		const float averageFrameTime = GetAverageDeltaTime(aDeltaTime);
		ImGui::Text("Average DeltaTime: %0.5f", averageFrameTime);
		ImGui::Text("Average FPS: %0.f", (1.0f / averageFrameTime));
		ImGui::TreePop();
	}

	ImGui::SetNextItemOpen(true);
	if (ImGui::TreeNode("Scene"))
	{
		const Scene* activeScene = mySceneManager->GetActiveScene();
		ImGui::Text("Area: %s", AreaToString(activeScene->GetArea()));
		ImGui::TreePop();
	}

	ImGui::SetNextItemOpen(true);
	if (ImGui::TreeNode("Player"))
	{
		const Vector2Float playerPosition = myPlayer->GetPosition();
		ImGui::Text("Position: %0.1f %0.1f", playerPosition.myX, playerPosition.myY);
		ImGui::TreePop();
	}

	ImGui::SetNextItemOpen(true);
	if (ImGui::TreeNode("Camera"))
	{
		const Vector2Float cameraPosition = myPlayerCamera->GetCameraPosition();
		ImGui::Text("Position: %0.1f %0.1f", cameraPosition.myX, cameraPosition.myY);
		const Vector2Float projection = myPlayerCamera->GetProjection();
		ImGui::Text("Projection: %0.1f %0.1f", projection.myX, projection.myY);
		const Vector2Float min = myPlayerCamera->GetMin();
		ImGui::Text("Min: %0.1f %0.1f", min.myX, min.myY);
		const Vector2Float max = myPlayerCamera->GetMax();
		ImGui::Text("Max: %0.1f %0.1f", max.myX, max.myY);
		const Vector2Float offset = myPlayerCamera->GetOffset();
		ImGui::Text("Offset: %0.1f %0.1f", offset.myX, offset.myY);
		ImGui::Text("Is in transition: %s", myPlayerCamera->IsInTransition() ? "True" : "False");
		ImGui::TreePop();
	}

	ImGui::SetNextItemOpen(true);
	if (ImGui::TreeNode("Resources"))
	{
		ImGui::Text("Number of textures: %i", myResourceManager->GetTextures().size());
		ImGui::TreePop();
	}

	ImGui::SetNextItemOpen(true);
	if (ImGui::TreeNode("Meshes"))
	{
		if (ImGui::TreeNode("Player"))
		{
			ImGui::Text("VBO: %u", myPlayerMesh->GetVBOIdentifier());
			ImGui::Text("Texture identifier: %i", myPlayerMesh->GetTetureIdentifier());
			ImGui::Text("Number of vertices: %i", myPlayerMesh->GetNumberOfVerticesIdentifier());
			ImGui::Text("Number of canvas vertices: %i", myPlayerMesh->GetCanvasVertices().size());
			ImGui::Text("Width: %0.1f", myPlayerMesh->GetWidth());
			ImGui::Text("Height: %0.1f", myPlayerMesh->GetHeight());
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Tile"))
		{
			ImGui::Text("VBO: %u", myTileMesh->GetVBOIdentifier());
			ImGui::Text("Texture identifier: %i", myTileMesh->GetTetureIdentifier());
			ImGui::Text("Number of vertices: %i", myTileMesh->GetNumberOfVerticesIdentifier());
			ImGui::Text("Number of canvas vertices: %i", myTileMesh->GetCanvasVertices().size());
			ImGui::Text("Width: %0.1f", myTileMesh->GetWidth());
			ImGui::Text("Height: %0.1f", myTileMesh->GetHeight());
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("Camera"))
		{
			ImGui::Text("VBO: %u", myCameraMesh->GetVBOIdentifier());
			ImGui::Text("Texture identifier: %i", myCameraMesh->GetTetureIdentifier());
			ImGui::Text("Number of vertices: %i", myCameraMesh->GetNumberOfVerticesIdentifier());
			ImGui::Text("Number of canvas vertices: %i", myCameraMesh->GetCanvasVertices().size());
			ImGui::Text("Width: %0.1f", myCameraMesh->GetWidth());
			ImGui::Text("Height: %0.1f", myCameraMesh->GetHeight());
			ImGui::TreePop();
		}

		if (ImGui::TreeNode("UI"))
		{
			ImGui::Text("VBO: %u", myUIMesh->GetVBOIdentifier());
			ImGui::Text("Texture identifier: %i", myUIMesh->GetTetureIdentifier());
			ImGui::Text("Number of vertices: %i", myUIMesh->GetNumberOfVerticesIdentifier());
			ImGui::Text("Number of canvas vertices: %i", myUIMesh->GetCanvasVertices().size());
			ImGui::Text("Width: %0.1f", myUIMesh->GetWidth());
			ImGui::Text("Height: %0.1f", myUIMesh->GetHeight());
			ImGui::TreePop();
		}
		
		ImGui::TreePop();
	}

	ImGui::End();
}

TileMap* Game::GetTileMap() const
{
	return mySceneManager->GetActiveScene()->GetTilemap();
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

float Game::GetAverageDeltaTime(float aCurrentDeltaTime)
{
	myDeltaTimeSum -= myDeltaTimes[myDeltaTimeIndex]; // Subtract value falling off
	myDeltaTimeSum += aCurrentDeltaTime;
	myDeltaTimes[myDeltaTimeIndex] = aCurrentDeltaTime; // Save new value so it can be subtracted later
	myDeltaTimeIndex = (myDeltaTimeIndex + 1) % myDeltaTimes.size();

	return (myDeltaTimeSum / static_cast<float>(myDeltaTimes.size()));
}

void Game::SetCameraScreenSize(float aWidth, float aHeight)
{
	myWindowSize = Vector2Float(aWidth, aHeight);

	if (myPlayerCamera)
		myPlayerCamera->SetScreenSize(myWindowSize);
}
