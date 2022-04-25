#include "GamePCH.h"

#include "GameObjects/GameObject.h"
#include "Trainer.h"
#include "Controllers/PlayerController.h"

#include "Sprites/AnimatedSprite.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/TileMap.h"

#include "Mesh/Mesh.h"

#include "GameplayHelpers/SceneManager.h"
#include "Scenes/Scene.h"
#include "Scenes/OakLab.h"
#include "Scenes/PalletTown.h"

Trainer::Trainer(ResourceManager * aResourceManager, GameCore * myGame, Mesh * myMesh, GLuint aTexture) :GameObject(myGame, myMesh, aTexture)
{
	myDirection = SpriteWalkDown;
	myResourceManager = aResourceManager;
	m_pMesh->GenerateFrameMesh();

	//Initialize the animated sprites
	for (int i = 0; i < NUM_DIRECTIONS; i++)
	{
		m_Animations[i] = new AnimatedSprite(myResourceManager, myGame, myMesh, 2, aTexture);
		m_Animations[i]->AddFrame(AnimationKeys[i] + "1.png");
		m_Animations[i]->AddFrame(AnimationKeys[i] + "2.png");
		m_Animations[i]->AddFrame(AnimationKeys[i] + "1.png");
		m_Animations[i]->AddFrame(AnimationKeys[i] + "3.png");
		m_Animations[i]->SetFrameSpeed(6.0f);
		m_Animations[i]->SetLoop(true);
		m_Animations[i]->SetPosition(m_Position);
	}

	m_Stop = false;
	m_InTransition = false;
}

Trainer::~Trainer()
{
	for (int i = 0; i < NUM_DIRECTIONS; i++)
	{
		delete m_Animations[i];
		m_Animations[i] = nullptr;
	}

	myResourceManager = nullptr;
}

void Trainer::Update(float deltatime)
{
	Pause();
	if (m_InTransition == false)
	{
		if (myController)
		{
			if (m_Stop == false)
			{
				if (myController->IsForwardHeld())
				{
					Move(SpriteWalkUp, deltatime);
				}
				if (myController->IsReverseHeld())
				{
					Move(SpriteWalkDown, deltatime);
				}
				if (myController->IsTurnRightHeld())
				{
					Move(SpriteWalkRight, deltatime);
				}
				if (myController->IsTurnLeftHeld())
				{
					Move(SpriteWalkLeft, deltatime);
				}
				if (myController->IsInputReleased())
				{
					for (int i = 0; i < NUM_DIRECTIONS; i++)
					{
						m_Animations[i]->SetFrameIndex(0);
					}
				}

			}
		}
	}

	if (m_InTransition == true)
	{
		if (myDirection == SpriteWalkUp || myDirection == SpriteWalkRight)
		{
			if (m_Position.y < aTransitionDestination.y)
			{
				Move(myDirection, deltatime);
			}
			else if (m_Position.x < aTransitionDestination.x)
			{
				Move(myDirection, deltatime);
			}
			else
			{
				m_InTransition = false;
			}
		}
		if (myDirection == SpriteWalkDown || myDirection == SpriteWalkLeft)
		{
			if (m_Position.y > aTransitionDestination.y)
			{
				Move(myDirection, deltatime);
			}
			else if (m_Position.x > aTransitionDestination.x)
			{
				Move(myDirection, deltatime);
			}
			else
			{
				m_InTransition = false;
			}
		}
	}

	for (int i = 0; i < NUM_DIRECTIONS; i++)
	{
		m_Animations[i]->SetPosition(GetPosition());
		m_Animations[i]->Update(deltatime);
	}
}

void Trainer::Draw(vec2 camPos, vec2 projecScale)
{
	m_Animations[myDirection]->Draw(camPos, projecScale);
}

void Trainer::Move(SpriteDirection dir, float deltatime)
{
	NewPosition = m_Position;

	Resume();

	if (myDirection != dir)
	{
		myDirection = dir;
	}

	vec2 velocity = DIRECTIONVECTOR[dir] * PLAYER_SPEED;

	NewPosition += velocity * deltatime;
	if (m_InTransition == false)
	{
		if (CheckForCollision(NewPosition) == true)
		{
			SetPosition(NewPosition);
		}
	}
	else
	{
		SetPosition(NewPosition);
	}
}

void Trainer::Pause()
{
	for (int i = 0; i < NUM_DIRECTIONS; i++)
	{
		m_Animations[i]->Pause();
	}
}

void Trainer::Resume()
{
	for (int i = 0; i < NUM_DIRECTIONS; i++)
	{
		m_Animations[i]->Resume();
	}
}

void Trainer::SetStop(bool StopPlayer)
{
	if (m_Stop != StopPlayer)
	{
		m_Stop = StopPlayer;
	}
}

void Trainer::OnEvent(Event * anEvent)
{
	DoorEvent* e = (DoorEvent*)anEvent;

	if (e->GetDoorType() == 11)
	{
		myDirection = SpriteWalkUp;
		SetPosition(m_pGame->GetSceneManager()->GetActiveScene()->GetPlayerStart());
		PlayerTransition();
	}
	if (e->GetDoorType() == 10)
	{
		myDirection = SpriteWalkDown;
		SetPosition(m_pGame->GetSceneManager()->GetActiveScene()->GetPlayerStart());
		PlayerTransition();
	}
}

void Trainer::PlayerTransition()
{
	m_InTransition = true;

	aTransitionDestination = GetPosition() + vec2(DIRECTIONVECTOR[myDirection] * (TILESIZE / 4));
}

SpriteDirection Trainer::GetMyDirection()
{
	return myDirection;
}

bool Trainer::CheckForCollision(vec2 playerNewPosition)
{
	//Get the location of each point of collision on the player and then truncate it to a row and column
	ivec2 OriginIndex = ivec2((playerNewPosition.x / TILESIZE), ((playerNewPosition.y - 0.3f) / TILESIZE));
	ivec2 TopLeftIndex = ivec2((playerNewPosition.x / TILESIZE), (((playerNewPosition.y - 0.5f) + (TILESIZE / 2)) / TILESIZE));
	ivec2 TopRightIndex = ivec2(((playerNewPosition.x + (TILESIZE / 2)) / TILESIZE), (((playerNewPosition.y - 0.5f) + (TILESIZE / 2)) / TILESIZE));
	ivec2 BottomRightIndex = ivec2(((playerNewPosition.x + (TILESIZE / 2)) / TILESIZE), ((playerNewPosition.y - 0.3f) / TILESIZE));

	//Check each index for whether the tile it lands on is walkable
	bool CheckOrigin = m_pGame->GetTileMap()->GetTileAtPlayer(OriginIndex);
	bool CheckTopLeft = m_pGame->GetTileMap()->GetTileAtPlayer(TopLeftIndex);
	bool CheckTopRight = m_pGame->GetTileMap()->GetTileAtPlayer(TopRightIndex);
	bool CheckBottomRight = m_pGame->GetTileMap()->GetTileAtPlayer(BottomRightIndex);

	//If all the point land on walkable tile return true else return false
	bool Collision = (CheckOrigin && CheckTopLeft && CheckTopRight && CheckBottomRight);
	
	return Collision;
}
