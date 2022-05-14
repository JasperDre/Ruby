#include "GamePCH.h"
#include "Player.h"

#include "Controllers/PlayerController.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/SceneManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"
#include "Scenes/Scene.h"
#include "Sprites/AnimatedSprite.h"

Player::Player(ResourceManager* aResourceManager, GameCore* myGame, Mesh* aMesh, GLuint aTexture)
	: Entity(myGame, aMesh, aTexture)
	, myController(nullptr)
{
	AnimationKeys = { "PlayerWalkDown_", "PlayerWalkRight_", "PlayerWalkLeft_", "PlayerWalkUp_" };

	for (unsigned int i = 0; i < m_Animations.size(); i++)
	{
		m_Animations[i] = new AnimatedSprite(aResourceManager, myGame, aMesh, 2, aTexture);
		m_Animations[i]->AddFrame(AnimationKeys[i] + "1.png");
		m_Animations[i]->AddFrame(AnimationKeys[i] + "2.png");
		m_Animations[i]->AddFrame(AnimationKeys[i] + "1.png");
		m_Animations[i]->AddFrame(AnimationKeys[i] + "3.png");
		m_Animations[i]->SetFrameSpeed(6.0f);
		m_Animations[i]->SetLoop(true);
		m_Animations[i]->SetPosition(myPosition);
	}

	myDirection = SpriteDirection::SpriteWalkDown;
	myResourceManager = aResourceManager;
	myMesh->GenerateFrameMesh();

	m_Stop = false;
	m_InTransition = false;
}

Player::~Player()
{
	for (const auto& m_Animation : m_Animations)
		delete m_Animation;
}

void Player::Update(float deltatime)
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
			if (myPosition.myY < aTransitionDestination.myY)
			{
				Move(myDirection, deltatime);
			}
			else if (myPosition.myX < aTransitionDestination.myX)
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
			if (myPosition.myY > aTransitionDestination.myY)
			{
				Move(myDirection, deltatime);
			}
			else if (myPosition.myX > aTransitionDestination.myX)
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

void Player::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	m_Animations[static_cast<int>(myDirection)]->Draw(camPos, projecScale);
}

void Player::Move(SpriteDirection dir, float deltatime)
{
	NewPosition = myPosition;

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

void Player::Pause() const
{
	for (const auto& m_Animation : m_Animations)
		m_Animation->Pause();
}

void Player::Resume() const
{
	for (const auto m_Animation : m_Animations)
		m_Animation->Resume();
}

void Player::SetStop(bool StopPlayer)
{
	if (m_Stop != StopPlayer)
		m_Stop = StopPlayer;
}

void Player::OnEvent(Event* anEvent)
{
	const DoorEvent* doorEvent = dynamic_cast<DoorEvent*>(anEvent);
	if (doorEvent->GetDoorType() == 11)
	{
		myDirection = SpriteDirection::SpriteWalkUp;
		SetPosition(myGameCore->GetSceneManager()->GetActiveScene()->GetPlayerStart());
		PlayerTransition();
	}
	if (doorEvent->GetDoorType() == 10)
	{
		myDirection = SpriteDirection::SpriteWalkDown;
		SetPosition(myGameCore->GetSceneManager()->GetActiveScene()->GetPlayerStart());
		PlayerTransition();
	}
}

void Player::PlayerTransition()
{
	m_InTransition = true;
	aTransitionDestination = GetPosition() + Vector2Float(DIRECTIONVECTOR[static_cast<int>(myDirection)] * (TILESIZE / 4));
}

SpriteDirection Player::GetMyDirection() const
{
	return myDirection;
}

bool Player::CheckForCollision(Vector2Float aPosition) const
{
	//Get the location of each point of collision on the player and then truncate it to a row and column
	const Vector2Int OriginIndex = Vector2Int(static_cast<int>(aPosition.myX / TILESIZE), static_cast<int>((aPosition.myY - 0.3f) / TILESIZE));
	const Vector2Int TopLeftIndex = Vector2Int(static_cast<int>(aPosition.myX / TILESIZE), static_cast<int>(((aPosition.myY - 0.5f) + (TILESIZE / 2)) / TILESIZE));
	const Vector2Int TopRightIndex = Vector2Int(static_cast<int>((aPosition.myX + (TILESIZE / 2)) / TILESIZE), static_cast<int>(((aPosition.myY - 0.5f) + (TILESIZE / 2)) / TILESIZE));
	const Vector2Int BottomRightIndex = Vector2Int(static_cast<int>((aPosition.myX + (TILESIZE / 2)) / TILESIZE), static_cast<int>((aPosition.myY - 0.3f) / TILESIZE));

	//Check each index for whether the tile it lands on is walkable
	const bool CheckOrigin = myGameCore->GetTileMap()->GetTileAtPlayer(OriginIndex);
	const bool CheckTopLeft = myGameCore->GetTileMap()->GetTileAtPlayer(TopLeftIndex);
	const bool CheckTopRight = myGameCore->GetTileMap()->GetTileAtPlayer(TopRightIndex);
	const bool CheckBottomRight = myGameCore->GetTileMap()->GetTileAtPlayer(BottomRightIndex);

	//If all the point land on walkable tile return true else return false
	const bool Collision = (CheckOrigin && CheckTopLeft && CheckTopRight && CheckBottomRight);

	return Collision;
}
