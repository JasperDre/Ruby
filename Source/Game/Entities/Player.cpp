#include "GamePCH.h"
#include "Player.h"

#include "Controllers/PlayerController.h"
#include "GameplayHelpers/ResourceManager.h"
#include "GameplayHelpers/SceneManager.h"
#include "GameplayHelpers/TileMap.h"
#include "Mesh/Mesh.h"
#include "Scenes/Scene.h"
#include "Sprites/AnimatedSprite.h"

Player::Player(ResourceManager* aResourceManager, GameCore* aGameCore, Mesh* aMesh, GLuint aTexture)
	: Entity(aGameCore, aMesh, aTexture)
	, myController(nullptr)
{
	myAnimationKeys = { "PlayerWalkDown_", "PlayerWalkRight_", "PlayerWalkLeft_", "PlayerWalkUp_" };

	for (unsigned int i = 0; i < myAnimations.size(); i++)
	{
		myAnimations[i] = new AnimatedSprite(aResourceManager, aGameCore, aMesh, 2, aTexture);
		myAnimations[i]->AddFrame(myAnimationKeys[i] + "1.png");
		myAnimations[i]->AddFrame(myAnimationKeys[i] + "2.png");
		myAnimations[i]->AddFrame(myAnimationKeys[i] + "1.png");
		myAnimations[i]->AddFrame(myAnimationKeys[i] + "3.png");
		myAnimations[i]->SetFrameSpeed(6.0f);
		myAnimations[i]->SetLoop(true);
		myAnimations[i]->SetPosition(myPosition);
	}

	myDirection = SpriteDirection::SpriteWalkDown;
	myResourceManager = aResourceManager;
	myMesh->GenerateFrameMesh();

	myIsStopped = false;
	myIsInTransition = false;
}

Player::~Player()
{
	for (const auto& m_Animation : myAnimations)
		delete m_Animation;
}

void Player::Update(float deltatime)
{
	Pause();
	if (!myIsInTransition)
	{
		if (myController)
		{
			if (!myIsStopped)
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
					for (const auto& m_Animation : myAnimations)
						m_Animation->SetFrameIndex(0);
				}

			}
		}
	}

	if (myIsInTransition)
	{
		switch (myDirection)
		{
			case SpriteDirection::SpriteWalkUp:
			case SpriteDirection::SpriteWalkRight:
			{
				if (myPosition.myY < myTransitionDestination.myY)
				{
					Move(myDirection, deltatime);
				}
				else if (myPosition.myX < myTransitionDestination.myX)
				{
					Move(myDirection, deltatime);
				}
				else
				{
					myIsInTransition = false;
				}

				break;
			}
			case SpriteDirection::SpriteWalkDown:
			case SpriteDirection::SpriteWalkLeft:
			{
				if (myPosition.myY > myTransitionDestination.myY)
				{
					Move(myDirection, deltatime);
				}
				else if (myPosition.myX > myTransitionDestination.myX)
				{
					Move(myDirection, deltatime);
				}
				else
				{
					myIsInTransition = false;
				}

				break;
			}
			case SpriteDirection::SpriteDirectionStop:
				break;
		}
	}

	for (const auto& m_Animation : myAnimations)
	{
		m_Animation->SetPosition(GetPosition());
		m_Animation->Update(deltatime);
	}
}

void Player::Draw(Vector2Float camPos, Vector2Float projecScale)
{
	myAnimations[static_cast<int>(myDirection)]->Draw(camPos, projecScale);
}

void Player::Move(SpriteDirection dir, float deltatime)
{
	myNewPosition = myPosition;

	Resume();

	if (myDirection != dir)
	{
		myDirection = dir;
	}

	const Vector2Float velocity = DIRECTIONVECTOR[static_cast<int>(dir)] * PLAYER_SPEED;

	myNewPosition += velocity * deltatime;
	if (myIsInTransition == false)
	{
		if (CheckForCollision(myNewPosition) == true)
		{
			SetPosition(myNewPosition);
		}
	}
	else
	{
		SetPosition(myNewPosition);
	}
}

void Player::Pause() const
{
	for (const auto& m_Animation : myAnimations)
		m_Animation->Pause();
}

void Player::Resume() const
{
	for (const auto m_Animation : myAnimations)
		m_Animation->Resume();
}

void Player::SetStop(bool aStopPlayer)
{
	if (myIsStopped != aStopPlayer)
		myIsStopped = aStopPlayer;
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
	myIsInTransition = true;
	myTransitionDestination = GetPosition() + Vector2Float(DIRECTIONVECTOR[static_cast<int>(myDirection)] * (TILESIZE / 4));
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
	const bool CheckOrigin = myGameCore->GetTileMap()->IsTileAtPlayer(OriginIndex);
	const bool CheckTopLeft = myGameCore->GetTileMap()->IsTileAtPlayer(TopLeftIndex);
	const bool CheckTopRight = myGameCore->GetTileMap()->IsTileAtPlayer(TopRightIndex);
	const bool CheckBottomRight = myGameCore->GetTileMap()->IsTileAtPlayer(BottomRightIndex);

	//If all the point land on walkable tile return true else return false
	const bool Collision = (CheckOrigin && CheckTopLeft && CheckTopRight && CheckBottomRight);

	return Collision;
}
