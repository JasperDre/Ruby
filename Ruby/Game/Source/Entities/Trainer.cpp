#include "GamePCH.h"
#include "Trainer.h"

#include "Controllers/PlayerController.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/SceneManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"
#include "Scenes/Scene.h"
#include "Sprites/AnimatedSprite.h"

Trainer::Trainer(ResourceManager* aResourceManager, GameCore* myGame, Mesh * myMesh, GLuint aTexture)
	: Entity(myGame, myMesh, aTexture)
	, myController(nullptr)
{
	AnimationKeys[0] = "PlayerWalkDown_";
	AnimationKeys[1] = "PlayerWalkRight_";
	AnimationKeys[2] = "PlayerWalkLeft_";
	AnimationKeys[3] = "PlayerWalkUp_";
	myDirection = SpriteDirection::SpriteWalkDown;
	myResourceManager = aResourceManager;
	m_pMesh->GenerateFrameMesh();

	for (unsigned int i = 0; i < NUM_DIRECTIONS; i++)
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
	for (auto& m_Animation : m_Animations)
	{
		delete m_Animation;
		m_Animation = nullptr;
	}

	myResourceManager = nullptr;
}

void Trainer::Update(float deltatime)
{
	Pause();
	if (!m_InTransition)
	{
		if (myController)
		{
			if (!m_Stop)
			{
				if (myController->IsForwardHeld())
				{
					Move(SpriteDirection::SpriteWalkUp, deltatime);
				}
				if (myController->IsReverseHeld())
				{
					Move(SpriteDirection::SpriteWalkDown, deltatime);
				}
				if (myController->IsTurnRightHeld())
				{
					Move(SpriteDirection::SpriteWalkRight, deltatime);
				}
				if (myController->IsTurnLeftHeld())
				{
					Move(SpriteDirection::SpriteWalkLeft, deltatime);
				}
				if (myController->IsInputReleased())
				{
					for (const auto& m_Animation : m_Animations)
						m_Animation->SetFrameIndex(0);
				}

			}
		}
	}

	if (m_InTransition)
	{
		if (myDirection == SpriteDirection::SpriteWalkUp || myDirection == SpriteDirection::SpriteWalkRight)
		{
			if (m_Position.myY < aTransitionDestination.myY)
			{
				Move(myDirection, deltatime);
			}
			else if (m_Position.myX < aTransitionDestination.myX)
			{
				Move(myDirection, deltatime);
			}
			else
			{
				m_InTransition = false;
			}
		}
		if (myDirection == SpriteDirection::SpriteWalkDown || myDirection == SpriteDirection::SpriteWalkLeft)
		{
			if (m_Position.myY > aTransitionDestination.myY)
			{
				Move(myDirection, deltatime);
			}
			else if (m_Position.myX > aTransitionDestination.myX)
			{
				Move(myDirection, deltatime);
			}
			else
			{
				m_InTransition = false;
			}
		}
	}

	for (const auto& m_Animation : m_Animations)
	{
		m_Animation->SetPosition(GetPosition());
		m_Animation->Update(deltatime);
	}
}

void Trainer::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	m_Animations[static_cast<int>(myDirection)]->Draw(camPos, projecScale);
}

void Trainer::Move(SpriteDirection dir, float deltatime)
{
	NewPosition = m_Position;

	Resume();

	if (myDirection != dir)
	{
		myDirection = dir;
	}

	const Vector2Float velocity = DIRECTIONVECTOR[static_cast<int>(dir)] * PLAYER_SPEED;

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
	for (const auto& m_Animation : m_Animations)
		m_Animation->Pause();
}

void Trainer::Resume() const
{
	for (const auto m_Animation : m_Animations)
		m_Animation->Resume();
}

void Trainer::SetStop(bool StopPlayer)
{
	if (m_Stop != StopPlayer)
		m_Stop = StopPlayer;
}

void Trainer::OnEvent(Event* anEvent)
{
	const DoorEvent* doorEvent = dynamic_cast<DoorEvent*>(anEvent);
	if (doorEvent->GetDoorType() == 11)
	{
		myDirection = SpriteDirection::SpriteWalkUp;
		SetPosition(m_pGame->GetSceneManager()->GetActiveScene()->GetPlayerStart());
		PlayerTransition();
	}
	if (doorEvent->GetDoorType() == 10)
	{
		myDirection = SpriteDirection::SpriteWalkDown;
		SetPosition(m_pGame->GetSceneManager()->GetActiveScene()->GetPlayerStart());
		PlayerTransition();
	}
}

void Trainer::PlayerTransition()
{
	m_InTransition = true;
	aTransitionDestination = GetPosition() + Vector2Float(DIRECTIONVECTOR[static_cast<int>(myDirection)] * (TILESIZE / 4));
}

SpriteDirection Trainer::GetMyDirection() const
{
	return myDirection;
}

bool Trainer::CheckForCollision(Vector2Float aPosition) const
{
	//Get the location of each point of collision on the player and then truncate it to a row and column
	const ivec2 OriginIndex = ivec2((aPosition.myX / TILESIZE), ((aPosition.myY - 0.3f) / TILESIZE));
	const ivec2 TopLeftIndex = ivec2((aPosition.myX / TILESIZE), (((aPosition.myY - 0.5f) + (TILESIZE / 2)) / TILESIZE));
	const ivec2 TopRightIndex = ivec2(((aPosition.myX + (TILESIZE / 2)) / TILESIZE), (((aPosition.myY - 0.5f) + (TILESIZE / 2)) / TILESIZE));
	const ivec2 BottomRightIndex = ivec2(((aPosition.myX + (TILESIZE / 2)) / TILESIZE), ((aPosition.myY - 0.3f) / TILESIZE));

	//Check each index for whether the tile it lands on is walkable
	const bool CheckOrigin = m_pGame->GetTileMap()->GetTileAtPlayer(OriginIndex);
	const bool CheckTopLeft = m_pGame->GetTileMap()->GetTileAtPlayer(TopLeftIndex);
	const bool CheckTopRight = m_pGame->GetTileMap()->GetTileAtPlayer(TopRightIndex);
	const bool CheckBottomRight = m_pGame->GetTileMap()->GetTileAtPlayer(BottomRightIndex);

	//If all the point land on walkable tile return true else return false
	const bool Collision = (CheckOrigin && CheckTopLeft && CheckTopRight && CheckBottomRight);

	return Collision;
}
